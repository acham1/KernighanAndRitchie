/**
 * Design and write _flushbuf, fflush, and fclose
 */

#include "my_stdio.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

/* _flushbuf: writes a char to buffer; if buffer is full then first write
 * buffer contents to file. 
 * returns c, or EOF if error.
 */
int _flushbuf(int c, FILE* stream) {
    if (!stream->flags._WRITE || stream->flags._EOF || stream->flags._ERR) {
        return EOF;        
    }
    /* check if need to allocate the buffer first */
    if (stream->base == NULL && !stream->flags._UNBUF) {
        stream->base = malloc(BUFSIZ);
        stream->ptr = stream->base;
        stream->cnt = BUFSIZ;
    }
    /* check if write to buffer or directly to file */
    if (stream->flags._UNBUF) {
        stream->ptr = NULL;
        stream->base = NULL;
        stream->count = 0;
        return (write(stream->fd, (unsigned char*) &c) <= 0) ? EOF : c;
    } else {
        /* number of chars written */
        int n = write(stream->fd, stream->base, stream->ptr - stream->base);
        n += write(stream->fd, (unsigned char*) &c, 1);
        stream->cnt = BUFSIZ;
        stream->ptr = stream->base;
        return (n == BUFSIZ + 1) ? c : EOF;
    }
}

/* fflush: return EOF if error, otherwise return 0 */
int fflush(File* stream) {
    int status = 0;
    if (stream == NULL) {
        for (File* f = _iob; f - _iob < OPEN_MAX; f++) {
            status = (f->flags._WRITE && fflush(f) == EOF) ? -1 : status;
        }
    } else {
        if (!stream->flags._WRITE) return EOF;
        _flushbuf(EOF, stream);
        if (stream->flags._ERR) return -1;
    }
    return status;
}

/* fclose: return 0 if successful, EOF otherwise */
int fclose(File* stream) {
    if (stream == NULL) {
        return EOF;
    }
    free(stream->base);
    stream->base = stream->ptr = NULL;
    stream->cnt = 0;
    stream->flags = (_flag) {0,0,0,0,0};
    return close(f->fd);
}