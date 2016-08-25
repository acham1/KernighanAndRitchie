/** Write a function invert(x,p,n) that returns x with the n bits that begin at position 
  * p inverted (i.e., 1 changed into 0 and vice versa), leaving the others unchanged. */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_LENGTH 8

int invert(unsigned int x, unsigned int p, unsigned int n);

int main() {
	char c, x_string[MAX_LENGTH + 1], p_string[MAX_LENGTH + 1], n_string[MAX_LENGTH + 1];
	int i = 0, x, p, n;

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
	i = 0;
	x = atoi(x_string);

	printf("\nPlease enter position p (max %d digits): ", MAX_LENGTH);
	while (i < MAX_LENGTH && (c = getchar()) != '\n' && c != EOF) {
		if (!isspace(c) && (c >= '0' && c <= '9')) {
			p_string[i++] = c;
			p_string[i] = '\0';
		} else if (!isspace(c)) {
			printf("\nInvalid input.\n");
			return EXIT_FAILURE;
		}
	}
	i = 0;
	p = atoi(p_string);

	printf("\nPlease enter number of bits n (max %d digits): ", MAX_LENGTH);
	while (i < MAX_LENGTH && (c = getchar()) != '\n' && c != EOF) {
		if (!isspace(c) && (c >= '0' && c <= '9')) {
			n_string[i++] = c;
			n_string[i] = '\0';
		} else if (!isspace(c)) {
			printf("\nInvalid input.\n");
			return EXIT_FAILURE;
		}
	}
	n = atoi(n_string);

	printf("Inverted number: %d\n", invert(x, p, n));
	return EXIT_SUCCESS;
}

int invert(unsigned int x, unsigned int p, unsigned int n) {
	int i = 0, mask1 = 0, mask2, mask3;

	while (i++ < n) {
		mask1 = (mask1 << 1) + 1;
	}
	mask1 = mask1 << (p - n + 1);
	mask3 = (mask2 = mask1);

	mask1 = mask1 & x;
	x = x & ~mask2;

	return x + (~mask1 & mask3);
}