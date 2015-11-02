/* multistack.c */
/* Date  : 04 October 2015
 * Author: Ankit Pati
 */

#include <stdio.h>

/* multistack handling code */
#define MAX        16
#define MAX_ELEMS  4
#define MAX_STACKS ((MAX)/(MAX_ELEMS))

int stk[MAX], btm[MAX_STACKS], top[MAX_STACKS], lmt[MAX_STACKS];

void init()
{
    int i;
    for(i=0; i<MAX_STACKS; ++i){
        btm[i]=top[i]=i*MAX_ELEMS;
        lmt[i]=(i+1)*MAX_ELEMS;
    }
}

void push(int sno, int data)
{
    if(top[sno] < lmt[sno]) stk[top[sno]++]=data;
    else puts("Stack Overflow!");
}

int pop(int sno)
{
    if(top[sno] != btm[sno]) return stk[--top[sno]];
    else puts("Stack Underflow!");
    return 0;
}
/* end of multistack handling code */

int main()
{
    unsigned ch, sno;
    int data;
    init();
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
            push(sno, data);
            break;
        case 2:
            puts("Stack Number (0-4)?");
            scanf(" %u%*c", &sno);
            if((data=pop(sno))) printf("%d\n", data);
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
