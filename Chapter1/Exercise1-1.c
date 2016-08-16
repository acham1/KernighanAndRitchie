/** Run the "hello, world" program on your system. Experiment with leaving out 
  * parts of the program, to see what error messages you get. */

#include <stdio.h>
#include <stdlib.h>

int main() {
	printf("Run the \"hello, world\" program on your system. Experiment with leaving out\n"
		"parts of the program, to see what error messages you get.\n");

	printf("hello, ");
	printf("world");
	printf("\n");
	return EXIT_SUCCESS;
}