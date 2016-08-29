/** Write the function itob(n,s,b) that converts the integer n into a base b
  * character representation in the string s. In particular, itob(n,s,16) 
  * formats s as a hexadecimal integer in s. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#define MAX_LENGTH 100

char * itob(int n, char s[], int b);
void reverse(char s[]);

int main() {
	printf("Write the function itob(n,s,b) that converts the integer n into a base b\n"
		"character representation in the string s. In particular, itob(n,s,16)\n"
		"formats s as a hexadecimal integer in s.\n");

	printf("INT_MIN: %d\n", INT_MIN);

	printf("Please enter number n: ");
	char c, s1[MAX_LENGTH + 1]; 
	int i = 0, n, b;
	while(i < MAX_LENGTH && (c = getchar()) != '\n' && c != EOF) {
		s1[i++] = c;
	}
	s1[i] = '\0';
	n = atoi(s1);
	printf("\nReceived number n: %d\n", n);

	printf("Please enter base b: ");
	i = 0;
	while(i < MAX_LENGTH && (c = getchar()) != '\n' && c != EOF) {
		s1[i++] = c;
	}
	s1[i] = '\0';
	b = atoi(s1);
	printf("\nReceived number b: %d\n", b);

	b = (b < 0) ? -b : b;
	if (b <= 1) {
		printf("Invalid base.\n");
		return EXIT_FAILURE;
	}
	itob(n, s1, b);
	printf("Converting to base %d: %s\n", b, s1);


	return EXIT_SUCCESS;
}

char * itob(int n, char s[], int b) {
	int i = 0, sign;
	unsigned int us;
	unsigned int ub = (unsigned) b;
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