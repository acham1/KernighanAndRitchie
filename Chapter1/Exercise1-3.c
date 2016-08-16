/** Modify the temperature conversion program to print a heading above the table */

#include <stdio.h>
#include <stdlib.h>

// print Fahrenheit-Celsius table for fahr = 0, 20, ..., 300; floating-point version
int main() {
	printf("Modify the temperature conversion program to print a heading above the table.\n");

	float fahr, celsius;
	float lower, upper, step;

	lower = 0;		// lower limit of temperature scale
	upper = 300;	// upper limit
	step = 20;		// step size

	printf("%4s %s\n", "fahr", "celsius");

	fahr = lower;
	while (fahr <= upper) {
		celsius = (5.0/9.0) * (fahr - 32.0);
		printf("%4.0f %6.1f\n", fahr, celsius);
		fahr = fahr + step;
	}
	return EXIT_SUCCESS;
}