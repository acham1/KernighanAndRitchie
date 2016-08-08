/** Write a program to print a histogram of the lengths of words in its input. It is easy
  * to draw the histogram with the bars horizontal; a vertical orientation is more
  * challenging. */

#include <stdio.h>

#define MAX_LEN 20	// maximum recorded word length
#define IN 0	// inside a word
#define OUT 1	// outside a word

main() {
	char c;
	int tally[MAX_LEN + 1] = {0};
	int currentLength = 0;
	int state = OUT;

	printf("Note: any input words of greater than length %d will be counted \nas a length "
		 "%d word.\n", MAX_LEN, MAX_LEN);
	printf("Enter input text here: ");
	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\n' || c == '\t') {
			if (state == IN) {
				tally[currentLength]++;
				currentLength = 0;
				state = OUT;
			}
		} else {
			currentLength < MAX_LEN ? currentLength++ : 0;
			if (state == OUT) {
				state = IN;
			}
		}
	}

	if (state == IN) {
		tally[currentLength]++;
	}

	printf("\nWord length histogram: \n");
	int i, j;
	for (i = 1; i <= MAX_LEN; i++) {
		printf("%2d: ", i);
		for (j = 0; j < tally[i]; j++) {
			printf("*");
		}
		printf("\n");
	}
}