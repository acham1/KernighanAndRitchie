/** Our getch and ungetch do not handle a pushed-back EOF correctly. Decide what 
  * their properties ought to be if an EOF is pushed back, then implement your design.*/

#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 1000
#define NUMBER '0'/* signal that a number was found */
#define MAXVAL 100 /* maximum depth of val stack */

int buf[BUFSIZE];
unsigned bufp = 0;

void ungetch(int c);
int getch(void);

int main(void) {
	printf("Our getch and ungetch do not handle a pushed-back EOF correctly. Decide what\n"
		"their properties ought to be if an EOF is pushed back, then implement your design.\n");

	printf("\nThe buffer needs to be an array of type that can hold the EOF character.\n"
		"In this implementation, the buffer will be an int array instead of char array.\n"
		"Furthermore, the argument and return types for ungetch and getch are now int.\n");

	printf("ungetch on EOF: ");
	ungetch(EOF);
	printf("done\n");
	printf("getch on EOF: ");
	if (getch() == EOF) {
		printf("done\n");
	} else {
		printf("failed\n");
	}

	return EXIT_SUCCESS;
}

void ungetch(int c) {
	if (bufp < BUFSIZE) {
		buf[bufp++] = c;
	} else {
		printf("error: buffer full\n");
	}
}

int getch(void) { /* get a (possibly pushed-back) character */
	if (bufp > 0) {
		return buf[--bufp];
	} else {
		return getchar();
	}
}