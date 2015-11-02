/* k_stack.c */
#include <stdio.h>

#define SIZE 5
struct stack        { int s[SIZE], top;        } st;
int stfull()        { return st.top >= SIZE-1; }
void push(int item) { st.s[++st.top]=item;     }
int stempty()       { return st.top==-1;       }
int pop()           { return st.s[st.top--];   }

void display()
{
    int i;
    if(stempty()) puts("Stack Underflow!");
    else for(i=st.top; i>=0; i--) printf(" %d ", st.s[i]);
}

int main()
{
    int item, choice;
    char ans;

    st.top=-1;

    puts("Implementation of Stack");

    do{
        puts("1. Push \n2. Pop \n3. Display");
        scanf(" %d%*c", &choice);
        switch(choice){
        case 1:
            puts("Enter item to push:");
            scanf(" %d%*c", &item);
            if(stfull()) puts("Stack Overflow!");
            else push(item);
            break;
        case 2:
            if(stempty()) puts("Stack Underflow!");
            else printf("Popped element: %d", pop());
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
/* end of k_stack.c */
