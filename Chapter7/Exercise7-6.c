/**
 * Exercise7-6.c
 * Write a program to compare two files, printing the first line where they differ
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 100

char line1[MAX_LINE];
char line2[MAX_LINE];

int main(int argc, char* argv[]) {
    FILE* f1, *f2;

    // check input arguments are of the proper quantity
    if (argc != 3) {
        printf("Error: expected exactly two arguments (files to compare).");
        return EXIT_FAILURE;
    }
    // attempt to open files
    f1 = fopen(argv[1], "r");
    f2 = fopen(argv[2], "r");
    // check that files can be opened
    if (f1 == NULL) {
        printf("Error: could not open file %s\n", argv[1]);
        return EXIT_FAILURE;
    } else if (f2 == NULL) {
        printf("Error: could not open file %s\n", argv[2]);
        return EXIT_FAILURE;
    }
    // scan for first different line
    while (1) {
        char* result1 = fgets(line1, MAX_LINE, f1);
        char* result2 = fgets(line2, MAX_LINE, f2);
        if (result1 == NULL && result2 == NULL) {
            printf("no difference found\n");
            break;
        } else if ((result1 != NULL && result2 == NULL)
            || (result1 == NULL && result2 != NULL)  
            || (strcmp(line1, line2) != 0)) {
            printf("found difference:\n");
            printf(">> %s\n", argv[1]);
            printf("%s\n", (line1 == NULL) ? "<end of file>" : line1);
            printf(">> %s\n", argv[2]);
            printf("%s\n", (line2 == NULL) ? "<end of file>" : line2);
            break;
        } else if ((strlen(line1) == MAX_LINE - 1) 
            && (result1[strlen(line1)-1] != '\n')) {
            printf("Error: file %s has line that exceeds %d chars\n", argv[1], MAX_LINE);
            printf("Line preview: %s\n", line1);
            break;
        } else if ((strlen(line2) == MAX_LINE - 1)
            && (result2[strlen(line2)-1] != '\n')) {
            printf("Error: file %s has line that exceeds %d chars\n", argv[2], MAX_LINE);
            printf("Line preview: %s\n", line2);
            break;
        } else {
//            printf("matched line: %s\n", line1);
        }
    }
    fclose(f1);
    fclose(f2);
    return EXIT_SUCCESS;
}