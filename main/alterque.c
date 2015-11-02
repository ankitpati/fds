/* alterque.c */
/* Date  : 01 November 2015
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX 40

typedef struct{
    int q[MAX];
    unsigned front, rear;
} *que;

que init()
{
    que q;
    if(!(q=malloc(sizeof(*q)))) puts("Allocation Error!");
    q->front=q->rear=0;
    return q;
}

void add(que q, int p)
{
    if(q->front==MAX) q->front=q->rear=0;
    if(q->rear<MAX) q->q[q->rear++]=p;
}

int del(que q)
{
    if(q->front<q->rear) return q->q[q->front++];
    return -1;
}

void display(que q)
{
    unsigned i;
    for(i=q->front; i<q->rear; ++i) printf("%d ", q->q[i]);
    putchar('\n');
}

void mergeque(que m, que q1, que q2)
{
    int p1, p2;
    do{
        if((p1=del(q1))!=-1) add(m, p1);
        if((p2=del(q2))!=-1) add(m, p2);
    } while(p1!=-1 || p2!=-1);
}

int main()
{
    unsigned ch;
    int p;
    que m, q1, q2;

    m=init();
    q1=init();
    q2=init();

    do{
        puts("Choose an action");
        puts("0: Exit");
        puts("1: Add to Queue 1");
        puts("2: Add to Queue 2");
        puts("3: Display Queue 1");
        puts("4: Display Queue 2");
        puts("5: Merge and Display");
        scanf(" %u%*c", &ch);
        switch(ch){
        case 0:
            puts("Bye!");
            break;
        case 1:
            scanf(" %d%*c", &p);
            add(q1, p);
            break;
        case 2:
            scanf(" %d%*c", &p);
            add(q2, p);
            break;
        case 3:
            display(q1);
            break;
        case 4:
            display(q2);
            break;
        case 5:
            mergeque(m, q1, q2);
            display(m);
            break;
        default:
            printf("Invalid Input!\n");
            break;
        }
        putchar('\n');
    } while(ch);

    return 0;
}
/* end of alterque.c */
