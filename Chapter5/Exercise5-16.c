/** Add the -d (``directory order'') option, which makes comparisons only on
    letters, numbers and blanks. Make sure it works in conjunction with -f. */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 100

int special_strcmp(const char* str1, const char* str2, int fold, int directory);
void quicksort_str(char** lines, int start, int end, int fold, int directory);
void print_heading(int fold, int directory);

int main(int argc, char* argv[]) {
    char buffer[MAX_LEN+1];
    int default_lines = 50;
    int directory = 0;
    int position = 0;
    int current_len;
    char** lines;
    int fold = 0;

    lines = malloc(sizeof(char*) * default_lines);
    while (--argc > 0) {
        if (strcmp(argv[argc], "-f") == 0) {
            fold = 1;
        } else if (strcmp(argv[argc], "-d") == 0) {
            directory = 1;  
        } else {
            printf("Error: option %s not recognized.\n", argv[argc]);
        }
    }
    print_heading(fold, directory);
    while (!feof(stdin) && fgets(buffer, MAX_LEN, stdin)) {
        current_len = strlen(buffer)+1;
        lines[position] = malloc(sizeof(char) * current_len);
        memcpy(lines[position], buffer, sizeof(char) * current_len);
        position++;
        if (position == default_lines) {
            lines = realloc(lines, default_lines += 2);
        }
    }
    quicksort_str(lines, 0, position-1, fold, directory);
    for (int i=0; i<position; i++) {
        printf("%d >> %s", i, lines[i]);
        free(lines[i]);
    }
    free(lines);
    return EXIT_SUCCESS;
}

int special_strcmp(const char* str1, const char* str2, int fold, int directory) {
    int position1 = 0;
    int position2 = 0;
    char c1, c2;
    while (1) {
        c1 = str1[position1];
        c2 = str2[position2];
        if (!c1 || !c2) {
            break;
        }
        if ((directory) && ((!isalnum(c1) && !isspace(c1)) || (!isalnum(c2) && !isspace(c2)))) {
            if (!isalnum(c1) && !isspace(c1)) {
                position1++;
            }
            if (!isalnum(c2) && !isspace(c2)) {
                position2++;
            }
            continue;
        }
        if (fold) {
            c1 = tolower(c1);
            c2 = tolower(c2);
        }
        if (c1 != c2) {
            break;
        }
        position1++; 
        position2++;
    }
    if (c1 && c2) {
        return c1 < c2 ? -1 : 1;
    } else if (!c1 && !c2) {
        return 0;
    } else {
        return c1 ? 1 : -1;
    }
}

void quicksort_str(char** lines, int start, int end, int fold, int directory) {
    int position = 0;
    int divider = 0;
    char* tmp;
    if (start >= end) {
        return;
    }
    for (position=0; position<end; position++) {
        if (special_strcmp(lines[position], lines[end], fold, directory) < 0) {
            tmp = lines[position];
            lines[position] = lines[divider];
            lines[divider] = tmp;
            divider++;
        }
    }
    tmp = lines[divider];
    lines[divider] = lines[end];
    lines[end] = tmp;
    quicksort_str(lines, start, divider-1, fold, directory);
    quicksort_str(lines, divider+1, end, fold, directory);
}

void print_heading(int fold, int directory) {
    printf("Add the -d (``directory order'') option, which makes comparisons only on\n"
        "letters, numbers and blanks. Make sure it works in conjunction with -f.\n");
    printf("FOLD: %s\n", fold ? "ON" : "OFF");
    printf("DIRECTORY: %s\n", directory ? "ON" : "OFF");
    printf("Please enter lines (max len %d) below: \n", MAX_LEN);
}
