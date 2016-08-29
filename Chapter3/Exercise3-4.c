/** In a two's complement number representation, our version of itoa does not handle the 
  * largest negative number, that is, the value of n equal to -(2wordsize-1). Explain why
  * not. Modify it to print that value correctly, regardless of the machine on which it
  * runs. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#define MAX_LENGTH 12

void itoa(int n, char s[]);
void reverse(char s[]);

int main() {
	printf("In a two's complement number representation, our version of itoa does not\n"
		"handle the largest negative number, that is, the value of n equal to\n"
		"-2^(wordsize-1). Explain why not. Modify it to print that value correctly,\n"
		"regardless of the machine on which it runs.\n");

	printf("\nIn a two's complement system, the largest negative number is\n"
		"-2^(wordsize-1). This corresponds to a bit pattern in which the only\n"
		"1-bit is at the far left position. The two's complement of this negative\n"
		"number is itself. The previous itoa implementaiton fails because it\n"
		"attempts to convert negative inputs into positive values first.\n"
		"In this new approach, we instead decrease the magnitude of the\n"
		"input integer by one, and start to print the modified integer.\n"
		"However, for the rightmost digit, the 1 value is added back before\n"
		"printing.\n");

	printf("INT_MIN: %d\n", INT_MIN);

	printf("Please enter number: ");
	char c, s1[MAX_LENGTH + 1]; 
	int i = 0;
	while(i < MAX_LENGTH && (c = getchar()) != '\n' && c != EOF) {
		s1[i++] = c;
	}
	s1[i] = '\0';
	printf("\nReceived number: %d\n", i = atoi(s1));
	itoa(i, s1);
	printf("Converting to string: %s\n", s1);

	return EXIT_SUCCESS;
}

/* itoa: convert n to characters in s */
void itoa(int n, char s[]) {
	int i, sign;
	bool isMin = false;
	if (n == INT_MIN) {
		isMin = true;
		n+= 1;
		printf("Received lowest number INT_MIN\n");
	}
	if ((sign = n) < 0) {/* record sign */
		n = -n;
	}
	/* make n positive */
	i = 0;
	do {
		/* generate digits in reverse order */
		if (isMin) {
			s[i++] = n % 10 + '1'; /* get next digit */
			isMin = false;
		} else {
			s[i++] = n % 10 + '0'; /* get next digit */
		}
	} while ((n /= 10) > 0);
	/* delete it */
	if (sign < 0) {
		s[i++] = '-';
	}
	s[i] = '\0';
	reverse(s);
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