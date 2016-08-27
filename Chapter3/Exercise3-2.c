/** Write a function escape(s,t) that converts characters like newline and tab into
  * visible escape sequences like \n and \t as it copies the string t to s. Use a 
  * switch. Write a function for the other direction as well, converting escape 
  * sequences into the real characters. */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_LENGTH 100

// converts eligible chars in 'from' into visible escape sequences in 'to'
char *  escape(char to[], char from[]);
char * unescape(char to[], char from[]);

int main() {
	printf("Write a function escape(s,t) that converts characters like newline and tab\n"
		"into visible escape sequences like \\n and \\t as it copies the string t to s.\n"
		"Use a switch. Write a function for the other direction as well, converting\n"
		"escape sequences into the real characters.\n");

	printf("Enter input string <%d chars long: ", MAX_LENGTH);

	char c, s[2 * MAX_LENGTH + 1], t[MAX_LENGTH + 1];
	int i = 0;
	while (i < MAX_LENGTH && (c = getchar()) != '\n' && c != EOF) {
		t[i++] = c;
	}
	t[i] = '\0';

	printf("\nOutput                         : %s\n", escape(s, t));

	printf("\nRestored                       : %s\n", unescape(t, s));
	return EXIT_SUCCESS;
}

char *  escape(char to[], char from[]) {
	int i = 0, j = 0;
	char c;
	while ((c = from[i++]) != '\0') {
		switch(c) {
			case '\t':
				to[j++] = '\\';
				to[j++] = 't';
				break;
			case '\n':
				to[j++] = '\\';
				to[j++] = 'n';
				break;
			default:
				to[j++] = c;
		}
	}
	to[j] = '\0';
	return to;
}

char * unescape(char to[], char from[]) {
	int i = 0, j = 0;
	char c;
	bool wasSlash = false;
	while ((c = from[i++]) != '\0') {
		switch(c) {
			case '\\':
				wasSlash = true;
				to[j++] = '\\';
				break;
			case 't':
				if (wasSlash) {
					to[j - 1] = '\t';
				} else {
					to[j++] = c;
				}
				wasSlash = false;
				break;
			case 'n':
				if (wasSlash) {
					to[j - 1] = '\n';
				} else {
					to[j++] = c;
				}
				wasSlash = false;					
				break;
			default:
				to[j++] = c;
				wasSlash = false;
		}
	}
	to[j] = '\0';
	return to;
}