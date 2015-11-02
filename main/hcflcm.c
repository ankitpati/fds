/* hcflcm.c */
/* Date  : 14 July 2015
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    unsigned a, b, i;
    printf("Enter two +ve integers:\n");
    scanf(" %u %u%*c", &a, &b);

    /* Method 1 */
    {
        for(i=a>b?a:b; a%i || b%i; --i);
        printf("\nHCF = %u\nLCM = %u\n", i, a*b/i);
    }

    /* Method 2 */
    {
        for(i=a>b?a:b; i%a || i%b; ++i);
        printf("\nLCM = %u\nHCF = %u\n", i, a*b/i);
    }

    return 0;
}
/* end of hcflcm.c */
