/**
 * Write a program to print a set of files, starting each new one on a 
 * new page, with a title and a running page count for each file.
 */

#include <stdio.h>
#include <stdlib.h>
#define LINES_PER_PAGE 64
#define MAX_LINE 1000


int main(int argc, char* argv[]) {
    if (argc == 1) {
        printf("Usage: printfiles <file1 file2 file3...>\n");
    }
    for (int i = 1; i < argc; i++) {
        int lineNumber = 0, pageNumber = 1;
        FILE* file = fopen(argv[i], "r");
        char line[MAX_LINE];

        if (file == NULL) {
            fprintf(stderr, "Error: file %s could not be opened.\n", argv[i]);
            continue;
        }
        /* title page */
        printf("%s\n\f", argv[i]);
        while (fgets(line, MAX_LINE, file)) {
            /* print page number */
            if (lineNumber == 0) {
                printf("Page %d\n", pageNumber);
            }
            printf("%2d: %s", lineNumber++, line);
            /* end page */
            if (lineNumber == LINES_PER_PAGE - 1) {
                lineNumber = 0;
                pageNumber++;
                printf("\n\f");
            }
            if (feof(file)) break;
        }
        printf("\n\f");
        fclose(file);
    }
    return EXIT_SUCCESS;
}