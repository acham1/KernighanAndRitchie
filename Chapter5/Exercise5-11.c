/** Modify the program entab and detab (written as exercises in Chapter 1) to
  * accept a list of tab stops as arguments. Use the default tab settings if 
  * there are no arguments. */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LEN 1000

void entab(char * string, char * argv[]);
void detab(char * string, char * argv[]);
int readstop(char * argv[]);
int getstop(char * argv[], int pos);

int main(int argc, char *argv[]) {
	printf("Modify the program entab and detab (written as exercises in Chapter 1) to\n"
		"accept a list of tab stops as arguments. Use the default tab settings if\n"
		"there are no arguments (every eigth position).\n");

	printf("\nEnter custom tab stops as space-separated integer list in command-line\n"
		"args, increasing order. Then enter text to be entabbed and detabbed below:\n");

	char s[MAX_LEN];
	while (printf("\nEnter text: "), !feof(stdin) && fgets(s, MAX_LEN, stdin) != NULL) {
		entab(s, argv);
		printf("Entabbed  : %s", s);
		detab(s, argv);
		printf("Detabbed  : %s", s);
	}
	return EXIT_SUCCESS;
}

int readstop(char * argv[]) {
	if (argv == NULL || *argv == NULL) {
		return -1;
	} else {
		return atoi(*argv);
	}
}

int getstop(char * argv[], int pos) {
	int stop;
	if ((stop = readstop(argv)) == -1) {
		return (pos / 8 * 8 + 8);
	} else {
		return stop;
	}
}

void entab(char * string, char * argv[]) {
	int inPos = 0, outPos = 0, virtualPos = 0, chain = 0;
	int nextstop = getstop(++argv, virtualPos);
	bool wasSpace = false;
	char c;

	while (virtualPos++, (c = string[inPos++]) != '\0') {
		switch(c) {
		case ' ':
			if (wasSpace) {
				chain++;
			} else {
				wasSpace = true;
				chain = 1;
			}

			while (virtualPos > nextstop) {
				nextstop = (*argv == NULL) ? getstop(NULL, virtualPos) : getstop(++argv, virtualPos);
			}

			if (virtualPos == nextstop) {
				string[outPos++] = '\t';
				chain = 0;
				wasSpace = false;
				nextstop = (*argv == NULL) ? getstop(NULL, virtualPos) : getstop(++argv, virtualPos);
			}

			break;

		case '\t':
			while (virtualPos >= nextstop) {
				nextstop = (*argv == NULL) ? getstop(NULL, virtualPos) : getstop(++argv, virtualPos);
			}

			chain = 0;
			virtualPos = nextstop;
			nextstop = (*argv == NULL) ? getstop(NULL, virtualPos) : getstop(++argv, virtualPos);

			string[outPos++] = '\t';
			wasSpace = false;

			break;

		default:
			if (wasSpace) {
				while (chain-- > 0) {
					string[outPos++] = ' ';
				}
			}
			wasSpace = false;
			string[outPos++] = c;

		}
	}
	string[outPos++] = '\0'; 
}

void detab(char * string, char * argv[]) {
	int inPos = 0, outPos = 0;
	int nextstop = getstop(++argv, outPos);
	char c, temp[MAX_LEN + 1];

	while ((c = string[inPos++]) != '\0') {
		if (c == '\t') {
			while (outPos >= nextstop) {
				nextstop = (*argv == NULL) ? getstop(NULL, outPos) : getstop(++argv, outPos);
			}
			while (outPos < nextstop) {
				temp[outPos++] = ' ';
			}
			nextstop = (*argv == NULL) ? getstop(NULL, outPos) : getstop(++argv, outPos);
		} else {
			temp[outPos++] = c;
		}
	}
	temp[outPos++] = '\0'; 
	strcpy(string, temp);
}