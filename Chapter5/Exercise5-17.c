/** Add a field-searching capability, so sorting may bee done on fields within lines,
    each field sorted according to an independent set of options. (The index for this book was
    sorted with -df for the index category and -n for the page numbers.) */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 100
#define MAX_FIELDS 2

int special_strcmp(const char* str1, const char* str2, int fold[MAX_FIELDS], int directory[MAX_FIELDS]);
void quicksort_str(char** lines, int start, int end, int fold[MAX_FIELDS], int directory[MAX_FIELDS]);
void print_heading(int fold[MAX_FIELDS], int directory[MAX_FIELDS]);

int main(int argc, char* argv[]) {
    int directory[MAX_FIELDS] = {0, 0};
    char buffer[MAX_LEN+1];
    int default_lines = 50;
    int fold[MAX_FIELDS] = {0, 0};
    int position = 0;
    int current_len;
    char** lines;

    lines = malloc(sizeof(char*) * default_lines);
    for (int i = 1; i<argc && i<3; i++) {
        if (argv[i][0] == '-') {
            int j = 1;
            while (argv[i][j]) {
                if (argv[i][j] == 'f') {
                    fold[i-1] = 1;
                } else if (argv[i][j] == 'd') {
                    directory[i-1] = 1;
                }
                j++;
            }
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

int my_strcmp(const char* str1, const char* str2, int fold, int directory) {
    printf("my_strcmp\n");
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

int special_strcmp(const char* str1, const char* str2, int fold[MAX_FIELDS], int directory[MAX_FIELDS]) {
    printf("special strcmp\n");
    char buffer1[MAX_LEN+1];
    char buffer2[MAX_LEN+1];
    int pos1, pos2;
    int result;

    pos1 = pos2 = 0;
    for (int i=0; i<MAX_FIELDS; i++) {
        while (str1[pos1] && str1[pos1] != '%') {
            buffer1[pos1] = str1[pos1];
            pos1++;
        }
        buffer1[pos1] = '\0';
        while (str2[pos2] && str2[pos2] != '%') {
            buffer2[pos2] = str2[pos2];
            pos2++;
        }
        buffer2[pos2] = '\0';
        result = my_strcmp(buffer1, buffer2, fold[i], directory[i]);
        if (result != 0) {
            return result;
        } else if (!str1[pos1] && str2[pos2]) {
            return -1;
        } else if (str1[pos1] && !str2[pos2]) {
            return 1;
        } else if (!str1[pos1] && !str2[pos2]) {
            return 0;
        }
        pos1++;
        pos2++;
    }
    return 0;
}

void quicksort_str(char** lines, int start, int end, int fold[MAX_FIELDS], int directory[MAX_FIELDS]) {
    printf("quicksort_str %d %d \n", start, end);
    int position = start;
    int divider = start;
    char* tmp;
    if (start >= end) {
        return;
    }
    for (position=start; position<end; position++) {
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

void print_heading(int fold[MAX_FIELDS], int directory[MAX_FIELDS]) {
    printf("Add a field-searching capability, so sorting may bee done on fields within lines,\n"
        "each field sorted according to an independent set of options. (The index for this book was\n"
        "sorted with -df for the index category and -n for the page numbers.) \n");
    printf("FOLD: 1 %s, 2 %s\n", fold[0] ? "ON" : "OFF", fold[1] ? "ON" : "OFF");
    printf("DIRECTORY: 1 %s, 2 %s\n", directory[0] ? "ON" : "OFF", directory[1] ? "ON" : "OFF");
    printf("This program supports up to two fields, delimited by the %% symbol.\n"
        "this program supports the -d, -f, and -df options.\n");
    printf("Specify options for first field and then second; e.g. ./a.out -df -f\n"
        "Please enter lines (max len %d) below: \n", MAX_LEN);
}
