/** Extend atof to handle scientific notation of the form 123.45e-6 where a floating-
  * point number may be followed by e or E and an optionally signed exponent. */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_LENGTH 20

double myAtof(char s[]);

int main() {
	char s[MAX_LENGTH + 1], c;
	int i = 0;

	printf("Extend atof to handle scientific notation of the form 123.45e-6 where a\n"
		"floating-point number may be followed by e or E and an optionally signed\n"
		"exponent.\n");

	printf("\nPlease enter floating point number of the form 123.45e-6: ");
	while (i < MAX_LENGTH && (c = getchar()) != '\n' && c != EOF) {
		s[i++] = c;
	}
	while (c != '\n' && c != EOF) {
		c = getchar();
	}
	s[i] = '\0';

	printf("\nConverting to float: %20.10f\n", myAtof(s));

	return EXIT_SUCCESS;
}

double myAtof(char s[]) {
	double val, power, multiplier;
	int i, e, sign;
	for (i = 0; isspace(s[i]); i++) /* skip white space */;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-') {
		i++;
	}
	for (val = 0.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
	}
	if (s[i] == '.') {
		i++;
	}
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10;
	}
	if (s[i] == 'e') {
		i++;
		multiplier = (s[i] == '-') ? 0.1 : 10.0;
//		printf("%d\n", atoi(&s[i]));
		e = atoi((s[i] == '-' ? &s[i + 1] : &s[i]));
		for (i = 0; i < e; i++) {
			val *= multiplier;
		}		
	}
	return sign * val / power;
}