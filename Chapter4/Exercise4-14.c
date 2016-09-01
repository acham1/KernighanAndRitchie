/** Define a macro swap(t,x,y) that interchanges two arguments of type t.
  * (Block structure will help.) */

#include <stdio.h>
#include <stdlib.h>
#define swap(t,x,y) {t SWAP_TEMP  = x; x = y; y = SWAP_TEMP; }

int main(void) {
	printf("Define a macro swap(t,x,y) that interchanges two arguments of type t.\n"
		"(Block structure will help.)\n");

	int a = 5, b = 10;
	printf("\nint a has value %d; int b has value %d\n", a, b);
	swap(int, a, b);
	printf("\nswapped: a = %d, b = %d\n", a, b);
	swap(int, a, b);
	printf("\nswapped again: a = %d, b = %d\n", a, b);

	return EXIT_SUCCESS;
}
