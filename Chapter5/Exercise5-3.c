/** Write a pointer version of the function strcat that we showed in Chapter 2:
  * strcat(s,t) copies the string t to the end of s. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 100

char * mystrcat(char * s, char * t);
char * mygetline(char * s, int n);

int main(void) {
	printf("Write a pointer version of the function strcat that we showed in Chapter 2:"
		"\nstrcat(s,t) copies the string t to the end of s.");

	char example1[2 * MAX_LEN + 1], example2[MAX_LEN + 1];
	printf("\nPlease enter line 1: ");
	mygetline(example1, MAX_LEN);
	printf("\nPlease enter line 2: ");
	mygetline(example2, MAX_LEN);
	printf("Concatenated line is: %s\n", mystrcat(example1, example2));

	return EXIT_SUCCESS;
}

char * mystrcat(char * s, char * t) {
	char * scopy = s + strlen(s);
	while ((*scopy++ = *t++) != '\0');
	return s;
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