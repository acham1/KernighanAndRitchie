/** Our version of getword does not properly handle underscores, string
  * constants, comments or preprocessor control lines. Write a better version. */

#include "Chapter6.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct key {
    char *word;
    int count;
} keytab[] = {
    "auto", 0,
    "break", 0,
    "case", 0,
    "char", 0,
    "const", 0,
    "continue", 0,
    "default", 0,
    "unsigned", 0, 
    "void", 0,
    "volatile", 0,
    "while", 0
};

#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof(struct key))

void print_heading(void);
int strict_getword(char* word, int lim);
int binsearch(char *, struct key tab[], int);

int main(void) {
    int n;
    char word[MAXWORD];

    while (strict_getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
            if ((n = binsearch(word, keytab, NKEYS)) >= 0) {
                keytab[n].count++;
            }
        }
    }
    for (n = 0; n < NKEYS; n++) {
        if (keytab[n].count > 0) {
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
        }
    }
    return EXIT_SUCCESS;
}

int binsearch(char *word, struct key tab[], int n) {
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0) {
            high = mid - 1;
        } else if (cond > 0) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}

int strict_getword(char* word, int lim) {
    char* w = word;
    int c, cnext;
    int hadSlash;

    while (isspace(c = getch()) && c != '"' && c != '/' && c != '\'') ;
    if (c != EOF) {
        cnext = getch();
        if (c == '/' && cnext == '/') {
            while ((c = getch()) != EOF && c != '\n');
        } else if (c == '/' && cnext == '*') {
            while (c != '*' || cnext != '/') {
                c = cnext;
                cnext = getch();
            }
        } else if (c == '"') {
            printf("in quote");
            hadSlash = 0;
            while (hadSlash || cnext != '"') {
                if (!hadSlash && cnext == '\\') {
                    hadSlash = 1;
                } else if (hadSlash && cnext == '\\') {
                    hadSlash = 0;
                } else {
                    hadSlash = 0;
                }
                c = cnext;
                cnext = getch();
            }
            printf("out quote");
        } else if (c == '\'') {
            hadSlash = 0;
            while (hadSlash || cnext != '\'') {
                if (!hadSlash && cnext == '\\') {
                    hadSlash = 1;
                } else if (hadSlash && cnext == '\\') {
                    hadSlash = 0;
                } else {
                    hadSlash = 0;
                }
                c = cnext;
                cnext = getch();
            }
        }
        *w++ = c;
    }
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++) {
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];
}

void print_heading(void) {
    printf("Our version of getword does not properly handle udnerscores, string\n"
        "constants, comments or preprocessor control lines. Write a better version.\n");
    printf("Please enter a valid C program below via stdin: \n");
}