/* sort.c */
/* Date  : 12 August 2015
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <stdlib.h>

int *bubsort(int *arr, unsigned n)
{
    unsigned i, j;
    int temp;
    for(i=0; i<n; ++i)
        for(j=0; j<n-i-1; ++j)
            if(arr[j+1]<arr[j]){
                temp     = arr[j+1];
                arr[j+1] = arr[j];
                arr[j]   = temp;
            }
    return arr;
}

int *inssort(int *arr, unsigned n)
{
    unsigned i, j;
    int temp;
    for(i=1; i<n; ++i){
        temp=arr[i];
        for(j=i; j && temp<arr[j-1]; --j) arr[j]=arr[j-1];
        arr[j]=temp;
    }
    return arr;
}

int *selsort(int *a, unsigned n)
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

/* quick sort */
void qikswap(int *a, unsigned i, unsigned j)
{
    int  temp;
    temp=a[i];
    a[i]=a[j];
    a[j]=temp;
}

int qikpart(int *a, unsigned left, unsigned right)
{
    size_t ileft;
    int piv;
    if(left>=right) return 0;

    piv=a[left];
    ileft=left+1;
    while(ileft<=right)
        if(a[ileft]<=piv) ++ileft;
        else if(a[right]<=piv) qikswap(a, ileft++, right--);
        else --right;

    qikswap(a, left, right);
    return right;
}

void qikcore(int *a, unsigned left, unsigned right)
{
    unsigned last;
    last=qikpart(a, left, right);
    if(!last) return;
    qikcore(a, left,  last-1);
    qikcore(a, last+1, right);
}

int *qiksort(int *a, unsigned n)
{
    qikcore(a, 0, n-1);
    return a;
}
/* end of quick sort */

/* merge sort */
int *merge(int *a, unsigned left, unsigned right)
{
    unsigned i, j, k, mid;
    int *tmp;
    if(!(tmp=malloc(sizeof(*tmp)*(right-left+1)))) return NULL;
    mid=left+(right-left)/2;
    i=left, j=mid+1, k=0;
    while(i<=mid && j<=right) tmp[k++]=a[i]<a[j]?a[i++]:a[j++];
    while(i<=mid  ) tmp[k++]=a[i++];
    while(j<=right) tmp[k++]=a[j++];
    for(i=left, j=0; j<k; ++i, ++j) a[i]=tmp[j];
    free(tmp);
    return a;
}

int *mrgcore(int *a, unsigned left, unsigned right)
{
    unsigned mid;
    if(left>=right) return a;
    mid=left+(right-left)/2;
    mrgcore(a, left,  mid);
    mrgcore(a, mid+1, right);
    return merge(a, left, right);
}

int *mrgsort(int *a, unsigned n)
{
    return mrgcore(a, 0, n-1);
}
/* end of merge sort */

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
    n=0;
    do{
        puts("What would you like to do?");
        puts(" ( 0) Exit");
        puts(" ( 1) Populate Array");
        puts(" ( 2) Print Array");
        puts(" ( 3) Bubble Sort");
        puts(" ( 4) Insertion Sort");
        puts(" ( 5) Selection Sort");
        puts(" ( 6) Quick Sort");
        puts(" ( 7) Merge Sort");
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
            bubsort(a, n);
            display(a, n);
            break;
        case 4:
            inssort(a, n);
            display(a, n);
            break;
        case 5:
            selsort(a, n);
            display(a, n);
            break;
        case 6:
            qiksort(a, n);
            display(a, n);
            break;
        case 7:
            mrgsort(a, n);
            display(a, n);
            break;
        default:
            puts("Incorrect Choice!");
            break;
        }
        putchar('\n');
    } while(ch);
    putchar('\n');
    return 0;
}
/* end of sort.c */

/* OUTPUT

What would you like to do?
 ( 0) Exit
 ( 1) Populate Array
 ( 2) Print Array
 ( 3) Bubble Sort
 ( 4) Insertion Sort
 ( 5) Selection Sort

1
Enter number of integers in array:
7
Enter 7 ints:
12 10 50 43 64 45 10

3 (Bubble Sort)
 10 10 12 43 45 50 64

1
Enter number of integers in array:
7
Enter 7 ints:
12 10 50 43 64 45 10

4 (Insertion Sort)
 10 10 12 43 45 50 64

1
Enter number of integers in array:
7
Enter 7 ints:
12 10 50 43 64 45 10

5 (Selection Sort)
 10 10 12 43 45 50 64

1
Enter number of integers in array:
7
Enter 7 ints:
12 10 50 43 64 45 10

6 (Quick Sort)
 10 10 12 43 45 50 64

7 (Merge Sort)
 10 10 12 43 45 50 64

0
Bye!

*/
