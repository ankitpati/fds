/* pointer.c */
/* Date  : 21 August 2015
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <stdlib.h>

char *getstr()
{
    int c;
    size_t n;
    char *s, *t;
    if(!(s=t=malloc(1))) return NULL;
    for(n=0; (c=getchar())!=EOF && c-'\n' && (t=realloc(s, n+2)); s[n++]=c) s=t;
    if(!t){
        free(s);
        return NULL;
    }
    s[n]='\0';
    return s;
}

char *strsearch(char *hay, char *ned)
{
    size_t pos, nlen, i;

    for(nlen=0; ned[nlen]; ++nlen);
    if(!nlen) return NULL;

    for(i=0; hay[i] && i<nlen; ++i);
    if(i!=nlen) return NULL;

    for(pos=0; hay[pos+nlen-1]; ++pos){
        for(i=0; i<nlen && (hay+pos)[i]==ned[i]; ++i);
        if(i==nlen) return hay+pos;
    }

    return NULL;
}

int *sort(int *a, unsigned n)
{
    unsigned i, j, small;
    int temp;
    for(i=0; i<n; ++i){
        small=i;
        for(j=i+1; j<n; ++j)
            if(a[j]<a[small])
                small=j;
        temp     = a[small];
        a[small] = a[i];
        a[i]     = temp;
    }
    return a;
}

int isleap(unsigned year)
{
    return year%400?year%100?year%4?0:1:0:1;
}

int isvaliddate(unsigned y, unsigned m, unsigned d)
{
    switch(m){
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        if(!d || d>31) return 0;
        break;
    case 2:
        if(isleap(y)){
            if(!d || d>29) return 0;
        }
        else if(!d || d>28) return 0;
        break;
    case 4: case 6: case 9: case 11:
        if(!d || d>30) return 0;
        break;
    default:
        return 0;
        break;
    }
    return 1;
}

void accept(int *a, unsigned *n)
{
    unsigned i;
    puts("Enter number of integers in array:");
    scanf(" %u%*c", n);
    printf("Enter %u ints:\n", *n);
    for(i=0; i<*n; ++i)
        scanf(" %d%*c", a+i);
}

void display(int *a, unsigned n)
{
    unsigned i;
    for(i=0; i<n; ++i)
        printf("%3d", a[i]);
    putchar('\n');
}

int main()
{
    unsigned n, ch;
    int a[50];
    char *s1, *s2, *f;
    unsigned y, m, d;
    n=0;
    do{
        puts("What would you like to do?");
        puts(" ( 0) Exit");
        puts(" ( 1) Populate Array");
        puts(" ( 2) Sort");
        puts(" ( 3) Check Date Validity");
        puts(" ( 4) String Search");
        scanf(" %u%*c", &ch);
        switch(ch){
        case 0:
            puts("Bye!");
            break;
        case 1:
            accept(a, &n);
            break;
        case 2:
            sort(a, n);
            puts("Sorted Array:");
            display(a, n);
            break;
        case 3:
            puts("Enter date in ISO format (yyyy-mm-dd):");
            if(scanf(" %u-%u-%u%*c", &y, &m, &d)<3 || !isvaliddate(y, m, d))
                puts("Invalid Date.");
            else puts("Valid Date.");
            break;
        case 4:
            puts("Enter first string:");
            s1=getstr();
            puts("Enter string to search:");
            s2=getstr();
            if(!(f=strsearch(s1, s2))) puts("Not Found.");
            else printf("Found at position: %u\n", (unsigned)(f-s1)+1);
            break;
        default:
            puts("Incorrect Choice!");
            break;
        }
    } while(ch);
    putchar('\n');
    return 0;
}
/* end of pointer.c */

/* OUTPUT

What would you like to do?
 ( 0) Exit
 ( 1) Populate Array
 ( 2) Sort
 ( 3) Check Date Validity
 ( 4) String Search

1
Enter number of integers in array:
7
Enter 7 ints:
12 10 50 43 64 45 10

2
Sorted Array:
 10 10 12 43 45 50 64

3
Enter date in ISO format (yyyy-mm-dd):
1995-12-13
Valid Date.

4
Enter first string:
hello, world
Enter string to search:
lo
Found at position: 4

0
Bye!

*/
