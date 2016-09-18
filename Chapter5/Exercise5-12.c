/** Extend entab and detab to accept the shorthand entab -m +n to mean tab stops every n 
  * columns, starting at column m. Choose convenient (for the user) default behavior. */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LEN 1000

void entab(char * string, char * argv[]);
void detab(char * string, char * argv[]);
void mnEntab(char * string, int m, int n);
void mnDetab(char * string, int m, int n);
int readstop(char * argv[]);
int getstop(char * argv[], int pos);
int mnGetstop(int pos, int m, int n);

int main(int argc, char *argv[]) {
	printf("Extend entab and detab to accept the shorthand entab -m +n to mean tab stops every\n"
  		"n columns, starting at column m. Choose convenient (for the user) default behavior.\n");

	printf("\nEnter custom tab stops as space-separated integer list in command-line\n"
		"args, increasing order. **OR** Use command=line arguments -m +n to set tabs\n"
		"every n columns, starting at column n.\n");

	bool mnStyle = false;
	if (argc >= 3 && argv[1][0] == '-' && argv[2][0] == '+') {
		if (atoi(argv[2] + 1) >= 0 ) {
			mnStyle = true;
		} else {
			printf("Invalid command-line argument \"%s\".\n", argv[2]);
			return EXIT_SUCCESS;
		}
	}

	char s[MAX_LEN];
	if (!mnStyle) {
		while (printf("\nEnter text: "), !feof(stdin) && fgets(s, MAX_LEN, stdin) != NULL) {
			entab(s, argv);
			printf("Entabbed  : %s", s);
			detab(s, argv);
			printf("Detabbed  : %s", s);
		}
	} else {
		while (printf("\nEnter text: "), !feof(stdin) && fgets(s, MAX_LEN, stdin) != NULL) {
			mnEntab(s, atoi(argv[1] + 1), atoi(argv[2] + 1));
			printf("Entabbed  : %s", s);
			mnDetab(s, atoi(argv[1] + 1), atoi(argv[2] + 1));
			printf("Detabbed  : %s", s);
		}
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

int mnGetstop(int pos, int m, int n) {
	if (pos < m) {
		return (m < pos/8 * 8 + 8) ? m : pos/8 * 8 + 8;
	} else {
		return pos + (pos - m) / n * n + n;
	}
}

void mnEntab(char * string, int m, int n) {
	int inPos = 0, outPos = 0, virtualPos = 0, chain = 0;
	int nextstop = mnGetstop(virtualPos, m, n);
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
				nextstop = mnGetstop(virtualPos, m, n);
			}

			if (virtualPos == nextstop) {
				string[outPos++] = '\t';
				chain = 0;
				wasSpace = false;
				nextstop = mnGetstop(virtualPos, m, n);
			}

			break;

		case '\t':
			while (virtualPos >= nextstop) {
				nextstop = mnGetstop(virtualPos, m, n);
			}

			chain = 0;
			virtualPos = nextstop;
			nextstop = mnGetstop(virtualPos, m, n);

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

void mnDetab(char * string, int m, int n) {
	int inPos = 0, outPos = 0;
	int nextstop = mnGetstop(outPos, m, n);
	char c, temp[MAX_LEN + 1];

	while ((c = string[inPos++]) != '\0') {
		if (c == '\t') {
			while (outPos >= nextstop) {
				nextstop = mnGetstop(outPos, m, n);
			}
			while (outPos < nextstop) {
				temp[outPos++] = ' ';
			}
			nextstop = mnGetstop(outPos, m, n);
		} else {
			temp[outPos++] = c;
		}
	}
	temp[outPos++] = '\0'; 
	strcpy(string, temp);	
}