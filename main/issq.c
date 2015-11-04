/* issq.c */
/* Date  : 24 July 2015
 * Author: Ankit Pati
 */

#include <stdio.h>

int issquare(unsigned n)
{
    unsigned i;
    if(n==1) return 1;
    for(i=1; i<n && n!=i*i; ++i);
    return i!=n;
}

int main()
{
    unsigned n;
    printf("Enter a number:\n");
    scanf(" %u%*c", &n);
    printf("The number is %sperfect square.\n", issquare(n)?"":"not ");
    return 0;
}
/* end of issq.c */
