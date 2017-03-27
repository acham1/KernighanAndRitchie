/**
 * Rewrite the program cat from Chapter 7 using read, write, open and close
 * instead of their standard library equivalents. Perform experiments to
 * determine the relative speeds of the two versions.
 */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

/* filecopy: copy from first file to second */
int filecopy(int descriptor1, int descriptor2) {
    char buffer[BUFSIZ];
    int n = 0;

    while (n = read(descriptor1, buffer, BUFSIZ)) {
        if (n == -1) break;
        write(descriptor2, buffer, n);
    }
    return n;
}

/* cat: concatenate files */
int main(int argc, char* argv[]) {
    int fileDescriptor;

    if (argc == 1) { /* no args; copy standard input */
        if (filecopy(0, 1) == -1) {
            /* error reading from stdin */
            char* errorMessage = "cat: error reading from stdin\n";
            write(2, errorMessage, strlen(errorMessage));
            return EXIT_FAILURE;
        }
    } else {
        while (--argc > 0) {
            if ((fileDescriptor = open(*++argv, O_RDONLY, 0)) == -1) {
                char* errorMessage = strcat(strcat("cat: can't open ", *argv), "\n");
                write(2, errorMessage, strlen(errorMessage));
                return EXIT_FAILURE;
            } else {
                filecopy(fileDescriptor, 1);
                close(fileDescriptor);
            }
        } 
    }
    return EXIT_SUCCESS;
}