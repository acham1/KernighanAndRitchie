/** Revise the main routine of the longest-line program so
  * it will correctly print the length of arbitrary long input
  * lines, and as much as possible of the text. */

#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 30		/* maximum input line length */

int mygetline(char line[], int maxline);
void copy(char from[], char to[]);

int main() {
	printf("Revise the main routine of the longest-line program so it will\n"
		"correctly print the length of arbitrary long input lines, and as much\n"
		"as possible of the text.\n");

	int len;			/* current line length */
	int max;			/* maximum length seen so far */
	char line[MAXLINE + 1];	/* current input line */
	char longest[MAXLINE + 1]; /* longest line saved here */

	printf("Enter text to find greatest line length (newline included; max printable length is %d):\n", MAXLINE);

	max = 0;
	while ((len = mygetline(line, MAXLINE)) > 0) {
		if (len > max) {
			max = len;
			copy(line, longest);
		}
	}
	if (max > 0) {		/* there was a line */
		printf("Longest line (length %d) received was:\n", max);
		printf("%s\n", longest);
	} else {
		printf("No line received.\n");
	}
	return EXIT_SUCCESS;
}  

int mygetline(char line[], int maxline) {
	int i = 0;
	char c;
	while ((c = getchar()) != '\n' && c != EOF) {
		if (i < maxline) {
			line[i] = c;
		}
		i++;
	}
	if (c == '\n') {
		if (i < maxline) {
			line[i] = c;
		}
		i++;
	}
	line[i] = '\0';
	return i;
}

void copy(char from[], char to[]) {
	int i = 0;
	while((to[i] = from[i]) != '\0') {
		i++;
	}
	to[i] = '\0';
}