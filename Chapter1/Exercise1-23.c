/** Write a program to remove all comments from a C program. Don't forget to
  * handle quoted strings and character constants properly. C comments don't nest. */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char removeComments(); // function that reads text from console and removes comments

int main() {
	printf("/*Write a program to remove all comments from a C program. Don't forget to \n"
		"handle quoted strings and character constants properly. C comments don't nest.*/\n");

	char c = '0';
	while (c != EOF) {
		c = removeComments();
	}
	printf("\n");
	return EXIT_SUCCESS;
}

char removeComments() {
	bool inSingleQuote = false, inDoubleQuote = false, inLineComment = false, 
	inBlockComment = false, wasBackSlash = false, wasForwardSlash = false, wasStar = false;
	char c;
	while ((c = getchar()) != EOF) {
		if (inSingleQuote) {
			printf("%c",c);
			if (c == '\\' && !wasBackSlash) {
				wasBackSlash = true;
			} else if (c == '\'' && !wasBackSlash) {
				inSingleQuote = false;
			} else {
				wasBackSlash = wasForwardSlash = wasStar = false;
			}
			
		} else if (inDoubleQuote) {
			printf("%c", c);
			if (c == '\\' && !wasBackSlash) {
				wasBackSlash = true;
			} else if (c == '\"' && !wasBackSlash) {
				inDoubleQuote = false;
			} else {
				wasBackSlash = wasForwardSlash = wasStar = false;
			}

		} else if (inLineComment) {
			if (c == '\n') {
				inLineComment = false;
				printf("\n");
				wasBackSlash = wasForwardSlash = wasStar = false;
			}

		} else if (inBlockComment) {
			if (c == '*') {
				wasStar = true;
			} else if (c == '/' && wasStar) {
				inBlockComment = false;
			} else {
				wasBackSlash = wasForwardSlash = wasStar = false;
			}

		} else {
			if (c == '/' && wasForwardSlash) {
				inLineComment = true;
				wasBackSlash = wasForwardSlash = wasStar = false;
			} else if (c == '/' && !wasForwardSlash) {
				wasForwardSlash = true;
			} else if (c == '\'') {
				inSingleQuote = true;
				printf("\'");
				wasBackSlash = wasForwardSlash = wasStar = false;
			} else if (c == '\"') {
				inDoubleQuote = true;
				printf("\"");
				wasBackSlash = wasForwardSlash = wasStar = false;
			} else if (c == '*' && wasForwardSlash) {
				inBlockComment = true;
				wasBackSlash = wasForwardSlash = wasStar = false;
			} else if (c != '/' && wasForwardSlash && c != '*') {
				printf("/%c", c);
				wasBackSlash = wasForwardSlash = wasStar = false;
			} else {
				wasBackSlash = wasForwardSlash = wasStar = false;
				printf("%c", c);
			}
		}
	}
	return c;
}