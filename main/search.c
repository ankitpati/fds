/* search.c */
/* Date  : 07 August 2015
 * Author: Ankit Pati
 */

#include <stdio.h>

int *isort(int *arr, unsigned n)
{
    unsigned i, j, small;
    int temp;
    for(i=0; i<n; ++i){
        small=i;
        for(j=i+1; j<n; ++j)
            if(arr[j]<arr[small])
                small=j;
        temp       = arr[small];
        arr[small] = arr[i];
        arr[i]     = temp;
    }
    return arr;
}

int *linsrch(int *a, unsigned n, int key)
{
    unsigned i;
    for(i=0; i<n && a[i]!=key; ++i);
    return i==n?NULL:(a+i);
}

int *binsrch(int key, int *arr, unsigned n)
{
    unsigned high, low, mid;
    low=0, high=n-1;
    while(low<=high){
        mid=low+(high-low)/2;
        switch(arr[mid]==key){
        case 0:
            arr[mid]<key?(low=mid+1):(high=mid-1);
            break;
        case 1:
            return arr+mid;
            break;
        }
    }
    return NULL;
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
    unsigned i, n, ch;
    int a[50], key, *res, mul_pos[50];
    n=0;
    do{
        puts("What would you like to do?");
        puts(" ( 0) Exit");
        puts(" ( 1) Populate Array");
        puts(" ( 2) Print Array");
        puts(" ( 3) Linear Search");
        puts(" ( 4) Sort");
        puts(" ( 5) Binary Search");
        scanf(" %u%*c", &ch);
        switch(ch){
        case 0:
            puts("Bye!");
            break;
        case 1:
            accept(a, &n);
            break;
        case 2:
            display(a, n);
            break;
        case 3:
            puts("Key?");
            scanf(" %d%*c", &key);
            for(i=0, res=a-1; (res=linsrch(res+1, n, key)); ++i) mul_pos[i]=res-a+1;
            if(res==a) puts("Not found.");
            else{
                printf("Found at position(s): ");
                display(mul_pos, i);
            }
            break;
        case 4:
            isort(a, n);
            break;
        case 5:
            puts("Key?");
            scanf(" %d%*c", &key);
            if((res=binsrch(key, a, n)))
                printf("Found at position: %lld\n", (long long int)(res-a+1));
            else puts("Not found.");
            break;
        default:
            puts("Incorrect Choice!");
            break;
        }
    } while(ch);
    putchar('\n');
    return 0;
}
/* end of search.c */

/* OUTPUT

What would you like to do?
 ( 0) Exit
 ( 1) Populate Array
 ( 2) Print Array
 ( 3) Linear Search
 ( 4) Sort
 ( 5) Binary Search

1
Enter number of integers in array:
7
Enter 7 ints:
43 50 12 11 43 14 78

2
 43 50 12 11 43 14 78

3
Key?
43
Found at position(s):   1  5

4

2
 11 12 14 43 43 50 78

5
Key?
50
Found at position: 6

0
Bye!

*/
