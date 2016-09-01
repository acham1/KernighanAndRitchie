/** Modify getop so that it doesn't need to use ungetch. Hint: use an internal 
  * static variable. */

#include <stdio.h>
#include "Exercise4-11.calc.h"
#define MAXVAL 100

static int sp = 0;
static double val[MAXVAL];

void push(double f) {
	if (sp < MAXVAL) {
		val[sp++] = f;
	} else {
		printf("error: stack full, can't push %g\n", f);
	}
}

double pop(void) {
	if (sp > 0) {
		return val[--sp];
	} else {
		printf("error: stack empty\n");
		return 0.0;
	}
}
