/** Implement a simple version of the #define processor (i.e., no arguments)
  * suitable for use with C programs, based on the routines of this section. 
  * You may also find getch and ungetch helpful.. */

#define HASHSIZE 101
#define MAXLINE 1000
#define FILEINDEX 1
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* get next word from a char* and store in allocated memory */
char * getWord(char* s) {
    char temp[MAXLINE];
    char* out;
    int pos = 0; /* position to write to in temp */

    while (!isspace(*s) && *s != '\0' && *s != EOF) {
        temp[pos++] = *s++;
    }
    temp[pos] = '\0';
    out = malloc(sizeof(char) * (1 + strlen(temp)));
    return strcpy(out, temp);
}

struct nlist { /* table entry: */
    struct nlist *next; /* next entry in chain */
    char *name;         /* defined name */
    char * defn;        /* replacement text */
};

static struct nlist *hashtab[HASHSIZE]; /* pointer table */

/** lookup: look for s in hashtab */
struct nlist *lookup(char* s) {
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
        if (strcmp(s, np->name) == 0) {
            return np; /* found */
        }
    }
    return NULL; /* not found */
}

/** undef: remove s from hashtab 
    returns: pointer to nlist that contains the removed string */
struct nlist *undef(char* s) {
    struct nlist *np, *prev;

    prev = NULL;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
        /* if find a match, then remove from table */
        if (strcmp(s, np->name) == 0) {
            if (prev != NULL) {
                prev->next = np->next;
            } else {
                prev = np;
                hashtab[hash(s)] = np->next;
            }
            return np; /* found */
        } else {
            /* if no match, advance to next node */
            prev = np;
        }
    }
    return NULL; /* not found */
}

unsigned hash(char *s) {
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++) {
        hashval = *s + 31 * hashval;
    }
    return (unsigned) hashval % HASHSIZE;
}

/* install: put (name, defn) in hashtab */
 struct nlist *install(char *name, char *defn) {
    struct nlist *np;
    unsigned hashval;
    if ((np = lookup(name)) == NULL) { /* not found */
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else {/* already there */
        free((void *) np->defn); /*free previous defn */
    }
    if ((np->defn = strdup(defn)) == NULL) {
        return NULL;
    }
    return np;
}

int main(int argc, char* argv[]) {
    struct nlist* node;
    char tmpline[MAXLINE];
    char* tableKey, *tableValue, *currentWord;
    char* strPointer;
    int containsDefine;
    FILE* f;

    f = fopen(argv[FILEINDEX]);
    /* keep reading new lines until end of file */
    while (fgets(tmpline, MAXLINE, f) != NULL) {
        strPointer = strtok(tmpline, ' ');
        containsDefine = strstr(strPointer, "#define");
        /* if line starts with #define, then install entry in hashtable */
        if (containsDefine == strPointer) {
            strPointer = strtok(NULL, ' ');
            tableKey = getWord(strPointer);
            strPointer = strtok(NULL, ' ');
            tableValue = getWord(strPointer);
            install(tableKey, tableValue);
        } else {
            /* check if each word is in the dictionary, */
            /* and print either the word of its definition*/
            currentWord = getWord(strPointer);
            while (strlen(currentWord)) {
                if (node = lookup(currentWord)) {
                    printf("%s ", node->defn);
                } else {
                    printf("%s ", currentWord);
                }
                free(currentWord);
            }
        }
    }
}