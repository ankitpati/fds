/* octalbin.c */
/* Date  : 24 July 2015
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *strrev(char *s)
{
    unsigned i, j;
    char t;
    for(i=0, j=strlen(s); i<j; ++i){
        t=s[i];
        s[i]=s[--j];
        s[j]=t;
    }
    return s;
}

void tooct(unsigned dec)
{
    unsigned i=0;
    char oct[32];
    do oct[i++]='0'+dec%8;
    while(dec/=8);
    oct[i]='\0';
    printf("%s in octal.\n", strrev(oct));
}

void tobin(unsigned dec)
{
    unsigned i=0;
    char bin[sizeof(dec)*8+1];
    do bin[i++]='0'+(dec&1);
    while(dec/=2);
    bin[i]='\0';
    printf("%s in binary.\n", strrev(bin));
}

void oct2bin(unsigned oct)
{
    char bin[32];
    bin[0]='\0';
    do{
        switch(oct%10){
        case 0:
            strcat(bin, "000");
            break;
        case 1:
            strcat(bin, "100");
            break;
        case 2:
        strcat(bin, "010");
        break;
        case 3:
                strcat(bin, "110");
                break;
        case 4:
                strcat(bin, "001");
                break;
        case 5:
                strcat(bin, "101");
                break;
        case 6:
                strcat(bin, "011");
                break;
        case 7:
                strcat(bin, "111");
                break;
        }
        } while(oct/=10);
        printf("= %s in binary.", strrev(bin));
}

int main()
{
        unsigned oct;
/*      printf("Enter a decimal number:\n");
        scanf(" %u%*c", &dec);
        tooct(dec);
        tobin(dec);
*/
        printf("Enter an octal number:\n");
        scanf(" %u%*c", &oct);
        oct2bin(oct);
        return 0;
}
/* end of octalbin.c */
