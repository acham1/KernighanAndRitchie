/** Expand dcl to handle declarations with function argument types,
  * qualifiers like const, and so on. */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

int dcl(void);
int dirdcl(void);
int gettoken(void); /* return next token */

int tokentype; /* type of last token */
char token[MAXTOKEN]; /* last token string */
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];
char lastchar[MAXTOKEN];
int haslast = 0;

int main() { /* convert declaration to words */
    int c;
    int getch(void);
    void ungetch(int);

    printf("Expand dcl to handle declarations with function argument types,\n"
        "qualifiers like const, and so on.\n");
    printf("This program cannot handle declarations with arguments.\n");
    printf("This program can handle qualifiers\n");
    printf("Example:\n"
    "    >> int (*((*fn[3])())[4])()\n"
    "    >> fn:  array[3] of pointer to function returning array[4] of pointer to\n"
    "            function returning int\n");
    printf("Enter declaration below: \n");
    while (printf(">> "), gettoken() != EOF) {
        strcpy(datatype, token);
        out[0] = '\0';
        if (dcl()) {
            printf("Error: invalid input\n");
            while (tokentype != '\n' && tokentype != EOF && (c = getch()) != '\n' && c != EOF);
            continue;
        }
        if (tokentype != '\n') {
            printf("syntax error\n");
        }
        printf("%s: %s %s \n", name, out, datatype);
    }
    printf("\n");
    return 0;
}

int gettoken(void) {
    int c, getch(void);
    void ungetch(int);
    char *p = token;
    int num_past = 0;
    int was_space = 1;

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
        for (*p++ = c; isalnum(c = getch()) || c == ' '; ) {
            *p++ = c;
            if (was_space && isalnum(c)) {
                was_space = 0;
                num_past = 1;
            } else if (!was_space && !isalnum(c)) {
                was_space = 1;
                num_past++;
            } else {
                num_past++;
            }
        }
        ungetch(c);
        if (c == '(') {
            while (num_past-- > 0) {
                ungetch(*--p);
            }
        }
        *p = '\0';
        return tokentype = NAME;
    } else {
        return tokentype = c;
    }
}

/* decl: parse a declarator */
int dcl(void) {
    int ns;

    for (ns = 0; gettoken() == '*'; ) {/* count *'s */
        ns++;
    }
    if (dirdcl()) {
        return 1;
    }
    while (ns-- > 0) {
        strcat(out, " pointer to");
    }
    return 0;
}

/* dirdcl: parse a direct declarator */
int dirdcl(void) {
    int type;
    void ungetch(int);

    if (tokentype == '(') { /* ( dcl ) */
        dcl();
        if (tokentype != ')') {
            printf("\nerror: missing )\n");
            return 1;
        } 
    } else if (tokentype == NAME) {/* variable name */
        strcpy(name, token);
    } else {
        printf("\nerror: expected name or (dcl)\n");
        return 1;
    }
    while ((type = gettoken()) == PARENS || type == BRACKETS) {
        if (type == PARENS) {
            strcat(out, " function returning");
        } else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
    return 0;
}

int getch(void) {
    if (haslast) {
        return lastchar[--haslast];
    } else {
        return getc(stdin);
    }
}

void ungetch(int c) {
    if (haslast >= MAXTOKEN) {
        printf("Error: cannot have more than one char of pushback\n");
    } else {
        lastchar[haslast++] = c;
    }
}