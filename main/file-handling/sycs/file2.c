#include <stdio.h>
#include <stdlib.h>

int main()
{
    char ch;

    FILE *fp = fopen("abc.txt", "r");
    if (fp == NULL) {
        printf("cant open file");
        exit(1);
    }

    while ((ch = getc(fp)) != EOF) printf("%c", ch);

    fclose(fp);
    return 0;
}
