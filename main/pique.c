/* pique.c */
/* Date  : 14 October 2015
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX 4

typedef struct{
    int pid, p;
} piq;

piq proc[4];

size_t front=0, rear=0;

void add(int pid, int p)
{
    piq t;

    if(rear==MAX){
        puts("Stack overflow!");
        return;
    }

    t.pid=pid;
    t.p=p;
    proc[rear++]=t;
}

int del()
{
    piq t;
    size_t i, low;

    if(front==rear){
        front=rear=0;
        puts("Stack underflow!");
        return -1;
    }

    for(i=low=front; i<rear; ++i)
        if(proc[i].p<proc[low].p)
            low=i;

    t=proc[low];
    for(i=low; i>front; --i) proc[i]=proc[i-1];
    ++front;

    return t.pid;
}

void display()
{
    size_t i;
    for(i=front; i<rear; ++i) printf("%d\t%d\n", proc[i].pid, proc[i].p);
}

int main()
{
    unsigned ch;
    int pid, p;
    do{
        puts("Choose an action");
        puts("0: Exit");
        puts("1: Add");
        puts("2: Del");
        puts("3: Display");
        scanf(" %d%*c", &ch);
        switch(ch){
        case 0:
            puts("Bye!");
            break;
        case 1:
            puts("PID and Priority?");
            scanf(" %d %d%*c", &pid, &p);
            add(pid, p);
            break;
        case 2:
            if((p=del())!=-1) printf("PID: %d\n", p);
            break;
        case 3:
            display();
            break;
        default:
            printf("Invalid Input!\n");
            break;
        }
        putchar('\n');
    } while(ch);
    return 0;
}
/* end of pique.c */
