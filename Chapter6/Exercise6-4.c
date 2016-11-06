/** Write a program that prints the distinct words in its input sorted into
  * decreasing order of frequency of occurrence. Precede each word by its 
  * count. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Chapter6.h"
#include <ctype.h>
#define MAXWORD 100
#define DEFAULT_NUM_WORDS 1

void print_heading(void);
int strict_getword(char* word, int lim);
void mergesort(char** words, int* frequencies, int first, int last);

int main(void) {
    int capacity = DEFAULT_NUM_WORDS;
    char** words = malloc(sizeof(char*) * capacity);
    int* frequencies = malloc(sizeof(int) * capacity);
    int i, found, pos = 0;
    char word[MAXWORD+1];

    print_heading();
    while (strict_getword(word, MAXWORD) != EOF) {
        if (strlen(word) <= 0 || !isalnum(word[0])) 
            continue;
        found = 0;
        for (i = 0; i < pos; i++) {
            if (strcmp(word, words[i]) == 0) {
                frequencies[i]++;
                found = 1;
                break;
            }
        }
        if (!found) {
            frequencies[pos] = 1;
            words[pos] = malloc(sizeof(char) * (strlen(word)+1));
            strcpy(words[pos++], word);
//            printf("added new word %s with frequency %d\n", words[pos-1], frequencies[pos-1]);
        }
        if (pos == capacity) {
//            printf("doubling capacity to %d\n", capacity);
            capacity *= 2;
            words = realloc(words, capacity * sizeof(char*));
            frequencies = realloc(frequencies, capacity * sizeof(int));
        }
    }

    mergesort(words, frequencies, 0, pos-1);
    printf("\nWords in order of frequency are:\n");
    for (i = 0; i < pos; i++)
        printf("%d %s\n", frequencies[i], words[i]);
    for (i = 0; i < pos; i++)
        free(words[i]);
    free(words);
    free(frequencies);
    return EXIT_SUCCESS;
}

void mergesort(char** words, int* frequencies, int first, int last) {
    int mid = (last+first)/2;
    int lp = first, rp = mid+1;
    char** aux_words = malloc(sizeof(char*) * (last-first+1));
    int* aux_freqs= malloc(sizeof(int) * (last-first+1));
    int pos = 0;

    if (last <= first) {
        free(aux_words);
        free(aux_freqs);
        return;
    }
    mergesort(words, frequencies, first, mid);
    mergesort(words, frequencies, mid+1, last);
    while (lp <= mid || rp <= last) {
        if (lp > mid) {
            aux_words[pos] = words[rp];
            aux_freqs[pos++] = frequencies[rp++];
        } else if (rp > last) {
            aux_words[pos] = words[lp];
            aux_freqs[pos++] = frequencies[lp++];
        } else {
            aux_words[pos] = (frequencies[lp] > frequencies[rp]) ? words[lp] : words[rp];
            aux_freqs[pos++] = (frequencies[lp] > frequencies[rp]) ? frequencies[lp++] : frequencies[rp++];
        }
    }
    for (lp = first; lp <= last; lp++) {
        words[lp] = aux_words[lp-first];
        frequencies[lp] = aux_freqs[lp-first];
    }
    free(aux_words);
    free(aux_freqs);
}


void print_heading(void) {
    printf("Write a program that prints the distinct words in its input sorted into\n"
        "decreasing order of frequency of occurrence. Precede each word by its\n"
        "count.\n");
    printf("Please enter a text document via stdin below:\n");
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
