/** Write a function undef that will remove a name and definition from the table
  * maintained by lookup and install. */

#define HASHSIZE 101
#include <stdio.h>

struct nlist { /* table entry: */
    struct nlist *next; /* next entry in chain */
    char *name;         /* defined name */
    char * defn;        /* replacement text */
};

static struct nlist *hashtab[HASHSIZE]; /* pointer table */


char *strdup(char *s) { /* make a duplicate of s */ 
    char *p;
    p = (char *) malloc(strlen(s)+1); /* +1 for '\0' */
    if (p != NULL)
        strcpy(p, s);
    return p;
}

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

/** lookup: look for s in hashtab */
struct nlist *undef(char* s) {
    struct nlist *np, *prev;

    prev = NULL;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
        if (strcmp(s, np->name)) {
            if (prev != NULL) {
                prev->next = np->next;
            } else {
                hashtab[hash(s)] = np->next;
            }
            return np; /* found */
        }
        prev = np;
    }
    return NULL; /* not found */
}

unsigned hash(char *s) {
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++) {
        hashval = *s + 31 * hashval;
    }
    return hashval % HASHSIZE;
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