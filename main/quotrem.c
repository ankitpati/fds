/* quotrem.c */
/* Date  : 14 July 2015
 * Author: Ankit Pati
 */

#include <stdio.h>

int main()
{
    unsigned a, b;
    printf("Enter two +ve integers:\n");
    scanf(" %u %u%*c", &a, &b);
    printf("%u / %u = %u\n%u %% %u = %u\n", a, b, a/b, a, b, a%b);
    return 0;
}
/* end of quotrem.c */
