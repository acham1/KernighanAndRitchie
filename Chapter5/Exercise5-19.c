/** Modify undcl so that it does not add redundant parentheses to declarations. */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXTOKEN 1000

enum {PARENS, BRACKETS, NAME};

int tokentype; /* type of last token */
int prevtokentype = 0;
char token[MAXTOKEN]; /* last token string */
char nexttoken[MAXTOKEN];
char prevtoken[MAXTOKEN];
int nexttokentype;
char temptoken[MAXTOKEN];
int temptokentype;
int getch(void);
void ungetch(int c);
int gettoken(void);
char out[1000];
int haslast = 0;
char lastchar;

/* undcl: convert word descriptions to declarations */
int main(void) {
    char temp[MAXTOKEN];

    printf("Modify undcl so that it does not add redundant parentheses to declarations.\n");
    printf("Example:\n");
    printf(">>  x () * [] * () char\n");
    printf(">>  char (*(*x())[])()\n");
    printf("Please enter description below: \n");

    printf(">>  ");
    tokentype = gettoken();
    prevtokentype = '\0';
    while (tokentype != EOF) {
        strcpy(out, token);
        tokentype = gettoken();

        while (tokentype != '\n') {
            strcpy(temptoken, token);
            temptokentype = tokentype;
            tokentype = gettoken();
            strcpy(nexttoken, token);
            nexttokentype = tokentype;
            strcpy(token, temptoken);
            tokentype = temptokentype;
            if (tokentype == PARENS || tokentype == BRACKETS) {
                strcat(out, token);
            } else if (tokentype == '*') {
                if (prevtokentype == '*' || nexttokentype == '*') {
                    sprintf(temp, "*%s", out);
                } else {
                    sprintf(temp, "(*%s)", out);
                }
                strcpy(out, temp);
            } else if (tokentype == NAME) {
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
            } else {
                printf("invalid input at %s\n", token);
            }
            prevtokentype = tokentype;
            strcpy(prevtoken, token);
            tokentype = nexttokentype;
            strcpy(token, nexttoken);
        }
        printf(">>  ");
        printf("%s\n", out);
        printf(">>  ");
        out[0] = '\0';
        prevtokentype = tokentype;
        strcpy(prevtoken, token);
        tokentype = gettoken();
    }
    printf("\n");
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