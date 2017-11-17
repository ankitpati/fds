#include <stdio.h>
#include <stdlib.h>

int main()
{
    char ch[20];

    FILE *fp = fopen("abc.txt", "w");
    if (fp == NULL) {
        printf("cant open file");
        exit(1);
    }

    printf("\nEnter some text: ");
    scanf("%s", ch);
    fprintf(fp, "%s", ch);

    fclose(fp);
    return 0;
}
