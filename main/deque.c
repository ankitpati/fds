/* deque.c */
/* Date  : 05 October 2015
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX 4

int que[MAX];
unsigned front=0, rear=0;

void add_front(int p)
{
    if(front) que[--front]=p;
    else puts("Queue Overflow!");
}

void add_rear(int p)
{
    if(rear!=MAX) que[rear++]=p;
    else puts("Queue Overflow!");
}

int del_front()
{
    int ret;
    if(front<rear){
        ret=que[front++];
        if(front==rear) front=rear=0;
        return ret;
    }
    else puts("Queue Underflow!");
    return -1;
}

int del_rear()
{
    int ret;
    if(front<rear){
        ret=que[--rear];
        if(front==rear) front=rear=0;
        return ret;
    }
    else puts("Queue Underflow!");
    return -1;
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
            add_front(p);
            break;
        case 2:
            scanf(" %d%*c", &p);
            add_rear(p);
            break;
        case 3:
            if((p=del_front())!=-1) printf("%d\n", p);
            break;
        case 4:
            if((p=del_rear())!=-1) printf("%d\n", p);
            break;
        default:
            puts("Invalid Input!");
            break;
        }
        putchar('\n');
    } while(ch);
    return 0;
}
/* end of deque.c */

/* OUTPUT

Choose an action
0: Exit
1: Add to   FRONT
2: Add to   REAR
3: Del from FRONT
4: Del from REAR

2 43

2 56

3
43

1 82

4
56

3
82

4
Queue Underflow!

*/
