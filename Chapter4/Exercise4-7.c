/** Write a routine ungets(s) that will push back an entire string onto the input.
  * Should ungets know about buf and bufp, or should it just use ungetch? */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 1000
#define NUMBER '0'/* signal that a number was found */
#define MAXVAL 100 /* maximum depth of val stack */

char buf[BUFSIZE];
char outString[BUFSIZE];
int bufp = 0;


void ungets(char s[]);
int getch(void);

int main(void) {
	printf("Write a routine ungets(s) that will push back an entire string onto the input.\n"
		"Should ungets know about buf and bufp, or should it just use ungetch?\n");

	printf("\nungets(s) should know about buf and bufp, since it can use that to determine if\n"
		"the line to be placed in buf has enough space ready for it.\n");

	printf("Please enter line of text: ");

	ungets("This pre-ungotten string should appear first. ");

	char c;
	int i = 0;
	while ((c = getch()) != '\n' && c != EOF) {
		outString[i++] = c;
	}
	outString[i++] = '\0';
	printf("\nPrinting received input from getch(): %s\n", outString);

	return EXIT_SUCCESS;
}

void ungets(char s[]) {
	if (strlen(s) + bufp >= BUFSIZE) {
		printf("Error: String too long to be ungotten.\n");
		return;
	} else {
		int i = strlen(s) - 1, j = 0;
		while (j < strlen(s)) {
			buf[bufp + j++] = s[i--];
		}
		bufp += strlen(s);
	}
}

int getch(void) { /* get a (possibly pushed-back) character */
	return (bufp > 0) ? buf[--bufp] : getchar();
}