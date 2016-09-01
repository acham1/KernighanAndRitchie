/** Suppose that there will never be more than one character of pushback. Modify
  * getch and ungetch accordingly. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFSIZE 1000
#define NUMBER '0'/* signal that a number was found */
#define MAXVAL 100 /* maximum depth of val stack */

char buf;
char outString[BUFSIZE];
bool bufOccupied = false;
char pre = '5';

void ungetch(char c);
int getch(void);

int main(void) {
	printf("Suppose that there will never be more than one character of pushback. Modify\n"
		"getch and ungetch accordingly.\n");

	printf("Please enter line of text: ");

	char c;
	int i = 0;
	ungetch(pre);
	while ((c = getch()) != '\n' && c != EOF) {
		outString[i++] = c;
	}
	outString[i++] = '\0';

	printf("\nYour input should be reproduced below, preceded by pre-ungotten char '%c'\n", pre);

	printf("\nPrinting received input from getch(): %s\n", outString);

	return EXIT_SUCCESS;
}

void ungetch(char c) {
	if (bufOccupied) {
		printf("\n error: only 1 char of pushback allowed\n");
	} else {
		bufOccupied = true;
		buf = c;
	}
}

int getch(void) { /* get a (possibly pushed-back) character */
	if (bufOccupied) {
		bufOccupied = false;
		return buf;
	} else {
		return getchar();
	}
}