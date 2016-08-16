/** Experiment to find out what happens when printf's argument string contains
  * \c where c is some character not listed above. */

#include <stdio.h>
#include <stdlib.h>

int main() {
	printf("Experiment to find out what happens when printf's argument string contains\n"
		"\\c where c is some character not listed above.\n");

	printf("Printing the \" character.\n");
	printf("Printing the \\ character.\n");
	printf("Printing the \' character.\n");
	printf("Printing a tab \t.\n");
	printf("Printing a new line. \n");
	return EXIT_SUCCESS;
}
