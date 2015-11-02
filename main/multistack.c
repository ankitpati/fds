/* multistack.c */
/* Date  : 04 October 2015
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <stdlib.h>

/* multistack handling code */
#define MAX        16
#define MAX_ELEMS  4
#define MAX_STACKS ((MAX)/(MAX_ELEMS))

typedef int stype;

typedef struct{
    stype stk[MAX];
    size_t btm[MAX_STACKS], top[MAX_STACKS], lmt[MAX_STACKS];
} *mulstk;

mulstk mul_init()
{
    size_t i;
    mulstk mul;
    if(!(mul=malloc(sizeof(*mul)))) return NULL;

    for(i=0; i<MAX_STACKS; ++i){
        mul->btm[i]=mul->top[i]=i*MAX_ELEMS;
        mul->lmt[i]=(i+1)*MAX_ELEMS;
    }

    return mul;
}

void mul_push(mulstk mul, size_t sno, stype data)
{
    if(mul->lmt[sno] > mul->top[sno]) mul->stk[mul->top[sno]++]=data;
    else puts("Stack Overflow!");
}

stype mul_pop(mulstk mul, size_t sno)
{
    if(mul->top[sno] != mul->btm[sno]) return mul->stk[--mul->top[sno]];
    else puts("Stack Underflow!");
    return (stype)0;
}
/* end of multistack handling code */

int main()
{
    unsigned ch, sno;
    stype data;
    mulstk mul;
    mul=mul_init();
    do{
        puts("What would you like to do?");
        puts(" ( 0) Exit");
        puts(" ( 1) Push");
        puts(" ( 2) Pop");
        scanf(" %u%*c", &ch);
        switch(ch){
        case 0:
            puts("Bye!");
            break;
        case 1:
            puts("Stack Number (0-4)?");
            scanf(" %u%*c", &sno);
            puts("Data?");
            scanf(" %d%*c", &data);
            mul_push(mul, sno, data);
            break;
        case 2:
            puts("Stack Number (0-4)?");
            scanf(" %u%*c", &sno);
            if((data=mul_pop(mul, sno))) printf("%d\n", data);
            break;
        default:
            puts("Incorrect Choice!");
            break;
        }
    } while(ch);
    putchar('\n');
    return 0;
}
/* end of multistack.c */
