/** 
 * Modify the fsize program to print the other information contained in the inode 
 * entry.
 */

extern int stat(char *, struct stat *);
extern void dirwalk(char *, void (*fcn)(char *));

/* fsize: print the name of file "name" */
void fsize(char *name) {
    struct stat stbuf;
    
    if (stat(name, &stbuf) == -1) {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }
    if ((stbuf.st_mode & S_IFMT) == S_IFDIR) {
        dirwalk(name, fsize);
    }
    /* print size, owners user id, time last modified */
    printf("%8ld %ld %ld %s\n", stbuf.st_size, stbuf.st_uid, stbuf.st_mtime, name);
}
