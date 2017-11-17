/* append-records.c */
/* Append student names to list. */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned i, n;
    char name[80];
    unsigned mark;
    FILE *fout;

    if (!(fout = fopen("stinfo.txt", "a"))) {
        fprintf(stderr, "File could not be opened!\n");
        exit(5);
    }

    printf("Number of Students? ");
    scanf(" %u%*c", &n);

    for (i = 0; i < n; ++i) {
        printf("\nStudent %u\n", i + 1);
        printf("Name  : ");
        fgets(name, 80, stdin);
        printf("Marks : ");
        scanf(" %u%*c", &mark);

        fprintf(fout, "%s%u\n", name, mark);
    }

    fclose(fout);
    return 0;
}
/* end of append-records.c */
