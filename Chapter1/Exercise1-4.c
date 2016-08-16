/** Write a program to print the corresponding Celsius to Fahrenheit table. */

#include <stdio.h>
#include <stdlib.h>

// print Celsius-Fahrenheit table for celsius = 0, 20, ... 300; floating-point version
int main() {
	printf("Write a program to print the corresponding Celsius to Fahrenheit table.\n");

	float celsius, fahr;
	float lower, upper, step;

	lower = 0;		// lower limit of temperature scale
	upper = 300;	// upper limit
	step = 20;		// step size

	printf("%s %s\n", "celsius", "fahr");

	for (celsius = lower; celsius <= upper; celsius += step) {
		fahr = celsius * (9.0/5.0) + 32.0;
		printf("%7.0f %5.1f\n", celsius, fahr);
	}
	return EXIT_SUCCESS;
}