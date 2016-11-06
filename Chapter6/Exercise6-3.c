/** Write a cross-referencer that prints a list of all words in a document, and for
  * each word, a list of the line numbers on which it occurs. Remove noise words like 
  * "the", "and", and "so" on. */

#include <stdio.h>
#include <stdlib.h>
#include "Chapter6.h"
#define MAXWORD 100

typedef struct Node {
    int num;
    char* key;
    struct Node* data;
    struct Node* next;
} Node;

void print_heading(void);
void free_list(Node* l);
Node* create_node(void);

int main(void) {
    int word[MAXWORD+1];

    print_heading();
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
    printf("Write a cross-referencer that prints a list of all words in a document,\n"
        "and for each word, a list of the line numbers on which it occurs. Remove noise\n"
        "words like \"the\", \"and\", and \"so\" on.\n");
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

Node* create_node() {
    Node* n = malloc(sizeof(Node));
    n->num = 0;
    n->key = NULL;
    n->data = NULL;
    n->next = NULL;
    return n;
}
