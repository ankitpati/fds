/* revnum.c */
/* Date  : 24 July 2015
 * Author: Ankit Pati
 */

#include <stdio.h>

unsigned revnum(unsigned n)
{
    unsigned rev=0;
    do rev=rev*10+n%10;
    while(n/=10);
    return rev;
}

int main()
{
    unsigned n;
    printf("Enter a number:\n");
    scanf(" %u%*c", &n);
    printf("Reversed: %u\n", revnum(n));
    return 0;
}
/* end of revnum.c */
