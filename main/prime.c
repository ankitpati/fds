/* prime.c */
/* Date  : 24 July 2015
 * Author: Ankit Pati
 */

#include <stdio.h>

int isprime(unsigned n)
{
    unsigned i;
    if(n==2 || n==3) return 1;
    else if(n==4) return 0;
    for(i=2; i<n/2 && n%i; ++i);
    return i==n/2;
}

void primefac(unsigned n)
{
    unsigned i=2;
    printf("Prime Factors:");
    while(n>1)
        if(n%i==0 && isprime(i)) printf(" %u", i), n/=i;
        else ++i;
    putchar('\n');
}

int main()
{
    unsigned n;
    printf("Enter a number:\n");
    scanf(" %u%*c", &n);
    primefac(n);
    return 0;
}
/* end of prime.c */
