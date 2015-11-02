/* floyd.c */
/* Date  : 24 July 2015
 * Author: Ankit Pati
 */

#include <stdio.h>

void floyd(unsigned n)
{
    unsigned i, j, k;
    for(i=k=1; i<=n; ++i){
        for(j=0; j<i; ++j, ++k)
            printf("%3u", k);
        putchar('\n');
    }
}

int main()
{
    unsigned n;
    printf("Enter a number:\n");
    scanf(" %u%*c", &n);
    floyd(n);
    return 0;
}
/* end of floyd.c */
