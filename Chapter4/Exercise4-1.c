/** Write the function strindex(s,t) which returns the position of the rightmost
  * occurrence of t in s, or -1 if there is none. */

#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH 100

int strindex(char s[], char t);

int main() {
	char s[MAX_LENGTH + 1], c, s2[MAX_LENGTH + 1];
	int i = 0, j = 0;

	printf("Write the function strindex(s,t) which returns the position of the\n"
		"rightmost occurrence of t in s, or -1 if there is none.\n");

	printf("Please enter text <%d chars: ", MAX_LENGTH);
	while (i < MAX_LENGTH && (c = getchar()) != '\n' && c != EOF) {
		s[i++] = c;
	}
	while (c != '\n' && c != EOF) {
		c = getchar();
	}
	s[i] = '\0';

	printf("\nPlease enter a char to search for: ");
	while (j < 1 && (c = getchar()) != '\n' && c != EOF) {
		s2[j++] = c;
	}
	s2[j] = '\0';
	if (j == '\n' || j == EOF) {
		printf("Invalid.\n");
		return EXIT_FAILURE;
	}

	j = strindex(s, s2[0]);
	if (j == -1) {
		printf("\nUnfound.\n");
	} else {
		printf("\nFound at %d.\n", j);
	}

	return EXIT_SUCCESS;
}

int strindex(char s[], char t) {
	int i = 0;
	char c;

	while ((c = s[i]) != '\0' && c != t) {
		i++;
	}

	return (c == t) ? i : -1;
}