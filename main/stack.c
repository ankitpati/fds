/* stack.c */
/* Date  : 11 September 2015
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <stdlib.h>

char *getstr()
{
    int c;
    size_t n;
    char *s, *t;
    if(!(s=t=malloc(1))) return NULL;
    for(n=0; (c=getchar())!=EOF && c-'\n' && (t=realloc(s, n+2)); s[n++]=c) s=t;
    if(!t){
        free(s);
        return NULL;
    }
    s[n]='\0';
    return s;
}

/* stack handling code */
#define MAX 40

typedef int stype;

typedef struct{
    stype data[MAX], *top;
} *stack;

stack stk;

stack st_init()
{
    stack stk;
    if(!(stk=malloc(sizeof(*stk)))) return NULL;
    stk->top=stk->data;
    return stk;
}

void st_push(stack stk, stype data)
{
    if(stk->top<stk->data+MAX) *stk->top++=data;
}

stype st_pop(stack stk)
{
    if(stk->top!=stk->data) return *--stk->top;
    return (stype)0;
}
/* end of stack handling code */

void dec2bin(unsigned dec)
{
    unsigned bk=dec;
    do st_push(stk, dec%2);
    while(dec/=2);
    do printf("%u", st_pop(stk));
    while(bk/=2);
    putchar('\n');
}

int ispalin(char *s)
{
    char *bk=s;
    while(*s) st_push(stk, *s++);
    while(*bk)
        if(st_pop(stk)!=*bk++)
            return 0;
    return 1;
}

int main()
{
    unsigned ch, dec;
    char *s;
    do{
        puts("What would you like to do?");
        puts(" ( 0) Exit");
        puts(" ( 1) Decimal to Binary");
        puts(" ( 2) Palindrome Check");
        scanf(" %u%*c", &ch);
        switch(ch){
        case 0:
            puts("Bye!");
            break;
        case 1:
            stk=st_init();
            puts("Decimal Number?");
            scanf(" %u%*c", &dec);
            dec2bin(dec);
            free(stk);
            break;
        case 2:
            stk=st_init();
            puts("String?");
            s=getstr();
            if(ispalin(s)) puts("Palindrome");
            else puts("Not Palindrome");
            free(s);
            free(stk);
            break;
        default:
            puts("Incorrect Choice!");
            break;
        }
    } while(ch);
    putchar('\n');
    return 0;
}
/* end of stack.c */

/* OUTPUT

What would you like to do?
 ( 0) Exit
 ( 1) Decimal to Binary
 ( 2) Palindrome Check

1
Decimal Number?
43
101011

2
String?
racecar
Palindrome

0
Bye!

*/
