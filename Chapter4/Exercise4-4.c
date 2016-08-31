/** Add the commands to print the top elements of the stack without popping, to
  * duplicate it, and to swap the top two elements. Add a command to clear the stack. */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#define BUFSIZE 100
#define MAXOP 100/* max size of operand or operator */
#define NUMBER '0'/* signal that a number was found */
#define MAXVAL 100 /* maximum depth of val stack */
#define MAX_LENGTH 

bool wasSign;
int getch(void);
void ungetch(int c);
int getop(char []);
void push(double);
double pop(void);

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */
int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */


int main(void) {
	char s[MAXOP];
	int type;
	double op, op2;

	printf("Add the commands to print the top elements of the stack without popping, to\n"
		"duplicate it, and to swap the top two elements. Add a command to clear the\n"
		"stack.\n");

	printf("Commands: p - print top elements, d - duplicate top element, c - clear stack\n");

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
			case 'p':
				printf("\ttop: %.8g\n", op = pop());
				push(op);
				break;
			case 'd':
				op = pop();
				push(op);
				push(op);
				printf("\tduplicated %.8g\n", op);
				break;
			case 'c':
				sp = 0;
				printf("\tcleared stack\n");
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

/* getop: get next character or numeric operand */
int getop(char s[]) {
	int i, c, c2;
	bool wasSign;
	while ((s[0] = c = getch()) == ' ' || c == '\t');
	s[1] = '\0';
	if (!isdigit(c) && c != '.' && c != '-' && c != '+') {
		return c;  /* not a number */
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