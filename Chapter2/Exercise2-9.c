/** In a two's complement number system, x &= (x-1) deletes the rightmost 1-bit
  * in x. Explain why. Use this observation to write a faster version of bitcount. */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_LENGTH 9

int bitcount(unsigned x);

int main() {
	printf("In a two's complement number system, x &= (x-1) deletes the rightmost 1-bit\n"
		"in x. Explain why. Use this observation to write a faster version of bitcount.\n");

	printf("\nSuppose the rightmost 1-bit in x is at position p (position 0 is on the\n"
		"right). Then, in x - 1, all the bits at positions < p are set to 1, and the\n"
		"bit at position p is set to 0. All other bits are the same. Then when the &\n"
		"operator is used, the rightmost 1-bit is set to 0 because of the 0 at that\n"
		"position in x - 1. The bits to the right of p are still 0 after the & operation\n"
		"because they were 0 in the corresponding positions of x.\n");


	char c, x_string[MAX_LENGTH + 1];
	int x, i = 0;
	printf("\nPlease enter decimal number x (max %d digits): ", MAX_LENGTH);
	while (i < MAX_LENGTH && (c = getchar()) != '\n' && c != EOF) {
		if (!isspace(c) && (c >= '0' && c <= '9')) {
			x_string[i++] = c;
			x_string[i] = '\0';
		} else if (!isspace(c)) {
			printf("\nInvalid input.\n");
			return EXIT_FAILURE;
		}
	}
	x = atoi(x_string);

	printf("Number of 1-bits: %d\n", bitcount(x));
	return EXIT_SUCCESS;
}

/* bitcount: count 1 bits in x */
int bitcount(unsigned x) {
	int b = 0;
	while (x > 0) {
		++b;
		x &= (x - 1);
	}
	return b;
}
