/** Rewrite readlines to store lines in an array supplied by main, rather than
  * calling alloc to maintain storage. How much faster is the program? */

#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 100
#define MAXLINES 100

int readlines(char (* s)[MAXLEN + 1], int);
int mygetline(char *, int);
char * mystrncpy(char *, char *, int);

int main(void) {
	printf("Rewrite readlines to store lines in an array supplied by main, rather than\n"
		"calling alloc to maintain storage. How much faster is the program?\n");

	printf("Please enter <=%d lines, <=%d chars each: ", MAXLINES, MAXLEN);

	int k = 0;
	char arrayOfStrings[MAXLINES][MAXLEN + 1];
	int l = readlines(arrayOfStrings, MAXLINES);

	while (l-- > 0) {
		printf("line %d: %s\n", k, arrayOfStrings[k]);
		k++;
	}
	return EXIT_SUCCESS;
}

/** copy from t to s **/
char * mystrncpy(char * s, char * t, int n) {
	char * u = s;
	while (n-- > 0 && (*s++ = *t++) != '\0');
	return u;
}

int readlines(char (* lineptr)[MAXLEN + 1], int maxlines) {
	int len, nlines = 0;
	char s[MAXLEN + 1];
	
	while ((len = mygetline(s, MAXLEN)) > 0) {
		if (nlines >= maxlines) {
			return -1;
		} else {
			s[len-1] = '\0'; /* delete newline */
			mystrncpy(lineptr[nlines++], s, MAXLEN + 1);
		}
	}
	return nlines;
}

int mygetline(char * s, int n) {
	char c;
	int i = 0;
	while (i < n && (c = getchar()) != '\n' && c != EOF) {
		*s++ = c;
		i++;
	}
	if (c == '\n') {
		*s++ = '\n';
		i++;
	}
	*s = '\0';
	return i;
}