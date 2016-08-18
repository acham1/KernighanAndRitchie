/** Write a function reverse(s) that reverses the character string s. Use it to 
  * write a program that reverses its input a line at a time. */

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#define MAXLINE 30

char mygetline(char line[], int maxlength);

void reverse(char line[], int maxlength);

int main() {
	printf("Write a function reverse(s) that reverses the character string s. Use \n"
		"it to write a program that reverses its input a line at a time.\n");

	printf("Enter text to be reversed (max length %d chars): \n", MAXLINE);
	char c, line[MAXLINE + 1];
	bool end = false;
	while (!end) {
		c = mygetline(line, MAXLINE);
		reverse(line, MAXLINE);
		if (line[0] != '\0') {
			printf("/Reversed  / %s\n", line);
		} else {
			printf("\n/Reversed  /\n");
		}
		if (c == EOF) {
			end = true;
		}
	}
	return EXIT_SUCCESS;
}

char mygetline(char line[], int maxlength) {
	int i = 0;
	char c;

	printf("/Enter Text/ ");
	while (i < maxlength && (c = getchar()) != '\n' && c != EOF) {
		line[i++] = c;
	}
	line[i] = '\0';
	while (c != '\n' && c != EOF) {
		c = getchar();
	}
	return c;
}

void reverse(char line[], int maxlength) {
	int i = 0, j = 0;
	char temp[maxlength];
	while (line[i] != '\0') {
		temp[j++] = line[i++];
	}
	j = 0;
	while (i > 0) {
		line[j++] = temp[--i]; 
	}
	line[j] = '\0';
}