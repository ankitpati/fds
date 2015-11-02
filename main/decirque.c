/* decirque.c */
/* Date  : 30 September 2015
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX 4

#define FRONT 0
#define REAR  1

int cirq[MAX];
unsigned front=0, rear=0, wrap=0;

void add(int l, int p)
{
    if(rear==front && wrap){
        puts("Stack overflow!");
        return;
    }
    if(l){
        cirq[rear++]=p;
        if(rear==MAX){
            wrap=!wrap;
            rear=0;
        }
    }
    else{
        if(--front==~0u){
            wrap=!wrap;
            front=MAX-1;
        }
        cirq[front]=p;
    }
}

int del(int l)
{
    int tmp;
    if(front==rear && !wrap){
        printf("Stack underflow!\n");
        return -1;
    }
    if(l){
        if(--rear==~0u){
            wrap=!wrap;
            rear=MAX-1;
        }
        tmp=cirq[rear];
    }
    else{
        tmp=cirq[front++];
        if(front==MAX){
            wrap=!wrap;
            front=0;
        }
    }
    return tmp;
}

int main()
{
    unsigned ch;
    int p;
    do{
        puts("Choose an action ");
        puts("0: Exit");
        puts("1: Add to   FRONT");
        puts("2: Add to   REAR ");
        puts("3: Del from FRONT");
        puts("4: Del from REAR ");
        scanf(" %u%*c", &ch);
        switch(ch){
        case 0:
            puts("Bye!");
            break;
        case 1:
            scanf(" %d%*c", &p);
            add(FRONT, p);
            break;
        case 2:
            scanf(" %d%*c", &p);
            add(REAR, p);
            break;
        case 3:
            if((p=del(FRONT))!=-1) printf("%d\n", p);
            break;
        case 4:
            if((p=del(REAR))!=-1) printf("%d\n", p);
            break;
        default:
            printf("Invalid Input!\n");
            break;
        }
        putchar('\n');
    } while(ch);
    return 0;
}
/* end of decirque.c */
