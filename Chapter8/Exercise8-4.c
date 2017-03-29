/* The standard library function
 * int fseek(FILE *fp, long offset, int origin) 
 * is identical to lseek except that fp is a file pointer instead of a file
 * descriptor and return value is an int status, not a position. Write fseek.
 * Make sure that your fseek coordinates properly with the buffering done for
 * the other functions of the library.
 */

#include <fcnt.h>
#include <unistd.h>
#include "my_stdio.h"

enum _origin {SEEK_SET, SEEK_CUR, SEEK_END};

extern int fflush(FILE * stream);

/* fseek origin must be SEEK_SET, SEEK_CUR, or SEEK_END
 * returns 0 on success, nonzero otherwise */
int fseek(FILE *fp, long offset, int origin) {
    int lseekOrigin; /* origin argument for lseek */
    switch (origin) {
        case SEEK_SET:
            lseekOrigin = 0;
            break;
        case SEEK_CUR:
            lseekOrigin = 1;
            break;
        case SEEK_END:
            lseekOrigin = 2;
            break;
        default:
            return EOF;
    }
    if (fp->flags._WRITE) {
        fflush(fp);
    } else if (fp->flags._READ) {
        f->cnt = 0;
        free(f->base);
        f->ptr = f->base = NULL;
    }
    return (lseek(fp->fd, offset, lseekOrigin) >= 0) ? 0 : EOF;
}