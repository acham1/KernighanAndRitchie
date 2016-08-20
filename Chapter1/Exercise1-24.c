/** Write a program to check a C program for rudimentary syntax errors like
  * unmatched parentheses, brackets and braces. Don't forget about quotes, both 
  * single and double, escape sequences, and comments. (This program is hard if
  * you do it in full generality.) */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool inSingleQuote = false, inDoubleQuote = false, inLineComment = false, 
		inBlockComment = false, inParenthesis = false, inBracket = false, inBrace = false,
		wasBackSlash = false, wasForwardSlash = false, wasStar = false;

char proofread();

int main() {
	printf("Write a program to check a C program for rudimentary syntax errors like \n"
		"unmatched parentheses, brackets and braces. Don't forget about quotes, both \n"
		"single and double, escape sequences, and comments. (This program is hard if \n"
		"you do it in full generality.)\n");

	proofread();

	if (inSingleQuote) {

	} else if (inDoubleQuote) {
		printf("Unbalanced double quote.\n");

	} else if (inBlockComment) {
		printf("Unbalanced block comment.\n");

	} else if (inParenthesis) {
		printf("Unbalanced parenthesis.\n");

	} else if (inBracket) {
		printf("Unbalanced bracket.\n");

	} else if (inBrace) {
		printf("Unbalanced brace.\n");

	} else {
		printf("No unbalanced wrappers found.\n");
	}
	return EXIT_SUCCESS;
}

char proofread() {
	extern bool inSingleQuote, inDoubleQuote, inLineComment, inBlockComment, inParenthesis, 
		inBracket, inBrace, wasBackSlash, wasForwardSlash, wasStar;
	char c;
	while ((c = getchar()) != EOF) {
		if (inSingleQuote) {
			if (c == '\\' && !wasBackSlash) {
				wasBackSlash = true;
			} else if (c == '\'' && !wasBackSlash) {
				inSingleQuote = false;
			} else {
				wasBackSlash = wasForwardSlash = wasStar = false;
			}
			
		} else if (inDoubleQuote) {
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

		} else if (inBracket) {
			if (c == ']') {
				inBracket = false;
			} else {
				wasBackSlash = wasForwardSlash = wasStar = false;
			}
 			
		} else if (inBrace) {
			if (c == '}') {
				inBrace = false;
			} else {
				wasBackSlash = wasForwardSlash = wasStar = false;
			}

		} else if (inParenthesis) {
			if (c == ')') {
				inParenthesis = false;
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
				wasBackSlash = wasForwardSlash = wasStar = false;
			} else if (c == '\"') {
				inDoubleQuote = true;
				wasBackSlash = wasForwardSlash = wasStar = false;
			} else if (c == '*' && wasForwardSlash) {
				inBlockComment = true;
				wasBackSlash = wasForwardSlash = wasStar = false;
			} else if (c == '(') {
				inParenthesis = true;
			} else if (c == '[') {
				inBracket = true;
			} else if (c == '{') {
				inBrace = true;
			} else if (c != '/' && wasForwardSlash && c != '*') {
				wasBackSlash = wasForwardSlash = wasStar = false;
			} else {
				wasBackSlash = wasForwardSlash = wasStar = false;
			}
		}
	}
	return c;
}