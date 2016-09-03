/** Rewrite appropriate programs from earlier chapters and exercises with pointers
  * instead of array indexing. Good possibilities include getline (Chapters 1 and 4),
  *  atoi, itoa, and their variants (Chapters 2, 3, and 4), reverse (Chapter 3), and 
  * strindex and getop (Chapter 4). */

#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 100

char * mygetline(char * s, int n);

int main(void) {
	printf("Rewrite appropriate programs from earlier chapters and exercises with pointers\n"
		"instead of array indexing. Good possibilities include getline (Chapters 1 and 4),\n"
		"atoi, itoa, and their variants (Chapters 2, 3, and 4), reverse (Chapter 3), and\n"
		"strindex and getop (Chapter 4).\n");

	printf("getline has been rewritten, please enter string: ");
	char example[MAXLEN + 1];
	mygetline(example, MAXLEN);
	printf("\nline was: %s\n", example);
	return EXIT_SUCCESS;
}

char * mygetline(char * s, int n) {
	char c;
	int i = 0;
	while (i < n && (c = getchar()) != '\n' && c != EOF) {
		*s++ = c;
	}
	*s = '\0';
	return s;
}