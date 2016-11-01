#include <stdio.h>
#include "Chapter6.h"
#include <stdlib.h>

void print_heading(void);
int getword(char *word, int lim) {
    int c;
    char *w = word;

    while (isspace(c = getch())) {
        
    }
}

int main(void) {
    
    return EXIT_SUCCESS;
}

void print_heading(void) {
    printf("Our version of getword does not properly handle udnerscores, string\n"
        "constants, comments or preprocessor control lines. Write a better version.\n");
}