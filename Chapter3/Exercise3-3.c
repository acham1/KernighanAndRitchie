/** Write a function expand(s1,s2) that expands shorthand notations like a-z in
  * the string s1 into the equivalent complete list abc...xyz in s2. Allow for 
  * letters of either case and digits, and be prepared to handle cases like a-b-c 
  * and a-z0-9 and -a-z. Arrange that a leading or trailing - is taken literally. */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#define MAX_LENGTH 50

char * expand(char s1[], char s2[]);
int populate(int i, int j, char s1[], char s2[]);					


int main() {
	printf("Write a function expand(s1,s2) that expands shorthand notations like a-z in\n"
		"the string s1 into the equivalent complete list abc...xyz in s2. Allow for\n"
		"letters of either case and digits, and be prepared to handle cases like a-b-c\n"
		"and a-z0-9 and -a-z. Arrange that a leading or trailing - is taken literally.\n");

	printf("\nEnter input string: ");

	char c, s1[MAX_LENGTH + 1], s2[26*MAX_LENGTH + 1]; 
	int i = 0;
	while(i < MAX_LENGTH && (c = getchar()) != '\n' && c != EOF) {
		s1[i++] = c;
	}
	s1[i] = '\0';

	printf("\nExpanded: %s\n", expand(s1, s2));
	return EXIT_SUCCESS;
}

char * expand(char s1[], char s2[]) {
	int i = 0, j = 0, totalChars = 0;
	char c;
	bool inWord = false;

	while ((c = s1[totalChars]) != '\0') {
		totalChars++;
	}

	while (i < totalChars) {
		c = s1[i];
		if (!inWord) {
			if (isspace(c)) {
				s2[j++] = c;
				i++;
			} else {
				inWord = true;
				if (i < totalChars-2) {
					if (s1[i+1] == '-' && (isspace(s1[i + 3]) || ispunct(s1[i+3]) || s1[i+3] == '\0') && s1[i+3] != '-') {
						j = populate(i, j, s1, s2);	
						i = i + 3;
						inWord = false;			
					} else {
						s2[j++] = c;
						i++;
					}
				} else {
					s2[j++] = c;
					i++;
				}
			}
		} else {
			if (isspace(c)) {
				inWord = false;
				s2[j++] = c;
				i++;
			} else {
				s2[j++] = c;
				i++;
			}
		}
	}
	s2[j] = '\0';
	return s2;
}

int populate(int i, int j, char s1[], char s2[]) {
	char c1 = s1[i], c2 = s1[i+2];
	int k = 0, inc;
	bool valid = false;
	if (c1 >= 'a' && c1 <= 'z' && c2 >= 'a' && c2 <= 'z') {
		valid = true;
	} else if (c1 >= 'A' && c1 <= 'Z' && c2 >= 'A' && c2 <= 'Z') {
		valid = true;		
	} else if (c1 >= '0' && c1 <= '9' && c2 >= '0' && c2 <= '9') {
		valid = true;
	}

	if (valid) {
		inc = (c1 > c2) ? -1:1;
		while (c1 != c2) {
			s2[j++] = c1;
			c1 += inc;
		}
		s2[j++] = c1++;
	} else {
		for (k = 0; k < 2; k++) {
			s2[j++] = s1[i++];
		}
	}
	return j;
}