/**
 * Write a program that will print arbitrary input in a sensible way. As a 
 * minimum, it should print non-graphic characters in octal or hexadecimal
 * according to local custom, and break long text lines. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LINE 80

int main(int argc, char* argv[]) {
    int counter = 0;
    char c;

    printf("Enter arbitrary input to be printed. Lines longer that %d will be broken.\n", MAX_LINE);

    while ((c = getchar()) != EOF) {
        counter++;
        if (isgraph(c)) {
            printf("%c", c);
        } else {
            printf("%o", c);
        }
        if (counter == MAX_LINE) {
            printf("\n");
            counter = 0;
        }
    }
    return EXIT_SUCCESS;
}