#include <stdio.h>
#include "Chapter6.h"
#define MAX_PUSHBACK 1000

static int lastchar[MAX_PUSHBACK];
static int haslast = 0;

extern int getch(void) {
    if (haslast) {
        return lastchar[--haslast];
    } else {
        return getc(stdin);
    }
    return 0;
}

extern void ungetch(int c) {
    if (haslast >= MAX_PUSHBACK) {
        printf("Error: cannot have more than %d chars of pushback\n", MAX_PUSHBACK);
    } else {
        lastchar[haslast++] = c;
    }
}