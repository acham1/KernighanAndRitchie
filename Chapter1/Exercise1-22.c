/** Write a program to ``fold'' long input lines into two or more shorter lines after
  * the last non-blank character that occurs before the n-th column of input. Make sure 
  * your program does something intelligent with very long lines, and if there are no
  * blanks or tabs before the specified column. */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

int w = 32; // max width of row
int n = 8; // number of positions per tab stop
char mygetline();

int main() {
	extern int w, n;
	printf("Write a program to ``fold'' long input lines into two or more shorter\n"
		"lines after the last non-blank character that occurs before the n-th\n"
		"column of input. Make sure your program does something intelligent with\n"
		"very long lines, and if there are no blanks or tabs before the specified column.\n");

	printf("\nEnter text to be folded (max row width %d; tab stops every %d slots):\n", w, n);
	char c = '0';
	while (c != EOF) {
		c = mygetline();
	}
	return EXIT_SUCCESS;
}

char mygetline() {
	char c;
	extern int n, w;
	int position = 0;
	bool wasSpace = true;

	while ((c = getchar()) != '\n' && c != EOF) {
		if (isspace(c)) {
			if ((position + (c == '\t') ?  n - 1 - position % n: 0) < w) {
				printf("%c", c);
			}
			wasSpace = true;
			position += ((c == '\t') ?  n - position % n: 1);
		} else {
			if (position < w) {
				printf("%c", c);
				position++;
			} else {
				if (!wasSpace) {
					printf("-\n%c", c);
					position = 1;
				} else {
					printf("\n%c", c);
					position = 1;
				}
			}
			wasSpace = false;
		}
	}
	printf("\n");
	return c;
}