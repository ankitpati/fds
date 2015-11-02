/* bill.c */
/* Date  : 24 July 2015
 * Author: Ankit Pati
 */

#include <stdio.h>

int main()
{
    unsigned units;
    double bill;
    printf("Enter units consumed:\n");
    scanf(" %u%*c", &units);
         if(units<= 50) bill = 0.5*units;
    else if(units<=150) bill = 0.5*50 + 0.75*(units-50);
    else if(units<=250) bill = 0.5*50 + 0.75*100 + 1.2*(units-150);
    else                bill = 0.5*50 + 0.75*100 + 1.2*100 + 1.5*(units-250);
    bill*=1.3;
    printf("Bill: %.2lf\n", bill);
    return 0;
}
/* end of bill.c */
