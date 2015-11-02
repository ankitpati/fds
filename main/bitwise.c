/* bitwise.c */
/* Date  : 14 July 2015
 * Author: Ankit Pati
 */

#include <stdio.h>

int main()
{
    int a=10, b=20, c, d, e, f;
    c=a&b;
    d=a|b;
    e=~a;
    f=a>>1;
    printf("%d %d %d %d\n", c, d, e, f);
    return 0;
}
/* end of bitwise.c */
