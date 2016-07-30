/** Write a program to print a histogram of the lengths of words in its input. It is easy
  * to draw the histogram with the bars horizontal; a vertical orientation is more
  * challenging. */

#include <stdio.h>

#define MAX_LEN 20	// maximum recorded word length
#define IN 0	// inside a word
#define OUT 1	// outside a word

main() {
	char c;
	int tally[MAX_LEN + 1];
	int currentLength = 0;

	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\n' || c == '\t') {
			
		} else {

		}
	}
}