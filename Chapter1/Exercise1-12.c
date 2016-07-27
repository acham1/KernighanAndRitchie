
#include <stdio.h>

#define IN 1 // inside a word
#define OUT 0 // outside a word


main() {
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
}