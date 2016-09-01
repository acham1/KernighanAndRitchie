/** An alternate organization uses getline to read an entire input line; this makes
  * getch and ungetch unnecessary. Revise the calculator to use this approach. */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#define BUFSIZE 100
#define MAXOP 100/* max size of operand or operator */
#define NUMBER '0'/* signal that a number was found */
#define MAXVAL 100 /* maximum depth of val stack */
#define UNKNOWN 0
#define SIN -2
#define EXP -3
#define POW -4
#define VAR -5
#define MAXLINE 1000

int getch(void);
void ungetch(int c);
int getop(char []);
void push(double);
double pop(void);
int getType(char s[]);
int mygetline(char s[], int lim);

bool endset = false;
int linep = 0;
char line[MAXLINE + 1] = "";
int currVar;
int variables[26];
bool VarSet[26];
int keys[] = {SIN, EXP, POW};
char * terms[] = {"sin", "exp", "pow", "end"};
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */
int sp = 0; /* next free stack position */
double MVal = 0;
bool MSet = false;
double val[MAXVAL]; /* value stack */

int main(void) {
	char s[MAXOP];
	int type, i;
	double op, op2;

	for (i = 0; i < 26; i++) {
		VarSet[i] = false;
	}

	printf("An alternate organization uses getline to read an entire input line; this makes\n"
		"getch and ungetch unnecessary. Revise the calculator to use this approach.\n");

	printf("\nCommands: P - print top elements, D - duplicate top element, C - clear stack, M - push most recently P-printed element\n");
	printf("\nSupports: sin, exp, pow\n");
	printf("\nEntering input from 'a' - 'z' stores top operand on first call, and pushes\n"
		"that value in subsequent calls.\n\n");

	while ((type = getop(s)) != EOF) {
		switch (type) {
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if (op2 != 0.0) {
					push(pop() / op2);
				} else {
					printf("error: zero divisor\n");
				}
				break;
			case '%':
				op2 = pop();
				if (op2 != 0.0) {
					push(fmod(pop(), op2));
				} else {
					printf("error: zero divisor\n");
				}
				break;
			case 'P':
				printf("\ttop: %.8g\n", op = pop());
				push(op);
				MSet = true;
				MVal = op;
				break;
			case 'D':
				op = pop();
				push(op);
				push(op);
				printf("\tduplicated %.8g\n", op);
				break;
			case 'C':
				sp = 0;
				printf("\tcleared stack\n");
				break;
			case 'M':
				if (MSet) {
					push(MVal);
				} else {
					printf("\tno previously printed value\n");
				}
				break;
			case SIN:
				push(sin(pop()));
				break;
			case EXP:
				push(exp(pop()));
				break;
			case POW:
				op2 = pop();
				push(pow(pop(), op2));
				break;
			case VAR:
				if (VarSet[currVar - 'a']) {
					push(variables[currVar - 'a']);
				} else {
					VarSet[currVar - 'a'] = true;
					variables[currVar - 'a'] = pop();
					push(variables[currVar - 'a']);
				}
				break;
			case '\n':
				printf("\t%.8g\n", op = pop());
				push(op);
				break;

			default:
				printf("error: unknown command %s\n", s);
				break;
		}
	}
	return EXIT_SUCCESS;
}

int getType(char s[]) {
	int i = 0, out = UNKNOWN;
	while (strcmp(terms[i], "end") != 0) {
		if (strcmp(terms[i], s) == 0) {
			out = keys[i];
		}
		i++;
	}
	return out;
}

/* getop: get next character or numeric operand */
int getop(char s[]) {
	int i = 0, c, c2;
	bool wasSign;

	while ((s[0] = c = getch()) == ' ' || c == '\t');
	if (c == '\n' || c == EOF) {
		return c;
	}
	if (!isdigit(c) && c != '.' && c != '-' && c != '+') {
		while ((c = getch()) != ' ' && c != '\t' && c != '\n' && c != EOF) {
			s[++i] = c;
		}
		ungetch(c);
		if (i == 0) {
			if (s[0] >= 'a' && s[0] <= 'z') {
				currVar = s[0];
				return VAR;
			}
			return s[0];
		}
		s[++i] = '\0';
		return getType(s);  /* not a number */
	}

	wasSign = (c == '+' || c == '-');
	if (wasSign) {
		c2 = getch();
		if (!isdigit(c2) && c2 != '.') {
			ungetch(c2);
			return c;
		} else {
			s[1] = c = c2;
			i = 1;
		}
	} else {
		i = 0;
	}

	if (isdigit(c)) {/* collect integer part */
		while (isdigit(s[++i] = c = getch()));
	}
	if (c == '.') {	/* collect fraction part */
		while (isdigit(s[++i] = c = getch()));
	}
	s[i] = '\0';
	if (c != EOF) {
		ungetch(c);
	}
	return NUMBER;
}

/* push: push f onto value stack */
void push(double f) {
	if (sp < MAXVAL) {
		val[sp++] = f;
	} else {
		printf("error: stack full, can't push %g\n", f);
	}
}

/* pop: pop and return top value from stack */
double pop(void) {
	if (sp > 0) {
		return val[--sp];
	} else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

int getch(void) { /* get a (possibly pushed-back) character */
	if (bufp > 0) {
		return buf[--bufp];
	} else if (line[linep] == '\0') {
		if (endset) {
			return EOF;
		} else {
			endset = (mygetline(line, MAXLINE) == EOF);
			linep = 0;
			return getch();
		}
	} else {
		return line[linep++];
	}
}

void ungetch(int c) {/* push character back on input */
	if (bufp >= BUFSIZE) {
		printf("ungetch: too many characters\n");
 	} else {
		buf[bufp++] = c;
 	}
}

/* getline: get line into s, return last char */
int mygetline(char s[], int lim) {
	int c, i = 0;
	while (--lim > 0 && (c=getchar()) != EOF && c != '\n') {
		s[i++] = c;
	}
	if (c == '\n') {
		s[i++] = c;
		s[i] = '\0';
	}
	return c;
}
