/** Write a version of itoa that accepts three arguments instead of two. The third
  * argument is a minimum field width; the converted number must be padded with blanks
  * on the left if necessary to make it wide enough. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#define MAX_LENGTH 100

char * itoa(int n, char s[], int w);
void reverse(char s[]);

int main() {
	printf("Write a version of itoa that accepts three arguments instead of two. The third\n"
		"argument is a minimum field width; the converted number must be padded with blanks\n"
		"on the left if necessary to make it wide enough. \n");

	printf("INT_MIN: %d\n", INT_MIN);

	printf("Please enter number n: ");
	char c, s1[MAX_LENGTH + 1]; 
	int i = 0, n, w;
	while(i < MAX_LENGTH && (c = getchar()) != '\n' && c != EOF) {
		s1[i++] = c;
	}
	s1[i] = '\0';
	n = atoi(s1);
	printf("\nReceived number n: %d\n", n);

	printf("Please enter minimum field width w: ");
	i = 0;
	while(i < MAX_LENGTH && (c = getchar()) != '\n' && c != EOF) {
		s1[i++] = c;
	}
	s1[i] = '\0';
	w = atoi(s1);
	printf("\nReceived width w: %d\n", w);

	itoa(n, s1, w);
	printf("Converting int to string: %s\n", itoa(n, s1, w));


	return EXIT_SUCCESS;
}

/* itoa: convert n to characters in s */
char * itoa(int n, char s[], int w) {
	int i = 0, sign;
	unsigned int us;
	unsigned int ub = 10;
	if ((sign = n) < 0) {/* record sign */
		us = (unsigned) -n;
	} else {
		us = (unsigned) n;
	}
	/* make n positive */

	do {
		/* generate digits in reverse order */
		s[i++] = us % ub + '0'; /* get next digit */
	} while ((us /= ub) > 0);
	/* delete it */
	if (sign < 0) {
		s[i++] = '-';
	}
	while (i < w && i < MAX_LENGTH) {
		s[i++] = ' ';
	}
	s[i] = '\0';
	reverse(s);
	return s;
}

/* reverse: reverse string s in place */
void reverse(char s[]) {
	int c, i, j;
	for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}