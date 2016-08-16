/** Write a program to print a histogram of the frequencies of different characters
  * in its input. */

#include <stdio.h>
#include <stdlib.h>

int main() {
	printf("Write a program to print a histogram of the frequencies of different\n"
		"characters in its input. Only alphanumerical characters are counted.\n");

	char c;
	int i, j;
	int numbers[10] = {0};
	int upperCaseLetters[26] = {0};
	int lowerCaseLetters[26] = {0};

	while ((c = getchar()) != EOF) {
		if (c <= 'Z' && c >= 'A') {
			upperCaseLetters[c - 'A']++;
		} else if (c <= 'z' && c >= 'a') {
			lowerCaseLetters[c - 'a']++;
			numbers[c - '0']++;
		}
	}

	printf("Upper Case Letter Histogram:\n");
	for (i = 0; i < 26; i++) {
		printf("%2c: ", 'A' + i);
		for (j = 0; j < upperCaseLetters[i]; j++) {
			printf("*");
		}
		printf("\n");
	}

	printf("Lower Case Letter Histogram:\n");
	for (i = 0; i < 26; i++) {
		printf("%2c: ", 'a' + i);
		for (j = 0; j < lowerCaseLetters[i]; j++) {
			printf("*");
		}
		printf("\n");
	}


	printf("Number Histogram:\n");	
	for (i = 0; i < 10; i++) {
		printf("%2c: ", '0' + i);
		for (j = 0; j < numbers[i]; j++) {
			printf("*");
		}
		printf("\n");
	}

	printf("\n");
	return EXIT_SUCCESS;
}