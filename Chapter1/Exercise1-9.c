/** Write a program to copy its input to its output, replacing each string of one or more
  * blanks by a single blank. */

#include <stdio.h>
#include <stdbool.h>

main() {
	bool inChain = false;
	char c;

	printf("Please enter an input string:\n");

	while ((c = getchar()) != EOF) {
		if (inChain && c != ' ') {
			inChain = false;
			putchar(c);
		} else if (!inChain && c == ' ') {
			inChain = true;
			putchar(c);
		} else if (!inChain && c != ' ') {
			putchar(c);
		}
	}
}