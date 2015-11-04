/* swapwot.c */
/* Date  : 14 July 2015
 * Author: Ankit Pati
 */

#include <stdio.h>

int main()
{
    unsigned a, b;
    printf("Enter two numbers:\n");
    scanf(" %u %u%*c", &a, &b);
    printf("Entered       : %3u %3u\n", a, b);

    a=a+b;
    b=a-b;
    a=a-b;
    printf("Addition Swap : %3u %3u\n", a, b);

    a^=b;
    b^=a;
    a^=b;
    printf("XOR Swap      : %3u %3u\n", a, b);

    return 0;
}
/* end of swapwot.c */
