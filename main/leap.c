/* leap.c */
/* Date  : 14 July 2015
 * Author: Ankit Pati
 */

#include <stdio.h>

int isleap(unsigned year)
{
    return year%400?year%100?year%4?0:1:0:1;
}

int main()
{
    unsigned y;
    printf("Enter a year:\n");
    scanf(" %u%*c", &y);
    printf("%u is%s a leap year.", y, isleap(y)?"":" not");
    return 0;
}
/* end of leap.c */
