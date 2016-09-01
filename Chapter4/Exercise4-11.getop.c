/** Modify getop so that it doesn't need to use ungetch. Hint: use an internal 
  * static variable. */

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "Exercise4-11.calc.h"

int getop(char s[]) {
	static char ungot;
	static bool hasUngot = false;
	int i = 0, c;
	
	if (hasUngot && ungot != ' ' && ungot != '\t') {
		s[0] = ungot;
	} else {
		while ((s[0] = c = getch()) == ' ' || c == '\t');
	}
	hasUngot = false;
	s[1] = '\0';
	
	if (!isdigit(c) && c != '.') {
		return c;
	}
	if (isdigit(c)) {
		while (isdigit(s[++i] = c = getch())) ;
	}
	if (c == '.') {
		while (isdigit(s[++i] = c = getch()));
	}
	s[i] = '\0';
	if (c != EOF) {
		ungot = c;
		hasUngot = true;
	}
	return NUMBER;
}
