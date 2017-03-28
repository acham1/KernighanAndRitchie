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
    if (!stream->flag._WRITE || stream->flag._EOF || stream->flag._ERR) {
        return EOF;        
    }
    /* check if need to allocate the buffer first */
    if (stream->base == NULL && !stream->flag._UNBUF) {
        stream->base = malloc(BUFSIZ);
        stream->ptr = stream->base;
        stream->cnt = BUFSIZ;
    }
    /* check if write to buffer or directly to file */
    if (stream->flag._UNBUF) {
        stream->ptr = NULL;
        stream->base = NULL;
        stream->cnt = 0;
        return (write(stream->fd, (unsigned char*) &c, 1) <= 0) ? EOF : c;
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
int fflush(FILE* stream) {
    int status = 0;
    if (stream == NULL) {
        FILE* f;
        for (f = _iob; f - _iob < OPEN_MAX; f++) {
            status = (f->flag._WRITE && fflush(f) == EOF) ? -1 : status;
        }
    } else {
        if (!stream->flag._WRITE) return EOF;
        _flushbuf(EOF, stream);
        if (stream->flag._ERR) return -1;
    }
    return status;
}

/* fclose: return 0 if successful, EOF otherwise */
int fclose(FILE* stream) {
    if (stream == NULL) {
        return EOF;
    }
    free(stream->base);
    stream->base = stream->ptr = NULL;
    stream->cnt = 0;
    stream->flag = (_flags) {0,0,0,0,0};
    return close(stream->fd);
}