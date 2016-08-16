/** Verify that the expression getchar() != EOF is 0 or 1. */

#include <stdio.h>
#include <stdlib.h>

int main() {
	printf("Verify that the expression getchar() != EOF is 0 or 1.\n");
	printf("Please provide input chars:\n");
	printf("Expression getchar() != EOF evaluates to %d.\n", getchar() != EOF);	
	return EXIT_SUCCESS;
}