/* bitext.c */
/* Date  : 14 July 2015
 * Author: Ankit Pati
 */

#include <stdio.h>

int main()
{
    unsigned n;
    printf("Enter a +ve integer:\n");
    scanf(" %u%*c", &n);
    printf("5th bit: %u\n6th bit: %u\n", n>>4&1, n>>5&1);
    return 0;
}
/* end of bitext.c */
