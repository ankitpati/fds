#include <stdio.h>
#include <stdlib.h>

int main()
{
    char str[20];

    FILE *fp = fopen("abc.txt", "w");
    if (fp == NULL) {
        printf("cant open file");
        exit(0);
    }

    printf("Enter some text: ");
    scanf("%s", str);

    fprintf(fp, "%s", str);

    fclose(fp);
    return 0;
}
