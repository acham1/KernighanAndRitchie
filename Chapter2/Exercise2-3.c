/** Write a function htoi(s), which converts a string of hexadecimal digits (including
  * an optional 0x or 0X) into its equivalent integer value. The allowable digits are 0
  * through 9, a through f, and A through F. */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#define MAX_HEX_DIGITS 6

int htoi(char s[]);

int main() {
	printf("Write a function htoi(s), which converts a string of hexadecimal digits\n"
		"(including an optional 0x or 0X) into its equivalent integer value.\n"
		"The allowable digits are 0 through 9, a through f, and A through F.\n");

	printf("\nEnter a <%d digit hexadecimal number with optional 0x or 0X lead: ", MAX_HEX_DIGITS);

	int i = 0;
	char c = '\0', s[MAX_HEX_DIGITS + 3];
	bool started = false;
	while (i < MAX_HEX_DIGITS + 2) {
		if (!started) {
			while (isspace(c = getchar())) { }
			if (c == EOF || c == '\n') {
				printf("No input found.\n");
				return EXIT_FAILURE;
			} else {
				s[i++] = c;
				started = true;
			}
		} else {
			c = getchar();
			if (c == EOF || c == '\n') {
				s[i++] = '\0';
				break;
			} else {
				s[i++] = c;
			}			
		}
	}

	printf("\nReceived input: %s\n", s);
	printf("Decimal value: %d\n", htoi(s));
	return EXIT_SUCCESS;
}

int htoi(char s[]) {
	int i = 0, out = 0;
	char c;
	bool firstIsZero = false;
	while ((c = s[i]) != '\0') {
		if (i == 0 && c == '0') {
			firstIsZero = true;
		} else if (i == 1 && (c == 'x' || c == 'X') && firstIsZero) {
		} else if (i == 1 && !(c == 'x' || c == 'X') && firstIsZero) {
			printf("Incorrect format | Reporting as ");
			return out;
		} else if (c >= 'a' && c <= 'f') {
				out = out * 16 + c - 'a' + 10;
		} else if(c >= 'A' && c <= 'F') {
				out = out * 16 + c - 'A' + 10;
		} else if (c >= '0' && c <= '9') {
				out = out * 16 + c - '0';
		} else {
			printf("Incorrect format | Reporting as ");
			return out;
		}
		++i;
	}
	return out;
}