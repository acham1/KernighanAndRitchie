/** Adapt the ideas of printd to write a recursive version of itoa; that is, convert
  * an integer into a string by calling a recursive routine. */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXLEN 100

const int example = -9876;
char * itoa(char s[], int i);
char intString[MAXLEN + 1];

int main(void) {
	printf("Adapt the ideas of printd to write a recursive version of itoa; that is,\n"
		"convert an integer into a string by calling a recursive routine.\n");

	printf("Example integer: %d\n", example);
	itoa(intString, example);
	printf("Converting to string: %s\n", intString);

	return EXIT_SUCCESS;
}

char * itoa(char s[], int i) {
	int j = 0;
	char * s2;

	if (i < 0) {
		i = -i;
		s[j++] = '-';
	}
	
	if (i/10 > 0) {
		s2 = itoa(s + j, i/10);
	} else {
		s2 = s;
	}
	s2[0] = i % 10 + '0';
	s2[1] = '\0';
	return s2 + 1;
}