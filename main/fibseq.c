/* fibseq.c */
/* Date  : 24 July 2015
 * Author: Ankit Pati
 */

#include <stdio.h>

void fibseq(unsigned n)
{
    unsigned i, x, y, t;
    puts("Fibonacci Series:");
    for(i=x=0, y=1; i<n; ++i){
        printf(" %u", t=x);
        x=y;
        y+=t;
    }
    putchar('\n');
}

int main()
{
    unsigned n;
    printf("Enter a number:\n");
    scanf(" %u%*c", &n);
    fibseq(n);
    return 0;
}
/* end of fibseq.c */
