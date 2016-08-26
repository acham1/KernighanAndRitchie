/** Write a function rightrot(x,n) that returns the value of the integer x rotated
 *  to the right by n positions. */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_LENGTH 9

int rightrot(unsigned int x, unsigned int n);

int main() {
	char c, x_string[MAX_LENGTH + 1], n_string[MAX_LENGTH + 1];
	int x, n, i = 0;

	printf("Write a function rightrot(x,n) that returns the value of the integer\n"
		"x rotated to the right by n positions.\n");

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

	printf("\nPlease enter number of positions n (max %d digits): ", MAX_LENGTH);
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

	printf("\nRotated number is: %d\n", rightrot(x, n));

	return EXIT_SUCCESS;
}

int rightrot(unsigned int x, unsigned int n) {
	unsigned int i = 0, begin = 0, temp = 0, numdigits = 0;

	temp = x;
	while (temp > 0) {
		temp /= 10;
		numdigits++;
	}

	if (numdigits == 0) {
		return 0;
	}

	n = n % numdigits;

	temp = 1;
	while (i++ < n) {
		begin = begin + temp * (x % 10);
		temp *= 10;
		x = x / 10;
	}

	for (i = 0; i < (numdigits - n); i++) {
		begin *= 10;
	}
	return begin + x;
}
