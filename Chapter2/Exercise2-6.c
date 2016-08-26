/** Write a function setbits(x,p,n,y) that returns x with the n bits that begin at
  * position p set to the rightmost n bits of y, leaving the other bits unchanged. */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_LENGTH 8


unsigned int setbits(unsigned int x, unsigned int p, unsigned int n, unsigned int y);

int main() {
	char c, x_string[MAX_LENGTH + 1], p_string[MAX_LENGTH + 1], n_string[MAX_LENGTH + 1], y_string[MAX_LENGTH + 1];
	int i = 0, x, p, n, y;

	printf("Write a function setbits(x,p,n,y) that returns x with the n bits that begin at\n"
		"position p set to the rightmost n bits of y, leaving the other bits unchanged.\n");

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

	while (c != '\n' && c != EOF) {
		c = getchar();
	}


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

	while (c != '\n' && c != EOF) {
		c = getchar();
	}

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
	i = 0;
	n = atoi(n_string);

	while (c != '\n' && c != EOF) {
		c = getchar();
	}

	printf("\nPlease enter position y (max %d digits): ", MAX_LENGTH);
	while (i < MAX_LENGTH && (c = getchar()) != '\n' && c != EOF) {
		if (!isspace(c) && (c >= '0' && c <= '9')) {
			y_string[i++] = c;
			y_string[i] = '\0';
		} else if (!isspace(c)) {
			printf("\nInvalid input.\n");
			return EXIT_FAILURE;
		}
	}
	i = 0;
	y = atoi(y_string);

	printf("\nModified number: %d\n", setbits(x, p, n, y));
	return EXIT_SUCCESS;
}

unsigned int setbits(unsigned int x, unsigned int p, unsigned int n, unsigned int y) {
/** Write a function setbits(x,p,n,y) that returns x with the n bits that begin at
  * position p set to the rightmost n bits of y, leaving the other bits unchanged. */
	int i = 0, maskp = 0, masky = 0;

	while (i++ < n) {
		maskp = (maskp << 1) + 1;
		masky = maskp;
	}
	maskp = maskp << (p - n + 1);
	masky = masky << (y - n + 1);
	x = x & ~(maskp);
	masky = (x & masky) << (p - y);
	return x + masky;
}
