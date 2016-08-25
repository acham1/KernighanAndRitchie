/** Write the function any(s1,s2), which returns the first location in a string s1
  * where any character from the string s2 occurs, or -1 if s1 contains no characters 
  * from s2. (The standard library function strpbrk does the same job but returns a 
  * pointer to the location.) */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAXLENGTH 50

int any(char s1[], char s2[]);

bool inString(char c, char s[]);

int main() {
	int i = 0, j = 0;
	char c, s1[MAXLENGTH + 1], s2[MAXLENGTH + 1];

	printf("Write the function any(s1,s2), which returns the first location in a string\n"
		"s1 where any character from the string s2 occurs, or -1 if s1 contains no\n"
		"characters from s2. (The standard library function strpbrk does the same\n"
		"job but returns a pointer to the location.)\n");

	printf("\nEnter string s1 (max length %d): ", MAXLENGTH);
	while (i < MAXLENGTH && (c = getchar()) != EOF && c != '\n') {
		s1[i++] = c;
	}
	s1[i] = '\0';

	printf("\nEnter string s2 (max length %d): ", MAXLENGTH);
	while (j < MAXLENGTH && (c = getchar()) != EOF && c != '\n') {
		s2[j++] = c;
	}
	s2[j] = '\0';

	printf("\nFirst location: %d\n", any(s1, s2));

	return EXIT_SUCCESS;
}

int any(char s1[], char s2[]) {
	int i = 0;
	while (s1[i] != '\0') {
		if (inString(s1[i], s2)) {
			return i;
		} else {
			i++;
		}
	}
	return -1;
}

bool inString(char c, char s[]) {
	int i = 0;
	while (s[i] != '\0') {
		if (c == s[i]) {
			return true;
		}
		++i;
	}
	return false;
}