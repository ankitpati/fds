#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    char name[30];
    long int prn;
    float marks;
};

int main()
{
    int n, i;
    struct student s;
    fpos_t pos;

    FILE *fp = fopen("student_details.dat", "wb+");
    if (fp == NULL) {
        printf("cant open file");
        exit(0);
    }

    printf("Enter no of students: ");
    scanf("%d%*c", &n);

    for (i = 0; i < n; ++i) {
        printf("Enter student name %d: ", i + 1);
        fgets(s.name, 30, stdin);

        printf("Enter student prn %d: ", i + 1);
        scanf("%ld%*c", &s.prn);

        printf("Enter student marks %d: ", i + 1);
        scanf("%f%*c", &s.marks);

        if (i == 1) fgetpos(fp, &pos);

        fwrite(&s, sizeof(s), 1, fp);
    }

    fsetpos(fp, &pos);
    strcpy(s.name, "Overwrite");
    s.prn = 0;
    s.marks = 0.0;
    fwrite(&s, sizeof(s), 1, fp);

    rewind(fp);

    printf("----------------------------------------\n");
    printf("Content of the file\n");

    while (fread(&s, sizeof(s), 1, fp) == 1) {
        printf("Name : %s\n", s.name);
        printf("PRN  : %ld\n", s.prn);
        printf("Marks: %f\n", s.marks);
    }

    fclose(fp);
    return 0;
}
