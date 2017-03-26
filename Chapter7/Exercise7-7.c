/** 
 * Exercise7-7.c
 * Modify the pattern finding program of Chapter 5 to take its input from
 * a set of named files or, if no files are named as arguments, from the
 * standard input. Should the file name be printed when a matching line is
 * found? 
 *
 * Yes, printing the filename makes the results more useful, when multiple
 * files are provided as input. 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

/**
 * search a file for matches
 */
int searchFile(char* line, FILE* file, int number, int except, char* pattern);

/**
 * find: print lines that match pattern from 1st arg 
 * (lines read from files provided in 2nd, 3rd, etc args or stdin if no file args)
 * Options: -n print line numbering
 *          -x except (print lines not matching pattern)
 */
int main(int argc, char* argv[]) {
    char line[MAXLINE], *pattern;
    int c, except = 0, number = 0;

    while (--argc > 0 && (*++argv)[0] == '-') {
        while (c = *++argv[0]) {
            switch (c) {
                case 'x':
                    except = 1;
                    break;
                case 'n':
                    number = 1;
                    break;
                default:
                    printf("find: illegal option %%c\n", c);
                    argc = 0;
                    break;
            }
        }
    }
    if (argc-- < 1) {
        printf("Usage: find -x -n pattern <file1 file2 ...>\n");
        return EXIT_FAILURE;
    } else {
        pattern = *argv++;
    }
    if (argc-- < 1) {
        printf("Using stdin as input.\n");
        searchFile(line, stdin, number, except, pattern);
    } else {
        FILE* file;

        while (*argv) {
            printf("\nSearching file: %s\n", *argv);
            file = fopen(*argv++, "r");
            if (file == NULL) {
                printf("Error: file not found.\n");
                continue;
            } else {
                searchFile(line, file, number, except, pattern);
            }
        }
    }
    return EXIT_SUCCESS;
}

/**
 * search a file for matches
 */
int searchFile(char* line, FILE* file, int number, int except, char* pattern) {
    long lineno = 0, found = 0;

    while (fgets(line, MAXLINE, file) != NULL) {
        lineno++;
        if ((strstr(line, pattern) != NULL) ^ except) {
            if (number) {
                printf("%ld:", lineno);
            }
            printf("%s", line);
            found++;
        }
        if (feof(file)) break;
    }
    return found;
}
