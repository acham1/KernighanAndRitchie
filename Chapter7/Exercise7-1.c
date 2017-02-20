/** 
 * Write a program that converts upper case to lower or lower case to upper,
 * depending on the name it is invoked with, as found in argv[0].
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define UPPER "upper"
#define LOWER "lower"

int main(int argc, char* argv[]) {
    int (*change)(int);
    int c;

    printf("Converts upper case to lower if invoked with name \"upper\"\n");
    printf("Converts lower case to upper if invoked with name \"lower\"\n");
    printf("Invalid otherwise.\n");

    printf("\nEnter text below:\n");

    if (strcmp(UPPER, argv[0]) == 0) {
        change = toupper;
    } else if (strcmp(LOWER, argv[0]) == 0) {
        change = tolower;
    } else {
        printf("Program invoked with invalid name (must be \"upper\" or \"lower\"\n");
        return EXIT_FAILURE;
    }
    while ((c = getchar()) != EOF) {
        printf("%c", change(c));
    }
    return EXIT_SUCCESS;
}