/** 
 * Exercise7-4.c
 * Write a private version of scanf analogous to minprintf from the previous section 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define MAX_WORD_LEN 100

/**
 * minscanf
 * A bare-bones version of scanf.
 */
int minscanf(char* format, ...) {
    va_list ap;
    int num = 0;

    va_start(ap, format);
    for (char* p = format; *p != '\0'; p++) {
        if (*p != '%') {
            char c = getc(stdin);
            if (c == *p) {
                continue;
            } else {
                return num;
            }
        } else {
            switch (*++p) {
                case 'd':
                    if (scanf("%d", va_arg(ap, int*)) < 1) {
                        va_end(ap);
                        return num;
                    }
                    break;
                case 'f':
                    if (scanf("%lf", va_arg(ap, double*)) < 1) {
                        va_end(ap);
                        return num;
                    }
                    break;
                case 's':
                    if (scanf("%s", va_arg(ap, char*)) < 1) {
                        va_end(ap);
                        return num;
                    }
                    break;
                default:
                    printf("Invalid argument type.");
                    break;
            } 
            num++;
        }
    }
    va_end(ap);
    return num;
}

int main(int argc, char* argv[]) {
    printf("Please enter the following (without quotations): \"1 2.0 three\"\n");
    int* integer = malloc(sizeof(int));
    double* decimal = malloc(sizeof(double));
    char* word = malloc(sizeof(char) * MAX_WORD_LEN);
    strcpy(word, "");
    minscanf("%d %f %s", integer, decimal, word);
    if (*integer != 1) {
        printf("You did not enter 1\n");
    }
    if (*decimal != 2.0) {
        printf("You did not enter 2.0\n");
    }
    if (strcmp(word, "three") != 0) {
        printf("You did not enter three\n");
    }
    printf("good job.");
    free(integer);
    free(decimal);
    free(word);
    return EXIT_SUCCESS;
}