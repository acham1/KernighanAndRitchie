/** Write a program to remove trailing blanks and tabs from
  * each line of input, and to delete entirely blank lines. */

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#define MAXLINE 30

char mygetline(char line[], int maxlength);

/** copies chars from from[] to to[], starting at index startingpos in to[] */
void copy(char from[], char to[], int startingpos);

main() {
	printf("Enter text (max length %d chars); trailing whitespace "
		"will be removed:\n", MAXLINE);

	char c, line[MAXLINE + 1];
	int i = 0;
	bool end = false;
	while (!end) {
		c = mygetline(line, MAXLINE);
		if (c == EOF) {
			end = true;
		}
		if (line[0] != '\0') {
			printf("%s/**Line%2d**/ %s /**End**/\n", (end) ? "\n" : "", i++, line);
		} else if (end) {
			printf("\n");
		}
	}

	return EXIT_SUCCESS;
}

char mygetline(char line[], int maxlength) {
	int i = 0, j = 0;
	char c, temp[maxlength + 1];

	printf("/Enter Text/ ");
	while ((i + j) < maxlength && (c = getchar()) != '\n' && c != EOF) {
		temp[j++] = c;
		if (!isspace(c)) {
			temp[j] = '\0';
			copy(temp, line, i);
			i += j;
			j = 0;
		}
	}
	line[i] = '\0';
	while (c != '\n' && c != EOF) {
		c = getchar();
	}
	return c;
}

void copy(char from[], char to[], int startingpos) {
	int i = 0;
	while (from[i] != '\0') {
		to[startingpos++] = from[i++];
	}
}
