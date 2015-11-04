/* in2pos.c */
/* Date  : 15 October 2015
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <ctype.h>

#define SIZE 40
struct stack        { int s[SIZE], top;        } st;
void push(int item) { st.s[++st.top]=item;     }
int pop()           { return st.s[st.top--];   }
int peek()          { return st.s[st.top];     }
int empty()         { return st.top==-1;       }

int priority(char x)
{
    switch(x){
    case '(':
        return 0;
    case '+': case '-':
        return 1;
    case '/': case '*': case '%':
        return 2;
    case '^':
        return 3;
    default:
        return 4;
    }
}

int main()
{
    int tk;
    st.top=-1;

    puts("Infix to Postfix. Enter infix expression:");

    while((tk=getchar())!='\n'){
             if(isalnum(tk)) putchar(tk);
        else if(tk == '(') push(tk);
        else if(tk == ')') while((tk=pop())!='(') putchar(tk);
        else{
            while(priority(tk)<=priority(peek()) && !empty()) putchar(pop());
            push(tk);
        }
    }

    while(!empty()) printf("%c", pop());

    return 0;
}
/* end of in2pos.c */
