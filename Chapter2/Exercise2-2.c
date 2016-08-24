/** Write a loop equivalent to the for loop above without using && or ||. */

#include <stdlib.h>
#include <stdio.h>

int main() {
	printf("Write a loop equivalent to the for loop above without using && or ||.\n\n");

	printf(
		"char c;\n"
		"int i = 0;\n"
		"for (i=0; i < lim-1;) {\n"
		"    if ((c = getchar()) != \'\\n\') {\n"
		"        if (c != EOF) {\n"
		"            s[i++] = c;\n"
		"        } else {\n"
		"            break;\n"
		"        }\n"
		"    } else {\n"
		"        break;\n"
		"    }\n"
		"}\n" );
	return EXIT_SUCCESS;
}
