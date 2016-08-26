/** Our binary search makes two tests inside the loop, when one would suffice (at
  * the price of more tests outside.) Write a version with only one test inside the 
  * loop and measure the difference in run-time. */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define numElements 100
#define MAX_LENGTH 100

int binsearch1(int x, int v[], int n);
int binsearch2(int x, int v[], int n);

int main() {
	printf("Our binary search makes two tests inside the loop, when one would suffice\n"
		"(at the price of more tests outside.) Write a version with only one test\n"
		"inside the loop and measure the difference in run-time.\n");

	time_t t1, t2;
	int i, v[numElements], toFind;
	for (i = 0; i < numElements; i++) {
		v[i] = i;
	}

	char c, x_string[numElements + 1];
	i = 0;
	printf("\nEnter an integer from [0, %d]: ", numElements);
	while (i < MAX_LENGTH && (c = getchar()) != '\n' && c != EOF) {
		x_string[i++] = c;
		x_string[i] = '\0';
	}
	toFind = atoi(x_string);
	printf("Searching for number %d\n", toFind);

	time(&t1);
	i = binsearch1(toFind, v, numElements);
	time(&t2);
	printf("Original result: %d (time %f us)\n", i, 1000000. * difftime(t2, t1));

	time(&t1);
	i = binsearch2(toFind, v, numElements);
	time(&t2);
	printf("Original result: %d (time %f us)\n", i, 1000000. * difftime(t2, t1));

	return EXIT_SUCCESS;
}

int binsearch1(int x, int v[], int n) {
	int low, high, mid;
	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low+high)/2;
		if (x < v[mid]) {
			high = mid;
		} else if (x > v[mid]) {
			low = mid + 1;
		} else {
			return mid;
		}
	}
	return -1;
}

int binsearch2(int x, int v[], int n) {
	int low, high, mid;
	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low+high)/2;
		if (x < v[mid]) {
			high = mid;
		} else if (x > v[mid]) {
			low = mid + 1;
		} else {
			return mid;
		}
	}
	return -1;
}