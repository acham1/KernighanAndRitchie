/** Modify undcl so that it does not add redundant parentheses to declarations. */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXTOKEN 1000

enum {PARENS, BRACKETS, NAME};

int tokentype; /* type of last token */
char token[MAXTOKEN]; /* last token string */
int getch(void);
void ungetch(int c);
int haslast = 0;
char lastchar;


int main(void) {
    return 0;
}

int gettoken(void) {
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    while ((c = getch()) == ' ' || c == '\t');
    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']'; );
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch()); ) {
            *p++ = c;
        }
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    } else {
        return tokentype = c;
    }
}

int getch(void) {
    if (haslast) {
        haslast = 0;
        return lastchar;
    } else {
        return getc(stdin);
    }
}

void ungetch(int c) {
    if (haslast) {
        printf("Error: cannot have more than one char of pushback\n");
    } else {
        haslast = 1;
        lastchar = c;
    }
}