/* linbreak.c */
/* Break arbitrary text input to 60-char lines. */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
    unsigned i;
    int c;
    FILE *fin, *fout;

    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");
    if (!fout && !fin) {
        fprintf(stderr, "File IO Error!\n");
        exit(5);
    }

    while (!feof(fin) && !ferror(fin) && !ferror(fout)) {
        i = 0;

        while (i < 60 && (c = getc(fin)) != EOF)
            if (!isspace(c)) {
                putc(c, fout);
                ++i;
            }

        fputc('\n', fout);
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
/* end of linbreak.c */
