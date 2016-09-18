/** Write the program expr, which evaluates a reverse Polish expression from the
  * command line, where each operator or operand is a separate argument. For example,
  * expr (2 3 4 + *) evaluates 2 * (3+4). */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#define BUFSIZE 100
#define NUMBER '0'/* signal that a number was found */
#define MAXVAL 100 /* maximum depth of val stack */
#define MAX_LENGTH 

bool wasSign;
int getop(char []);
void push(double);
double pop(void);

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */
int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */

int main(int argc, char *argv[]) {
	char * s;
	int type, argNum = 1;
	double op, op2;

	printf("Write the program expr, which evaluates a reverse Polish expression from the\n"
		"command line, where each operator or operand is a separate argument. For example,\n"
		"expr '2 3 4 + *' evaluates 2 * (3+4).\n");

	printf("Please enclose each argument in double quotes: \n");
	while ((type = getop(s = *(argv + argNum++))) != EOF && type != '\0') {
		//printf("\nArg was: %s\n", s);
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
			case '\n':
				printf("\t%.8g\n", op = pop());
				break;
				push(op);
			default:
				printf("error: unknown command %s\n", s);
				break;
		}
	}
	printf("Final answer is: %f\n", pop());
	return EXIT_SUCCESS;
}

/* getop: get next character or numeric operand */
int getop(char s[]) {
	int i, c, c2, stringPos = 0;
	bool wasSign;
	if (s == NULL) {
		return '\0';
	}
	while ((s[0] = c = s[stringPos++]) == ' ' || c == '\t');
	if (!isdigit(c) && c != '.' && c != '-' && c != '+') {
		return c;  /* not a number */
	}

	wasSign = (c == '+' || c == '-');
	if (wasSign) {
		c2 = s[stringPos++];
		if (!isdigit(c2) && c2 != '.' && c2 != '\0') {
			return c2;
		} else if (c2 == '\0') {
			return c;
		} else {
			s[1] = c = c2;
			i = 1;
		}
	} else {
		i = 0;
	}

	if (isdigit(c)) {/* collect integer part */
		while (isdigit(s[++i] = c = s[stringPos++]));
	}
	if (c == '.') {	/* collect fraction part */
		while (isdigit(s[++i] = c = s[stringPos++]));
	}
	s[i] = '\0';
	if (c != EOF && c != '\0') {
		return c;
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