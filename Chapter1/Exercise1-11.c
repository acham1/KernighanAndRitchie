/** How would you test the word count program? What kinds of input are most likely to
  * uncover bugs if there are any? */

// The word count program could be tested with character sequences that contain exotic
// combinations of whitespace characters and other punctuation that are not commonly
// found adjacent to each other in typical language.

#include <stdlib.h>
#include <stdio.h>

int main() {
	printf("How would you test the word count program? What kinds of input are most\n"
		"likely to uncover bugs if there are any?\n");

	printf("\nThe word count program could be tested with character sequences \n"
		"that contain exotic combinations of whitespace characters and other\n"
		"punctuation that are not commonly found adjacent to each other in\n"
		"typical language.\n");
	return EXIT_SUCCESS;
}