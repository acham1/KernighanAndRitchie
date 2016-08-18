/** Write a program detab that replaces tabs in the input with the proper number
  * off blanks to space to the next tab stop. Assume a fixed set of tab stops, 
  * say every n columns. Should n be a variable or a symbolic parameter? */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int n = 8; // number of positions per tab stop
char mygetline();

int main() {
	printf("Write a program detab that replaces tabs in the input with the proper \n"
		"number off blanks to space to the next tab stop. Assume a fixed set of tab \n"
		"stops, say every n columns. Should n be a variable or a symbolic parameter?\n");

	printf("\nIn this exercise, n=8 will be an exernal variable.\n");
	char c = '0';

	printf("Enter text to be detabbed:\n");
	while (c != EOF) {
		c = mygetline();
	}
	return EXIT_SUCCESS;
}

char mygetline() {
	extern int n;
	int i = 0;
	char c;

	while ((c = getchar()) != '\n' && c != EOF) {
		if (c != '\t') {
			printf("%c", c);
			i++;
		} else {
			int j = 0, k = n - i % n;
			while (j++ < k) {
				printf(" ");
				i++;
			}
		}
	}
	printf("\n");
	return c;
}