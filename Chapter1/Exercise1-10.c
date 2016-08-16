/** Write a program to copy its input to its output, replacing each tab by \t, each 
 *  backspace by \b, and each backslash by \\. This makes tabs and backspaces visible
 *  in an unambiguous way. */

#include <stdio.h>
#include <stdlib.h>

 int main() {
 	printf("Write a program to copy its input to output, replacing each tab by \\t,\n"
 		"each backspace by \\b, and each backslash by \\\\. This makes tabs and \n"
 		"backspaces visible in an unambiguous way.\n");
 	printf("Please enter an input string:\n");

 	char c;
 	while ((c = getchar()) != EOF) {
 		if (c == '\t') {
 			printf("\\t");
 		} else if (c == '\b') {
 			printf("\\b");
 		} else if (c == '\\') {
 			printf("\\\\");
 		} else {
 			putchar(c);
 		}
 	}
 	return EXIT_SUCCESS;
 }