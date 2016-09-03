/** Write getfloat, the floating-point analog of getint. What type does getfloat
  * return as its function value? */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#define MAXLEN 100

int getch(void);
void ungetch(int);
int getfloat(float *pn);

static bool haswaiting = false;
static int waiting;

int main(void) {
	printf("Write getfloat, the floating-point analog of getint. What type does getfloat\n"
		"return as its function value?\n");

	printf("\ngetfloat can return an int just like getint did, since the return value\n"
		"is just a signal and the gotten float is stored in a pointer already.\n");

	float myfloat = 0;
	printf("\nPlease enter a float: ");
	if (getfloat(&myfloat) != 0) {
		printf("\nFloat was: %f\n", myfloat);
	} else {
		printf("\nerror: invalid input.\n");
	}
	return EXIT_SUCCESS;
}

int getfloat(float *pn) {
	int c, sign;
	float divisor = 1;
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
	if (c != EOF && c != '.') {
		*pn *= sign;
		ungetch(c);
		return c;
	} else if (c == EOF) {
		return c;
	} else {
		c = getch();
	}
	while (isdigit(c)) {
		divisor *= 10;
		*pn = 10 * *pn + (c - '0');
		c = getchar();
	}
	*pn *= sign;
	*pn /= divisor;
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
