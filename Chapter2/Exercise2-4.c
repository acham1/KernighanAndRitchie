/** Write an alternative version of squeeze(s1,s2) that deletes each character in
  * s1 that matches any character in the string s2. */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXLENGTH 100

void squeeze(char s1[], char s2[]);
bool inString(char c, char s[]);

int main() {
	char c, s1[MAXLENGTH + 1], s2[MAXLENGTH + 1];
	int i = 0, j = 0;

	printf("Write an alternative version of squeeze(s1,s2) that deletes each character in\n"
		"s1 that matches any character in the string s2.\n");
	
	printf("Enter string s1 (max length %d): ", MAXLENGTH);
	while (i < MAXLENGTH && (c = getchar()) != EOF && c != '\n') {
		s1[i++] = c;
	}
	s1[i] = '\0';		

	printf("\nEnter string s2 (max length %d): ", MAXLENGTH);
	while (i < MAXLENGTH && (c = getchar()) != EOF && c != '\n') {
		s2[j++] = c;
	}
	s2[i] = '\0';

	squeeze(s1, s2);
	printf("\nOutput string: %s\n", s1);

	return EXIT_SUCCESS;
}

void squeeze(char s1[], char s2[]) {
	int i = 0, j = 0;

	while (s1[i] != '\0') {
		if (!inString(s1[i], s2)) {
			s1[j++] = s1[i];
		}
		++i; 
	}
	s1[j] = '\0';
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