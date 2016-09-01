/** Write a recursive version of the function reverse(s), which reverses the
  * string s in place. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char example[] = "1234567890";
char * reverse(char s[]);
void reverse_helper(char * begin, char * end);

int main(void) {
	printf("Write a recursive version of the function reverse(s), which reverses the\n"
		"string s in place.\n");
	printf("Example string: %s\n", example);
	printf("Reversed: %s\n", reverse(example));

	return EXIT_SUCCESS;
}

char * reverse(char s[]) {
	char * begin = s;
	char * end = s + strlen(s) - 1;

	reverse_helper(begin, end);
	return s;
}

void reverse_helper(char * begin, char * end) {
	char c;
	if (end > begin) {
		c = *begin;
		*begin = *end;
		*end = c;
		reverse_helper(begin + 1, end - 1);
	}
}