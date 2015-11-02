/* k_cque.c */
#include <stdio.h>

#define MAX 2

struct cqueue     { int data[MAX], rear, front;        } q;
void initialize() { q.rear=q.front=-1;                 }
int empty()       { return q.rear==-1;                 }
int full()        { return q.front == (q.rear+1)%MAX ; }

void enqueue(int item)
{
    if(full()){
        puts("Queue Overflow!");
        return;
    }
    if(q.front==-1) q.front=0;
    q.rear = (q.rear+1)%MAX;
    q.data[q.rear] = item;
}

void dequeue()
{
    if(empty()){
        puts("Queue Underflow!");
        return;
    }
    printf("Deleted data is %d\n", q.data[q.front]);
    if(q.front==q.rear) q.front=q.rear=-1;
    else q.front = (q.front+1)%MAX;
}

void display()
{
    int i;
    if(empty()){
        puts("Queue Underflow!");
        return;
    }

    puts("Queue is");
    if(q.front<=q.rear)
        for(i=q.front; i<=q.rear; ++i) printf(" %d ", q.data[i]);
    else{
        for(i=q.front; i<MAX; ++i) printf(" %d ", q.data[i]);
        for(i=0; i<=q.rear; ++i) printf(" %d ", q.data[i]);
    }
    putchar('\n');
}

int main()
{
    int choice, item;
    char ans;
    initialize();
    do{
        puts("1. Insert\n2. Delete\n3. Display\n4. Exit");
        scanf(" %d%*c", &choice);
        switch(choice){
        case 1:
            puts("Item?");
            scanf(" %d%*c", &item);
            enqueue(item);
            break;
        case 2:
            dequeue();
            break;
        case 3:
            display();
            break;
        }
        puts("Continue?");
        scanf(" %c%*c", &ans);
    } while(ans=='Y' || ans=='y');
    return 0;
}
/* end of k_cque.c */
