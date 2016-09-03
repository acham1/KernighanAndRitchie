/** Write versions of the library functions strncpy, strncat, and strncmp, which
operate on at most the first n characters of their argument strings. For example,
strncpy(s,t,n) copies at most n characters of t to s. Full descriptions are in Appendix B.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 100

char * mygetline(char * s, int limit);
char * mystrncopy(char * s, char * t, int n);
char * mystrncat(char * s, char * t, int n);
int mystrncmp(char * s, char * t, int n);
const int N = 5;

int main(void) {
	printf("Write versions of the library functions strncpy, strncat, and strncmp, which\n"
		"operate on at most the first n characters of their argument strings. For example,\n"
		"strncpy(s,t,n) copies at most n characters of t to s. Full descriptions are in\n"
		"Appendix B.\n");

	char example1[2 * MAXLEN + 1], example2[MAXLEN + 1], example3[MAXLEN + 1];
	printf("Please enter example1 text: ");
	mygetline(example1, MAXLEN);
	printf("Please enter example2 text: ");
	mygetline(example2, MAXLEN);

	printf("mystrncmp(example1, example2, %d): %d\n", N, mystrncmp(example1, example2, N));
	printf("mystrncopy(example3, example2, %d): %s\n", N, mystrncopy(example3, example2, N));
	printf("mystrncat(example1, example3, %d): %s\n", N, mystrncat(example1, example3, N));	

	return EXIT_SUCCESS;
}

/** cat from t to s **/
char * mystrncat(char * s, char * t, int n) {
	char * scopy = s + strlen(s);
	while (n-- > 0 && (*scopy++ = *t++) != '\0');
	*scopy = '\0';
	return s;
}

/** copy from t to s **/
char * mystrncopy(char * s, char * t, int n) {
	char * u = s;
	while (n-- > 0 && (*s++ = *t++) != '\0');
	return u;
}


int mystrncmp(char * s, char * t, int n) {
	int i = 0;

	while (n-- > 0) {
		if (s[i] != t[i]) {
			return (s[i] > t[i]) ? 1 : -1;
		} else if (s[i++] == '\0') {
			return 0;
		}
	}
	return 0;
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