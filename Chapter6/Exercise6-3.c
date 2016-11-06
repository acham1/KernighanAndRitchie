/** Write a cross-referencer that prints a list of all words in a document, and for
  * each word, a list of the line numbers on which it occurs. Remove noise words like 
  * "the", "and", and "so" on. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Chapter6.h"
#include <ctype.h>
#define MAXWORD 100
#define NUM_NOISE 3
#define DEFAULT_OCCURENCE 1

typedef struct Node {
    int pos;
    char* key;
    int capacity;
    int* line_nums;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
} List;

char* noise[NUM_NOISE] = {"the", "and", "so"};

void print_heading(void);
void free_list(List* l);
Node* create_node(void);
List* create_list(void);
int isnoise(char* word);
int strict_getword(char* word, int lim);
int line_num = 1;

int main(void) {
    List* L = create_list();
    int result, prevresult;
    char word[MAXWORD+1];
    Node* n, *prevn;
    int skip, i;

    print_heading();
    while (strict_getword(word, MAXWORD) != EOF) {
        if (isnoise(word))
            continue;
        if (strlen(word) <= 0) 
            continue;
        if (L->head == NULL) {
            n = L->head = create_node();
            n->line_nums[n->pos++] = line_num;
            n->key = malloc(strlen(word)+1);
            memcpy(n->key, word, strlen(word)+1);
        } else if (strcmp(word, L->head->key) < 0) {
            n = L->head;
            L->head = create_node();
            L->head->next = n;
            n->line_nums[n->pos++] = line_num;
            n->key = malloc(strlen(word)+1);
            memcpy(n->key, word, strlen(word)+1);
        } else {
            result = prevresult = 0;
            n = L->head;
            skip = 0;
            while (n != NULL) {
                result = strcmp(word, n->key);
                if (result == 0) {
                    if (n->pos >= n->capacity) 
                        n->line_nums = realloc(n->line_nums, n->capacity *= 2);
                    n->line_nums[n->pos++] = line_num;
                    skip = 1;
                    break;
                } else if (result < 0 && prevresult > 0) {
                    prevn->next = create_node();
                    prevn->next->next = n;
                    n = prevn->next;
                    n->line_nums[n->pos++] = line_num;
                    n->key = malloc(strlen(word)+1);
                    memcpy(n->key, word, strlen(word)+1);
                    skip = 1;
                    break;
                }
                prevresult = result;
                prevn = n;
                n = n->next;
            }
            if (skip)
                continue;
            prevn->next = create_node();
            n = prevn->next;
            n->line_nums[n->pos++] = line_num;
            n->key = malloc(strlen(word)+1);
            memcpy(n->key, word, strlen(word)+1);
        }
    }

    printf("\nPrinting line locations of each word:\n\n");
    n = L->head;
    while (n != NULL) {
        printf("%s: ", n->key);
        i = 0;
        while (i < n->pos) {
            printf("%d, ", n->line_nums[i++]);
        }
        printf("\n");
        n = n->next;
    }
    free_list(L);
    return EXIT_SUCCESS;
}

int isnoise(char* word) {
    int i = 0;
    while (i < NUM_NOISE) 
        if (strcmp(word, noise[i++]) == 0) 
            return 1;
    return 0;
}

void print_heading(void) {
    printf("Write a cross-referencer that prints a list of all words in a document,\n"
        "and for each word, a list of the line numbers on which it occurs. Remove noise\n"
        "words like \"the\", \"and\", and \"so\" on.\n");
    printf("Please enter a text document via stdin below:\n");
}

int strict_getword(char* word, int lim) {
    char* w = word;
    int c, cnext;
    int hadSlash;

    while (isspace(c = getch()) && c != '"' && c != '/' && c != '\'') 
        if (c == '\n')
            line_num++;
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

void free_list(List* l) {
    Node* n, *m;

    if (l == NULL)
        return;
    n = l->head;
    while (n != NULL) {
        m = n->next;
        free(n->line_nums);
        free(n->key);
        free(n);
        n = m;
    }
    free(l);
}

List* create_list() {
    List* l = malloc(sizeof(List));
    l->head = NULL;
    return l;
}

Node* create_node() {
    Node* n = malloc(sizeof(Node));
    n->pos = 0;
    n->key = NULL;
    n->next = NULL;
    n->capacity = DEFAULT_OCCURENCE;
    n->line_nums = malloc(sizeof(int) * DEFAULT_OCCURENCE);
    return n;
}
