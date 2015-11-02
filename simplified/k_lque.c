/* k_lque.c */
#include <stdio.h>

#define MAX 2

struct lque{
    int data[MAX];
    int rear, front;
} q;

void initialize()
{
    q.rear=q.front=-1;
}

void enqueue(int item)
{
    if (q.front==-1)
    q.front=0;
    q.rear=q.rear+1;
    q.data[q.rear]=item;
}

void dequeue()
{
    int no;
    if(q.front==-1)
    puts("Queue Underflow");
    else{
        no=q.data[q.front];
        if(q.front==q.rear) q.front=q.rear=-1;
        else q.front=q.front+1;
        printf("Deleted data is %d", no);
    }
}

void display()
{
    int i;
    if(q.front==-1)
        puts("Queue Underflow");
        else{
            puts("Queue is");
            for(i=q.front; i<=q.rear; ++i) printf(" %d ", q.data[i]);
        }
}

int main()
{
    int choice, item;
    char ans;
    initialize();
    do{
        puts("Main Menu \n1. Insertion \n2. Deletion \n3. Display");
        scanf(" %d%*c", &choice);
        switch(choice){
        case 1:
            if(q.rear==(MAX-1)) puts("Queue Overflow");
            else{
                puts("Item?");
                scanf(" %d%*c", &item);
                enqueue(item);
            }
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
/* end of k_lque.c */
