#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, i;
    char name[30], ch;
    long int prn;
    float marks;

    FILE *fp = fopen("student_details.txt", "a+");
    if (fp == NULL) {
        printf("cant open file");
        exit(0);
    }

    printf("Enter no of students: ");
    scanf("%d%*c", &n);

    for (i = 0; i < n; ++i) {
        printf("Enter student name %d: ", i + 1);
        fgets(name, 30, stdin);

        printf("Enter student prn %d: ", i + 1);
        scanf("%ld%*c", &prn);

        printf("Enter student marks %d: ", i + 1);
        scanf("%f%*c", &marks);

        fprintf(fp, "\n\nName:%s", name);
        fprintf(fp, "PRN:%ld", prn);
        fprintf(fp, "\nMarks:%f", marks);
    }
    rewind(fp);

    printf("----------------------------------------\n");
    printf("Content of the file\n");

    while ((ch = getc(fp)) != EOF) printf("%c", ch);

    fclose(fp);
    return 0;
}
