/** Write a program to determine the ranges of char, short, int, and long
  * variables, both signed and unsigned, by printing appropriate values from 
  * standard headers and by direct computation. Harder if you compute them: 
  * determine the ranges of the various floating-point types. */

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int main() {
printf("Write a program to determine the ranges of char, short, int, and long\n"
	"variables, both signed and unsigned, by printing appropriate values \n"
	"from standard headers and by direct computation. \n");
	
	printf("/* Standard Header Results */\n");
	printf("Type            %20s %20s\n", "Mininum", "Maximum");
	printf("Unsigned Char   %20u %20u\n", CHAR_MIN, UCHAR_MAX);
	printf("Signed   Char   %20d %20d\n", SCHAR_MIN, SCHAR_MAX);
	printf("Unsigned Short  %20u %20u\n", 0, USHRT_MAX);
	printf("Signed   Short  %20d %20d\n", SHRT_MIN, SHRT_MAX);
	printf("Unsigned Int    %20u %20u\n", 0, UINT_MAX);
	printf("Signed   Int    %20d %20d\n", INT_MIN, INT_MAX);
	printf("Unsigned Long   %20lu %20lu\n", (long) 0, ULONG_MAX);
	printf("Signed   Long   %20ld %20ld\n\n", LONG_MIN, LONG_MAX);

	return EXIT_SUCCESS;
}
