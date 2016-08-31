/** Add access to library functions like sin, exp, and pow. See <math.h> in
  * Appendix B, Section 4. */

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


bool wasSign;
int getch(void);
void ungetch(int c);
int getop(char []);
void push(double);
double pop(void);
int getType(char s[]);

int keys[] = {SIN, EXP, POW};
char * terms[] = {"sin", "exp", "pow", "end"};
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */
int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */

int main(void) {
	char s[MAXOP];
	int type;
	double op, op2;

	printf("Add access to library functions like sin, exp, and pow. See <math.h> in\n"
		"Appendix B, Section 4.\n");

	printf("\nCommands: P - print top elements, D - duplicate top element, C - clear stack\n");
	printf("\nSupports: sin, exp, pow\n\n");

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
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {/* push character back on input */
	if (bufp >= BUFSIZE) {
		printf("ungetch: too many characters\n");
 	} else {
		buf[bufp++] = c;
 	}
}