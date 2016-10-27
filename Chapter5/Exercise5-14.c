/** Modify the sort program to handle a -r flag, which indicates sorting in reverse
  * (decreasing) order. Be sure that -r works with -n. */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXLINES 5000 /* max #lines to be sorted */
#define MAXLEN 500

char * lineptr[MAXLINES]; /* pointers to text lines */
char myheap[MAXLINES * (MAXLEN + 1)];
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void KRqsort(void *lineptr[], int left, int right, int (*comp)(void *, void *), int reverse);
int numcmp(const char *, const char *);

/* sort input lines */
int main(int argc, char *argv[]) {
	printf("Modify the sort program to handle a -r flag, which indicates sorting in reverse\n"
		"(decreasing) order. Be sure that -r works with -n.\n");
	int nlines; /* number of input lines read */
	int reverse = 0; /* 1 if reverse sort */
	int numeric = 0; /* 1 if numeric sort */

	while (argc-- > 1) {
		if (strcmp(argv[argc], "-n") == 0) {
			printf("numeric sort: ON\n");
			numeric = 1;
		} else if (strcmp(argv[argc], "-r") == 0) {
			printf("reverse sort: ON\n");
			reverse = 1;
		} else {
			printf("\nerror: did not recognize flag %s\n", argv[argc]);
		}
	}

	printf("\nPlease enter up to %d lines below:\n", MAXLINES);
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		KRqsort((void**) lineptr, 0, nlines-1,(int (*)(void*,void*)) (numeric ? numcmp : strcmp), reverse);
		writelines(lineptr, nlines);
		return EXIT_SUCCESS;
	} else {
		printf("input too big to sort\n");
		return EXIT_FAILURE;
	}
}

int readlines(char *lineptr[], int nlines) {
	int i = 0;
	char * last;
	lineptr[i] = myheap;
	while (!feof(stdin) && i < nlines && (last = fgets(lineptr[i], MAXLEN + 1, stdin))) {
		if (i++ < nlines) {
			lineptr[i] = lineptr[i-1] + strlen(lineptr[i-1]) + 1;
		} else {
			break;
		}
	}
	return feof(stdin) ? i : -1;
}

void writelines(char *lineptr[], int nlines) {
	int n = 0;
	while (n < nlines) {
		printf("Line %d: %s", n++, *lineptr++);
	}
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(const char *s1, const char *s2) {
	double v1, v2;
	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2) {
		return -1;
	} else if (v1 > v2) {
		return 1;
	} else {
		return 0;
	}
}

void swap(void *v[], int i, int j) {
	void *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/* qsort: sort v[left]...v[right] into increasing order */
void KRqsort(void *v[], int left, int right, int (*comp)(void *, void *), int reverse) {
	int i, last;
	int cmp_result;

	void swap(void *v[], int, int);
	if (left >= right) {
		return;
	} /* do nothing if array contains fewer than two elements */

	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++) {
		cmp_result = comp(v[i], v[left]);
		if ((!reverse && cmp_result < 0) || (reverse && cmp_result > 0)) {
			swap(v, ++last, i);
		}
	}
	swap(v, left, last);
	KRqsort(v, left, last-1, comp, reverse);
	KRqsort(v, last+1, right, comp, reverse);
}
