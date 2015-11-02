/* leap.c */
/* Date  : 14 July 2015
 * Author: Ankit Pati
 */

#include <stdio.h>

int main()
{
    unsigned y;
    printf("Enter a year:\n");
    scanf(" %u%*c", &y);
         if(!(y%400)) puts("Leap");
    else if(!(y%100)) puts("Not Leap");
    else if(!(y%  4)) puts("Leap");
    else              puts("Not Leap");
    return 0;
}
/* end of leap.c */
