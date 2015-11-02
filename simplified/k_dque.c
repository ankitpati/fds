/* k_dque.c */
#include <stdio.h>

#define MAX 5

struct dqueue{
    int data[MAX];
    int rear,front;
} q;

void initialize()
{
    q.rear=q.front=-1;
}

void enqueue_rear(int item)
{
    if(q.rear == (MAX-1)) puts("Queue Overflow!");
    else{
        if(q.front==-1) q.front=0;
        q.rear=q.rear+1;
        q.data[q.rear]=item;
    }
}

void enqueue_front(int item)
{
    if(q.front<=0) puts("Queue Overflow!");
    else{
        q.front=q.front-1;
        q.data[q.front] = item;
    }
}

void dequeue_front()
{
    int no;
    if(q.front==-1) puts("Queue Underflow!");
    else{
        no=q.data[q.front];
        if(q.front==q.rear) q.front=q.rear=-1;
        else q.front= q.front+1;
    }
    printf("Deleted data is %d\n", no);
}

void dequeue_rear()
{
    int no;
    if(q.rear==-1) puts("Queue Underflow!");
    else{
        no=q.data[q.rear];
        if(q.front==q.rear) q.front=q.rear=-1;
        else q.rear=q.rear-1;
    }
    printf("Deleted data is %d\n", no);
}

void display()
{
    int i;
    if(q.front==-1) puts("Queue Underflow!");
    else{
        puts("Queue is:");
        for(i=q.front; i<=q.rear; ++i) printf(" %d ", q.data[i]);
    }
}

int main()
{
    int choice, item;
    char ans;
    initialize();
    do{
        puts("1. Insertion At Rear \n2. Insertion At Front \n3. Deletion At Front \n4: Deletion At Rear \n5. Display");
        scanf(" %d%*c", &choice);
        switch(choice){
        case 1:
            puts("Item?");
            scanf(" %d%*c", &item);
            enqueue_rear(item);
            break;
        case 2:
            puts("Item?");
            scanf(" %d%*c", &item);
            enqueue_front(item);
            break;
        case 3:
            dequeue_front();
            break;
        case 4:
            dequeue_rear();
            break;
        case 5:
            display();
            break;
        }
        puts("Continue?");
        scanf(" %c%*c", &ans);
    } while(ans=='Y' || ans=='y');
    return 0;
}
/* end of k_dque.c */
