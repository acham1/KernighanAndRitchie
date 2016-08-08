/** Rewrite the temperature conversion program of Section1.2 
  * to use a function for conversion. */

#include <stdio.h>

double fahr2celsius(double);

main() {
	int fahr;
	int lower = 0, upper = 300, step = 20;
	printf("Fahr   Celsius\n");
	for (fahr = lower; fahr <= upper; fahr += step) {
		printf("%5.1f  %5.1f\n", (double) fahr, fahr2celsius(fahr));
	}
	printf("\n");
}

double fahr2celsius(double fahr) {
	return (fahr - 32.0) * (5.0/9.0);
}