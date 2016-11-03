/** Write a program that reads a C program and prints in alphabetical order each
  * group of variable names that are identical in the first 6 characters, but different 
  * somewhere thereafter. Don't count words within strings and comments. Make 6 a 
  * parameter that can be set from the command line. */

#include "Chapter6.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node {
    int num;
    char* key;
    struct Node* data;
    struct Node* next;
} Node;

#define MAXWORD 100
#define DEFAULT_N 6

void print_heading(void);
int strict_getword(char* word, int lim);
void free_list(Node* l);
Node* create_node(void);
char* truncate(char* word, int n);
int addword(Node** l, char* word);

int main(int argc, char* argv[]) {
    char word[MAXWORD+1];
    char* tmpword;
    char* key;
    Node* list = NULL;
    Node* tmp;
    Node* prevtmp;
    int n = DEFAULT_N;
    int result;
    int prevresult;
    int skip;

    print_heading();

    if (argc > 1) {
        n = atoi(argv[1]);
        if (n <= 0) {
            printf("Error: invalid command line argument. must be positive integer\n");
            return EXIT_FAILURE;
        }
    }

    while (strict_getword(word, MAXWORD) != EOF) {
        if (strlen(word) <= 0) {
            continue;
        }
        if (list == NULL) {
            list = create_node();
            list->num = 1;
            list->key = truncate(word, n);
            list->data = create_node();
            tmpword = malloc(strlen(word)+1);
            memcpy(tmpword, word, strlen(word)+1);
            list->data->key = tmpword;
        } else if (strcmp(word, list->key) < 0) {
            tmp = list;
            list = create_node();
            list->next = tmp;
            list->num = 1;
            list->key = truncate(word, n);
            list->data = create_node();
            tmpword = malloc(strlen(word)+1);
            memcpy(tmpword, word, strlen(word)+1);
            list->data->key = tmpword;            
        } else {
            result = 0;
            prevresult = 0;
            tmp = list;
            key = truncate(word, n);
            skip = 0;
            while (tmp != NULL) {
                result = strcmp(key, tmp->key);
                if (result == 0) {
                    if (addword(&tmp->data, word)) {
                        tmp->num++;
                    } else {
                        free(key);
                    }
                    skip = 1;
                    break;
                } else if (result < 0 && prevresult > 0) {
                    prevtmp->next = create_node();
                    prevtmp->next->next = tmp;
                    tmp = prevtmp->next;
                    tmp->key = key;
                    tmp->num = 1;
                    tmp->data = create_node();
                    tmpword = malloc(strlen(word)+1);
                    memcpy(tmpword, word, strlen(word)+1);
                    tmp->data->key = tmpword;
                    skip = 1;
                    break;
                }
                prevresult = result;
                prevtmp = tmp;
                tmp = tmp->next;
            }
            if (skip) {
                continue;
            }
            prevtmp->next = create_node();
            tmp = prevtmp->next;
            tmp->key = key;
            tmp->num = 1;
            tmp->data = create_node();
            tmpword = malloc(strlen(word)+1);
            memcpy(tmpword, word, strlen(word)+1);
            tmp->data->key = tmpword;
        }
    }

    printf("Printing word clusters sharing first %d letters:\n\n", n);
    tmp = list;
    while (tmp != NULL) {
        prevtmp = tmp->data;
        while (prevtmp != NULL) {
            printf("%s\n", prevtmp->key);
            prevtmp = prevtmp->next;
        }
        printf("\n");
        tmp = tmp->next;
    }

    free_list(list);
    return EXIT_SUCCESS;
}

void print_heading(void) {
    printf("Write a program that reads a C program and prints in alphabetical order each\n"
        "group of variable names that are identical in the first 6 characters, but different\n"
        "somewhere thereafter. Don't count words within strings and comments. Make a\n"
        "parameter that can be set from the command line.\n");    
    printf("Enter command line argument number n to use first n characters as key (default 6).\n");
    printf("Please enter a valid c program via stdin below: \n");
}

char* truncate(char* word, int n) {
    char* out;
    int len = strlen(word);

    len = (len < n) ? len : n;
    out = malloc(sizeof(char) * (len+1));
    memcpy(out, word, len);
    out[len] = '\0';
    return out;
}

Node* create_node() {
    Node* n = malloc(sizeof(Node));
    n->num = 0;
    n->key = NULL;
    n->data = NULL;
    n->next = NULL;
    return n;
}

void free_list(Node* l) {
    Node* n;
    if (l != NULL) {
        n = l->next;
        if (l->key != NULL) {
            free(l->key);
        }
        free_list(l->data);        
        free(l);
        free_list(n);
    }
}

int addword(Node** n, char* word) {
    Node* tmp, *prevtmp;
    int result, prevresult;
    char* tmpword;
    Node* list = *n;

    if (list == NULL) {
        *n = create_node();
        tmpword = malloc(strlen(word)+1);
        memcpy(tmpword, word, strlen(word)+1);
        (*n)->key = tmpword;
    } else if (strcmp(word, list->key) < 0) {
        *n = create_node();
        tmpword = malloc(strlen(word)+1);
        memcpy(tmpword, word, strlen(word)+1);
        (*n)->key = tmpword;
        (*n)->next = list;
    } else {
        result = 0;
        prevresult = 0;
        tmp = list;
        while (tmp != NULL) {
            result = strcmp(word, tmp->key);
            if (result == 0) {
                return 0;
            } else if (result < 0 && prevresult > 0) {
                prevtmp->next = create_node();
                prevtmp->next->next = tmp;
                tmp = prevtmp->next;
                tmpword = malloc(strlen(word)+1);
                memcpy(tmpword, word, strlen(word)+1);
                tmp->key = tmpword;
                return 1;
            }
            prevresult = result;
            prevtmp = tmp;
            tmp = tmp->next;
        }
        prevtmp->next = create_node();
        tmp = prevtmp->next;
        tmpword = malloc(strlen(word)+1);
        memcpy(tmpword, word, strlen(word)+1);
        tmp->key = tmpword;
        return 1;
    }
    return 0;
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
        } else {
            *w++ = c;
            ungetch(cnext);
        }
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
//    printf("(%s)", word);
    return word[0];
}
