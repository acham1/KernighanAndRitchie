/** Write a program to count blanks, tabs, and newlines. */

#include <stdio.h>

main() {
	int blanks, tabs, newlines;
	blanks = 0;
	tabs = 0;
	newlines = 0;

	char c;
	while ((c = getchar()) != EOF) {
		if (c == ' ') {
			blanks++;
		} else if (c == '\t') {
			tabs++;
		} else if (c == '\n') {
			newlines++;
		}
	}

	printf("Number of blanks: %d\n", blanks);
	printf("Number of tabs: %d\n", tabs);
	printf("Number of newlines: %d\n", newlines);
}