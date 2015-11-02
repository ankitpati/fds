/* swapwot.c */
/* Date  : 14 July 2015
 * Author: Ankit Pati
 */

#include <stdio.h>

int main()
{
    double a, b;
    printf("Enter two numbers:\n");
    scanf(" %lf %lf%*c", &a, &b);
    printf("Entered: %.2lf %.2lf\n", a, b);

    a+=b;
    b=a-b;
    a-=b;

    printf("Swapped: %.2lf %.2lf\n", a, b);
    return 0;
}
/* end of swapwot.c */
