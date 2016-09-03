/** Write the function strend(s,t), which returns 1 if the string t occurs at the
  * end of the string s, and zero otherwise. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLINE 100

char * mygetline(char * s, int n);
int strend(char * s, char * t);

int main(void) {
	char example1[MAXLINE + 1];
	char example2[MAXLINE + 1];
	char example3[MAXLINE + 1];
	printf("Write the function strend(s,t), which returns 1 if the string t occurs at the\n"
		"end of the string s, and zero otherwise.\n");

	printf("\nPlease enter string 1: ");
	mygetline(example1, MAXLINE);
	printf("\nPlease enter string 2 (not the end of string 1): ");
	mygetline(example2, MAXLINE);
	printf("\nPlease enter string 3 (is the end of string 1): ");
	mygetline(example3, MAXLINE);

	printf("strend(example1, example2): %d\n", strend(example1, example2));
	printf("strend(example1, example3): %d\n", strend(example1, example3));
	return EXIT_SUCCESS;
}

int strend(char * s, char * t) {
	int i = strlen(s), j = strlen(t);
	if (j > i) {
		return 0;
	} else {
		s += (i - j);
		return (!strcmp(s, t) ? 1 : 0);
	}
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

