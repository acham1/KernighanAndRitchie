/** Write the program tail, which prints the last n lines of its input. By default, n
  * is set to 10, let us say, but it can be changed by an optional argument so that
  * tail -n prints the last n lines. The program should behave rationally no matter 
  * how unreasonable the input or the value of n. Write the program so it makes the 
  * best use of available storage; lines should be stored as in the sorting program 
  * of Section 5.6, not in a two-dimensional array of fixed size. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define LINE_MAX 10000

void update(char ** finalSet, int seen, int n, char * newLine);

int main(int argc, char * argv[]) {
	printf("Write the program tail, which prints the last n lines of its input. By default, n\n"
		"is set to 10, let us say, but it can be changed by an optional argument so that\n"
		"tail -n prints the last n lines. The program should behave rationally no matter\n"
		"how unreasonable the input or the value of n. Write the program so it makes the\n"
		"best use of available storage; lines should be stored as in the sorting program\n"
		"of Section 5.6, not in a two-dimensional array of fixed size.\n");

  printf("Please enter n value as command-line input and type input text below:\n");

  int n;
  if (argv[1] == NULL) {
    printf("Error: No n value provided.\n");
  } else {
      n = atoi(argv[1]);
      if (n == 0) {
        printf("Found n = 0; no printing needed.\n");
        return EXIT_SUCCESS;
      }
  }

  char tempLine[LINE_MAX + 1];
  int seen = 0;
  char ** lastN = malloc(n * sizeof(char *));
  while (!feof(stdin) && fgets(tempLine, LINE_MAX, stdin) != NULL) {
    seen++;
    update(lastN, seen, n, tempLine);
  }

  int i;
  printf("\nLast %d lines: \n", n);
  for (i = 0; i < min(seen, n); i++) {
    printf("%s", lastN[i]);
    free(lastN[i]);
  }
  free(lastN);
	return EXIT_SUCCESS;
}

void update(char ** finalSet, int seen, int n, char * newLine) {
  if (seen > n) {
    free(finalSet[0]);
    int i;
    for (i = 0; i < n - 1; i++) {
      finalSet[i] = finalSet[i + 1];
    }
  }
  finalSet[(seen >= n) ? n - 1: seen - 1] = malloc(sizeof(char) * (strlen(newLine) + 1));
  strcpy(finalSet[(seen >= n) ? n - 1: seen - 1], newLine);
}


