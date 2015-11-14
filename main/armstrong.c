/* armstrong.c */
/* Date  : 14 November 2015
 * Author: Ankit Pati
 */

#include <stdio.h>

int is_armstrong(unsigned n)
{
    unsigned bk, tmp, cube;
    bk = n, cube = 0;
    do tmp = bk % 10, cube += tmp * tmp * tmp;
    while(bk /= 10);
    return n == cube;
}

int main()
{
    unsigned i;
    for(i=0; i<3000; ++i)
        if(is_armstrong(i))
            printf("%d ", i);
    putchar('\n');
    return 0;
}
/* end of armstrong.c */
