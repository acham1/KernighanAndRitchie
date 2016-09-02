/** As written, getint treats a + or - not followed by a digit as a valid
  * representation of zero. Fix it to push such a character back on the input. */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#define MAXLEN 100

int getch(void);
void ungetch(int);
int getint(int *pn);

static bool haswaiting = false;
static int waiting;

int main(void) {
	printf("As written, getint treats a + or - not followed by a digit as a valid\n"
		"representation of zero. Fix it to push such a character back on the input.\n");

	int myint = 0;
	printf("Please enter an integer: ");
	if (getint(&myint) != 0) {
		printf("\nInteger was: %d\n", myint);
	} else {
		printf("\nerror: invalid input.\n");
	}
	return EXIT_SUCCESS;
}

int getint(int *pn) {
	int c, sign;
	while (isspace(c = getch())) ; /* skip white space */
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c); /* it is not a number */
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-') {
		c = getch();
		if (!isdigit(c)) {
			return 0;
		}
	}
	for (*pn = 0; isdigit(c); c = getch()) {
		*pn = 10 * *pn + (c - '0');
	}
	*pn *= sign;
	if (c != EOF) {
		ungetch(c);
	}
	return c;
}

int getch(void) {
	if (haswaiting) {
		haswaiting = false;
		return waiting;
	} else {
		return getchar();
	}
}

void ungetch(int i) {
	if (haswaiting) {
		printf("\n**error: too many calls to ungetch**\n");
	} else {
		haswaiting = true;
		waiting = i;
	}
}
