/* iseven.c */
/* Date  : 14 July 2015
 * Author: Ankit Pati
 */

#include <stdio.h>

int main()
{
    unsigned n;
    printf("Enter a +ve integer:\n");
    scanf(" %d%*c", &n);
    printf("Bit Shift   : %d is %s.\n", n, n-(n>>1<<1)?"odd":"even"); /* Method 1 */
    printf("Bitwise And : %d is %s.\n", n, n&1?"odd":"even");         /* Method 2 */
    return 0;
}
/* end of iseven.c */
