/* array.c */
/* Date  : 27 July 2015
 * Author: Ankit Pati
 */

#include <stdio.h>

void insert(int *a, unsigned *n, unsigned pos, int key)
{
    unsigned i;
    --pos;
    for(i=*n; i>pos; --i) a[i]=a[i-1];
    a[pos]=key;
    ++*n;
}

void delet(int *a, unsigned *n, unsigned pos)
{
    unsigned i;
    --pos;
    for(i=pos; i<*n; ++i) a[i]=a[i+1];
    --*n;
}

int *isort(int *arr, unsigned n)
{
    unsigned i, j, small;
    int temp;
    for(i=0; i<n; ++i){
        small=i;
        for(j=i; j<n; ++j)
            if(arr[j]<arr[small])
                small=j;
        temp       = arr[small];
        arr[small] = arr[i];
        arr[i]     = temp;
    }
    return arr;
}

int *msort(int *s, int *a, unsigned n, int *b, unsigned m)
{
    unsigned i, j, k;
    i=j=k=0;
    while(i<n && j<m)
        if(a[i]<b[j]) s[k++]=a[i++];
        else          s[k++]=b[j++];
    while(i<n) s[k++]=a[i++];
    while(j<m) s[k++]=b[j++];
    return s;
}

int main()
{
    unsigned i, j, n, m, ch;
    int a[50], b[50], s[50];

    puts("Enter number of elements in array 1:");
    scanf(" %u%*c", &n);
    puts("Enter contents of array 1:");
    for(i=0; i<n; ++i) scanf(" %u%*c", a+i);
    putchar('\n');

    puts("Enter number of elements in array 2:");
    scanf(" %u%*c", &m);
    puts("Enter contents of array 2:");
    for(i=0; i<m; ++i) scanf(" %u%*c", b+i);
    putchar('\n');

    do{
        puts("What would you like to do?");
        puts(" ( 0) Exit");
        puts(" ( 1) Display");
        puts(" ( 2) Insert an element");
        puts(" ( 3) Delete an element");
        puts(" ( 4) Sort");
        puts(" ( 5) Merge sort");
        scanf(" %u%*c", &ch);
        switch(ch){
        case 0:
            puts("Bye!");
            break;
        case 1:
            printf("Array 1:");
            for(i=0; i<n; ++i) printf(" %d", a[i]);
            putchar('\n');
            printf("Array 2:");
            for(i=0; i<m; ++i) printf(" %d", b[i]);
            break;
        case 2:
            puts("Enter a position and key to insert:");
            scanf(" %u %u%*c", &i, &j);
            insert(a, &n, i, j);
            printf("Inserted:");
            for(i=0; i<n; ++i) printf(" %d", a[i]);
            break;
        case 3:
            puts("Enter a position to delete:");
            scanf(" %u%*c", &i);
            delet(a, &n, i);
            printf("Deleted:");
            for(i=0; i<n; ++i) printf(" %d", a[i]);
            break;
        case 4:
            isort(a, n);
            printf("Sorted Array 1:");
            for(i=0; i<5; ++i) printf(" %d", a[i]);
            putchar('\n');
            isort(b, m);
            printf("Sorted Array 2:");
            for(i=0; i<m; ++i) printf(" %d", b[i]);
            break;
        case 5:
            msort(s, a, n, b, m);
            printf("Merged Array:");
            for(i=0; i<m+n; ++i) printf(" %d", s[i]);
            break;
        default:
            puts("Incorrect Choice!");
            break;
        }
        putchar('\n');
        putchar('\n');
    } while(ch);

    return 0;
}
/* end of array.c */

/* OUTPUT

Enter number of elements in array 1:
5
Enter contents of array 1:
43 56 50 45 65

Enter number of elements in array 2:
6
Enter contents of array 2:
65 43 54 57 89 21

What would you like to do?
 ( 0) Exit
 ( 1) Display
 ( 2) Insert an element
 ( 3) Delete an element
 ( 4) Sort
 ( 5) Merge sort

1
Array 1: 43 56 50 45 65
Array 2: 65 43 54 57 89 21

2
Enter a position and key to insert:
3 47
Inserted: 43 56 47 50 45 65

3
Enter a position to delete:
5
Deleted: 43 56 47 50 65

4
Sorted Array 1: 43 47 50 56 65
Sorted Array 2: 21 43 54 57 65 89

5
Merged Array: 21 43 43 47 50 54 56 57 65 65 89

0
Bye!

*/
