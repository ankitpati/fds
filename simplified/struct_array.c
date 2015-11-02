/* struct_array.c */
/* Date  : 11 September 2015
 * Author: Ankit Pati
 */

/* !!! WARNING !!!
 * This code uses gets(). Do not use in production.
 */

#include <stdio.h>
#include <string.h>

typedef struct{
    char name[80], city[80];
    unsigned roll, mark;
} student;

student error={"", "", 0, 0};

void insert(student a[], unsigned n[], unsigned pos, student key)
{
    unsigned i;
    --pos;
    for(i=n[0]; i>pos; --i) a[i]=a[i-1];
    a[pos]=key;
    ++n[0];
}

void delet(student a[], unsigned n[], unsigned pos)
{
    unsigned i;
    --pos;
    for(i=pos; i<n[0]; ++i) a[i]=a[i+1];
    --n[0];
}

student srch_mark(student arr[], unsigned n, unsigned key)
{
    unsigned i;
    for(i=0; i<n && arr[i].mark!=key; ++i);
    return i==n?error:arr[i];
}

student srch_roll(student arr[], unsigned n, unsigned key)
{
    unsigned i;
    for(i=0; i<n && arr[i].roll!=key; ++i);
    return i==n?error:arr[i];
}

student srch_name(student arr[], unsigned n, char name[])
{
    unsigned i;
    for(i=0; i<n && strcmp(arr[i].name, name); ++i);
    return i==n?error:arr[i];
}

student srch_city(student arr[], unsigned n, char city[])
{
    unsigned i;
    for(i=0; i<n && strcmp(arr[i].city, city); ++i);
    return i==n?error:arr[i];
}

void sort_roll(student arr[], unsigned n)
{
    unsigned i, j, small;
    student temp;
    for(i=0; i<n; ++i){
        small=i;
        for(j=i; j<n; ++j)
            if(arr[j].roll<arr[small].roll)
                small=j;
        temp       = arr[small];
        arr[small] = arr[i];
        arr[i]     = temp;
    }
}

void sort_name(student arr[], unsigned n)
{
    unsigned i, j, small;
    student temp;
    for(i=0; i<n; ++i){
        small=i;
        for(j=i; j<n; ++j)
            if(strcmp(arr[j].name, arr[small].name)<0)
                small=j;
        temp       = arr[small];
        arr[small] = arr[i];
        arr[i]     = temp;
    }
}

void sort_city(student arr[], unsigned n)
{
    unsigned i, j, small;
    student temp;
    for(i=0; i<n; ++i){
        small=i;
        for(j=i; j<n; ++j)
            if(strcmp(arr[j].city, arr[small].city)<0)
                small=j;
        temp       = arr[small];
        arr[small] = arr[i];
        arr[i]     = temp;
    }
}

void sort_mark(student arr[], unsigned n)
{
    unsigned i, j, small;
    student temp;
    for(i=0; i<n; ++i){
        small=i;
        for(j=i; j<n; ++j)
            if(arr[j].mark<arr[small].mark)
                small=j;
        temp       = arr[small];
        arr[small] = arr[i];
        arr[i]     = temp;
    }
}

unsigned accept(student a[], unsigned n)
{
    char s[80];
    unsigned i, l;
    printf("Enter number of candidates: ");
    scanf(" %u%*c", &l);
    for(i=n; i<l; ++i){
        puts("Enter the following details:");
        printf(" - Name : ");
        gets(s);
        strcpy(a[i].name, s);

        printf(" - City : ");
        gets(s);
        strcpy(a[i].city, s);

        printf(" - Roll : ");
        scanf(" %u%*c", &a[i].roll);

        printf(" - Mark : ");
        scanf(" %u%*c", &a[i].mark);
        putchar('\n');
    }
    return n+l;
}

void display(student a[], unsigned n)
{
    unsigned i;
    printf("Name\tCity\tRoll\tMark\n");
    for(i=0; i<n; ++i)
        printf("%s\t%s\t%u\t%u\n", a[i].name, a[i].city, a[i].roll, a[i].mark);
    putchar('\n');
}

void display_one(student a)
{
    printf("Name\tCity\tRoll\tMark\n%s\t%s\t%u\t%u\n\n", a.name, a.city, a.roll,
                                                                        a.mark);
}

int is_equal(student a, student b)
{
    if(
        !strcmp(a.name, b.name) && !strcmp(a.city, b.city)
        && a.roll==b.roll && a.mark==b.mark
    ) return 1;
    return 0;
}

int main()
{
    char s[80];
    student a[50], key, res;
    unsigned ch, n, pos;
    n=0;
    do{
        puts("What would you like to do?");
        puts(" ( 0) Exit");
        puts(" ( 1) Enter details");
        puts(" ( 2) Show details");
        puts(" ( 3) Insert an element");
        puts(" ( 4) Delete an element");
        puts(" ( 5) Sort by Name");
        puts(" ( 6) Sort by City");
        puts(" ( 7) Sort by Roll");
        puts(" ( 8) Sort by Mark");
        puts(" ( 9) Search by Name");
        puts(" (10) Search by City");
        puts(" (11) Search by Roll");
        puts(" (12) Search by Mark");
        scanf(" %u%*c", &ch);
        switch(ch){
        case 0:
            puts("Bye!");
            break;
        case 1:
            n=accept(a, n);
            break;
        case 2:
            display(a, n);
            break;
        case 3:
            puts("Enter the following details:");
            printf(" - Name : ");
            gets(s);
            strcpy(key.name, s);

            printf(" - City : ");
            gets(s);
            strcpy(key.city, s);

            printf(" - Roll : ");
            scanf(" %u%*c", &key.roll);

            printf(" - Mark : ");
            scanf(" %u%*c", &key.mark);

            puts("Position?");
            scanf(" %u%*c", &pos);
            putchar('\n');

            insert(a, &n, pos, key);
            display(a, n);
            break;
        case 4:
            puts("Position?");
            scanf(" %u%*c", &pos);
            delet(a, &n, pos);
            display(a, n);
            break;
        case 5:
            sort_name(a, n);
            display(a, n);
            break;
        case 6:
            sort_city(a, n);
            display(a, n);
            break;
        case 7:
            sort_roll(a, n);
            display(a, n);
            break;
        case 8:
            sort_mark(a, n);
            display(a, n);
            break;
        case 9:
            puts("Name?");
            gets(s);
            res=srch_name(a, n, s);
            if(is_equal(res, error)) display_one(res);
            else puts("Not Found.");
            break;
        case 10:
            puts("City?");
            gets(s);
            res=srch_city(a, n, s);
            if(is_equal(res, error)) display_one(res);
            else puts("Not Found.");
            break;
        case 11:
            puts("Roll?");
            scanf(" %u%*c", &pos);
            res=srch_roll(a, n, pos);
            if(is_equal(res, error)) display_one(res);
            else puts("Not Found.");
            break;
        case 12:
            puts("Mark?");
            scanf(" %u%*c", &pos);
            res=srch_mark(a, n, pos);
            if(is_equal(res, error)) display_one(res);
            else puts("Not Found.");
            break;
        default:
            puts("Incorrect Choice!");
            break;
        }
        putchar('\n');
    } while(ch);
    return 0;
}
/* end of struct_array.c */

/* OUTPUT

What would you like to do?
 ( 0) Exit
 ( 1) Enter details
 ( 2) Show details
 ( 3) Insert an element
 ( 4) Delete an element
 ( 5) Sort by Name
 ( 6) Sort by City
 ( 7) Sort by Roll
 ( 8) Sort by Mark
 ( 9) Search by Name
 (10) Search by City
 (11) Search by Roll
 (12) Search by Mark

1
Enter number of candidates: 3
Enter the following details:
 - Name : TC
 - City : Kol
 - Roll : 43
 - Mark : 90
Enter the following details:
 - Name : AP
 - City : Mum
 - Roll : 45
 - Mark : 82
Enter the following details:
 - Name : MV
 - City : Del
 - Roll : 47
 - Mark : 65

2
Name    City    Roll    Mark
TC      Kol     43      90
AP      Mum     45      82
MV      Del     47      65

3
Enter the following details:
 - Name : SP
 - City : Hyd
 - Roll : 49
 - Mark : 80
Position?
2

Name    City    Roll    Mark
TC      Kol     43      90
SP      Hyd     49      80
AP      Mum     45      82
MV      Del     47      65

4
Position?
4
Name    City    Roll    Mark
TC      Kol     43      90
SP      Hyd     49      80
AP      Mum     45      82

5
Name    City    Roll    Mark
AP      Mum     45      82
SP      Hyd     49      80
TC      Kol     43      90

9
Name?
TC
Name    City    Roll    Mark
TC      Kol     43      90

0
Bye!

*/
