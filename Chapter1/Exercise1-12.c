/** Write a program that prints its input one word per line. */

#include <stdio.h>
#include <stdlib.h>

#define IN 1 // inside a word
#define OUT 0 // outside a word


int main() {
	printf("Write a program that prints its input one word per line.\n");

	char c;
	int state = OUT;

	printf("Please enter an input string:\n");
	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\t' || c == '\n') {
			if (state == IN) {
				state = OUT;
				putchar('\n');
			}
		} else {
			if (state == OUT) {
				state = IN;
			}
			putchar(c);
		}
	}
	return EXIT_SUCCESS;
}