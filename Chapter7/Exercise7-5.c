/**
 * Exercise 7-5
 * Rewrite the postfix calculator of Chapter 4 to use scanf and/or sscanf to do
 * the input and number conversion. 
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_DEPTH 100

int main (int argc, char* argv[]) {
    double stack[MAX_DEPTH];
    int stackPosition = 0;
    double number = 0;
    char symbol = 0;

    printf("Exercise 7-5 Polish Calculator\n");
    printf("Operations supported: + - / * (separated by whitespace)\n");
    printf("Maximum stack depth: %d\n", MAX_DEPTH);
    printf("Usage example: for operations (0 + 1) * 5, enter \"0 1 + 5 *\"\n");
    printf("\nBegin:\n");

    while (!feof(stdin)) {
        if (scanf(" %lf", &number)) {
            printf("number\n");
        } else if (scanf(" %c", &symbol)) {
            printf("Read symbol %c\n", symbol);
        }
    }
    printf("Ending.\n");
    return EXIT_SUCCESS;
}