/** Write a program to print all input lines that are longer than 80 characters. */

#include <stdio.h>
#include <stdlib.h>
#define MINLINE 80		/* maximum input line length */

int mygetline(char line[], int minline);
char printremainder();

int main() {
	printf("Write a program to print all input lines that are longer than %d characters.\n", MINLINE);
	
	int c;			/* current line length */
	char line[MINLINE + 1];	/* current input line */
	printf("Enter text; all input lines with length >%d (including newline) will be printed:\n", MINLINE);

	while ((c = mygetline(line, MINLINE))) {
		if (c == EOF) {
			break;
		} else if (c != -2 && c != '\n') {
			if (printremainder() == EOF) {
				break;
			}
		}
	}
	return(EXIT_SUCCESS);
}  

int mygetline(char line[], int minline) {
	int i = 0;
	char c;
	while ((c = getchar()) != '\n' && c != EOF && i < minline) {
		line[i] = c;
		i++;
	}
	line[i] = '\0';
	if (i == minline && c != EOF) {
		printf("%s%c", line, c);
		return c;
	} else if (c == EOF) {
		return c;
	} else {
		return -2;
	}
}

char printremainder() {
	char c;
	while ((c = getchar()) != '\n' && c != EOF) {
		printf("%c", c);
	}
	if (c == '\n') {
		printf("\n");
	}
	return c;
}