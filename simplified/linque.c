/* linque.c */
/* Date  : 30 September 2015
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX 40

int que[MAX];
int front=0, rear=0;

void add(int p)
{
    if(front==MAX) front=rear=0;
    if(rear<MAX) que[rear++]=p;
    else printf("Queue overflow!\n");
}

int del()
{
    if(front<rear) return que[front++];
    else printf("Queue underflow!\n");
    return -1;
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
        scanf(" %u%*c", &ch);
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
/* end of linque.c */
