/** Rewrite the function lower, which converts upper case letters to lower case,
  * with a conditional expression instead of if-else. */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_LENGTH 100

int lower(int c);

int main() {
	printf("Rewrite the function lower, which converts upper case letters to lower\n"
		"case, with a conditional expression instead of if-else.\n");

	char c, x_string[MAX_LENGTH + 1];
	int i = 0;
	printf("\nPlease enter string (max %d digits): ", MAX_LENGTH);
	while (i < MAX_LENGTH && (c = getchar()) != '\n' && c != EOF) {
		x_string[i++] = c;
		x_string[i] = '\0';
	}
	i = 0;

	printf("Lower case string: ");
	while (x_string[i] != '\0') {
		printf("%c", lower(x_string[i++]));
	}
	printf("\n");
	return EXIT_SUCCESS;
}

/* lower: convert c to lower case; ASCII only */
int lower(int c) {
	return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}
