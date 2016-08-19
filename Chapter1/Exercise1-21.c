/** Write a program entab that replaces strings of blanks by the minimum number
  * of tabs and blanks to achieve the same spacing. Use the same tab stops as 
  * for detab. When either a tab or a single blank would suffice to reach a tab 
  * stop, which should be given preference? */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int n = 8; // number of positions per tab stop
char mygetline();

int main() {
	printf("Write a program entab that replaces strings of blanks by the minimum\n"
	"number of tabs and blanks to achieve the same spacing. Use the same tab\n"
	"stops as for detab. When either a tab or a single blank would suffice to\n"
	"reach a tab stop, which should be given preference?\n");

	printf("\nTabs should be given preference. In this exercise, tab stops are\n"
		"set at every %dth position.\n", n);
	char c = '0';

	printf("Enter text to be entabbed:\n");
	while (c != EOF) {
		c = mygetline();
	}
	return EXIT_SUCCESS;
}

char mygetline() {
	extern int n;
	int currentPosition = 0, spaceBuffer = 0;
	char c;

	while ((c = getchar()) != '\n' && c != EOF) {
		currentPosition++;
		if (c != ' ') {
			while (spaceBuffer-- > 0) {
				printf(" ");
			}
			printf("%c", c);
		} else {
			spaceBuffer++;
			if (currentPosition % n == 0) {
				printf("\t");
				spaceBuffer = 0;
			}
		}
	}
	printf("\n");
	return c;
}