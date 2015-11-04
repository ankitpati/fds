/* reverse.c */
/* Date  : 14 July 2015
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <string.h>
#include <math.h>

char *strrev(char *s)
{
    int i, j;
    char t;
    for(i=0, j=strlen(s)-1; i<j; ++i, --j){
        t=s[i];
        s[i]=s[j];
        s[j]=t;
    }
    return s;
}

int main()
{
    char s[82];
    unsigned n, nlen, ntmp;
    printf("Enter a string and a number.\n");
    fgets(s, 80, stdin);
    scanf(" %u%*c", &n);
    s[strlen(s)-1]='\0';

    nlen=0, ntmp=n;
    do ++nlen;
    while(ntmp/=10);
    ntmp=0;
    do ntmp+=(n%10)*pow(10, --nlen);
    while(n/=10);
    n=ntmp;

    printf("Reversed string:\n%s\n\nReversed number: %u\n", strrev(s), n);
    return 0;
}
/* end of reverse.c */
