/** Add the option -f to fold upper and lower case together, so that case
  * distinctions are not made during sorting; for example, a and A compare equal.  */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 100

void print_heading(int fold);
int folded_strcmp(const char* str1, const char* str2);
void quicksort_str(char** lines, int start, int end, int fold);

int main(int argc, char* argv[]) {
	char buffer[MAX_LEN+1];
	int default_lines = 50;
	int position = 0;
	int current_len;
    char** lines;
    int fold = 0;

    lines = malloc(sizeof(char*) * default_lines);
    while (--argc > 0) {
    	if (strcmp(argv[argc], "-f") == 0) {
    		fold = 1;
    		break;
    	}
    }
    print_heading(fold);
    while (!feof(stdin) && fgets(buffer, MAX_LEN, stdin)) {
    	current_len = strlen(buffer)+1;
    	lines[position] = malloc(sizeof(char) * current_len);
    	memcpy(lines[position], buffer, sizeof(char) * current_len);
    	position++;
        if (position == default_lines) {
            lines = realloc(lines, default_lines += 2);
        }
    }
    quicksort_str(lines, 0, position-1, fold);
    for (int i=0; i<position; i++) {
        printf("%d >> %s", i, lines[i]);
    	free(lines[i]);
    }
    free(lines);
	return EXIT_SUCCESS;
}

int folded_strcmp(const char* str1, const char* str2) {
	int position = 0;
	while (tolower(str1[position]) == tolower(str2[position]) 
		&& str1[position] && str2[position]) {
		position++;
	}
    if (str1[position] && str2[position]) {
    	return tolower(str1[position]) < tolower(str2[position]) ? -1 : 1;
	} else {
		if (!str1[position] && !str2[position]) {
			return 0;
		} else {
			return str1[position] ? 1 : -1;
		}
	}
}

void quicksort_str(char** lines, int start, int end, int fold) {
	int (*cmp)(const char*, const char*);
	int position = 0;
	int divider = 0;
	char* tmp;

	if (start >= end) {
		return;
	}
	cmp = fold ? &folded_strcmp : &strcmp;
	for (position=0; position<end; position++) {
		if (cmp(lines[position], lines[end]) < 0) {
			tmp = lines[position];
			lines[position] = lines[divider];
			lines[divider] = tmp;
			divider++;
		}
	}
	tmp = lines[divider];
	lines[divider] = lines[end];
	lines[end] = tmp;
	quicksort_str(lines, start, divider-1, fold);
	quicksort_str(lines, divider+1, end, fold);
}

void print_heading(int fold) {
    printf("Add the option -f to fold upper and lower case together, so that case\n"
    "distinctions are not made during sorting; for example, a and A compare equal.\n");
    printf("FOLD: %s\n", fold ? "ON" : "OFF");
    printf("Please enter lines (max len %d) below: \n", MAX_LEN);
}
