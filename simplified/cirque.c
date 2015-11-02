/* cirque.c */
/* Date  : 30 September 2015
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX 4

int cirq[MAX];
int front=0, rear=0, wrap=0;

void add(int p)
{
    if(rear==front && wrap){
        printf("Stack overflow!\n");
        return;
    }
    cirq[rear++]=p;
    if(rear==MAX){
        wrap=!wrap;
        rear=0;
    }
}

int del()
{
    int tmp;
    if(front==rear && !wrap){
        printf("Stack underflow!\n");
        return -1;
    }
    tmp=cirq[front++];
    if(front==MAX){
        wrap=!wrap;
        front=0;
    }
    return tmp;
}

int main()
{
    int ch;
    int p;
    do{
        puts("Choose an action");
        puts("0: Exit");
        puts("1: Add");
        puts("2: Del");
        scanf(" %d%*c", &ch);
        switch(ch){
        case 0:
            puts("Bye!");
            break;
        case 1:
            scanf(" %d%*c", &p);
            add(p);
            break;
        case 2:
            if((p=del())!=-1) printf("%d\n", p);
            break;
        default:
            printf("Invalid Input!\n");
            break;
        }
        putchar('\n');
    } while(ch);
    return 0;
}
/* end of cirque.c */
