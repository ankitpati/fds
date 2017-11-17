/* textcopy.c */
/* Text File Copy */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    int c;
    FILE *fin, *fout;

    if (argc != 3) {
        fprintf(stderr, "Usage:\n\ttextcopy <source> <destination>\n");
        exit(1);
    }

    if (!strcmp(argv[1], argv[2])) {
        fprintf(stderr, "Source and destination files cannot be same!\n");
        exit(2);
    }

    if (!(fin = fopen(argv[1], "r")) || !(fout = fopen(argv[2], "w"))) {
        fprintf(stderr, "File(s) could not be opened!\n");
        exit(5);
    }

    while ((c = fgetc(fin)) != EOF) fputc(c, fout);

    fclose(fout);
    fclose(fin);
    return 0;
}
/* end of textcopy.c */
