/**
 * Rewrite fopen and _fillbuf with fields instead of explicit bit operations.
 * Compare code size and execution speed.
 */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "my_stdio.h" 
#define PERMS 0666 /* RW for owner, group, others */

FILE _iob[OPEN_MAX] = { /* stdin, stdout, stderr */
    { 0, (char *) 0, (char *) 0, {1,0,0,0,0}, 0 },
    { 0, (char *) 0, (char *) 0, {0,1,0,0,0}, 1 },
    { 0, (char *) 0, (char *) 0, {0,1,1,0,0}, 2 }
};

FILE *my_fopen(char *name, char *mode) {
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a') {
        return NULL;
    }
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++) {
        if (!fp->flag._READ && !fp->flag._WRITE) {
            break; /* found free slot */
        }
    }
    if (fp >= _iob + OPEN_MAX) { /* no free slots */
        return NULL;
    }
    if (*mode == 'w') {
        fd = creat(name, PERMS);
    } else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0L, 2);
    } else {
        fd = open(name, O_RDONLY, 0);
    } 
    if (fd == -1) {/* couldn't access name */
        return NULL;
    }
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag = (*mode == 'r') ? (_flags) {1,0,0,0,0} : (_flags) {0,1,0,0,0};
    return fp;
}

 /* _fillbuf: allocate and fill input buffer */
int my_fillbuf(FILE *fp) {
    int bufsize;

    if (!fp->flag._READ || fp->flag._EOF || fp->flag._ERR) {
        return EOF;
    }
    bufsize = (fp->flag._UNBUF) ? 1 : BUFSIZ;
    if (fp->base == NULL) { /* no buffer yet */
        if ((fp->base = (char *) malloc(bufsize)) == NULL) {
            return EOF; /* can't get buffer */
        }
    }
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {
        if (fp->cnt == -1) {
            fp->flag._EOF = 1;
        } else {
            fp->flag._ERR = 1;
        }
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}

int main (int argc, char* argv[]) {
    return 0;
}