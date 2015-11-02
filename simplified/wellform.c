/* wellform.c */
/* Date  : 04 October 2015
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <string.h>

#define SIZE 40
struct stack        { int s[SIZE], top;        } st;
int stfull()        { return st.top >= SIZE-1; }
void push(int item) { st.s[++st.top]=item;     }
int stempty()       { return st.top==-1;       }
int pop()           { return st.s[st.top--];   }

int isformed(char *s)
{
    size_t i;
    st.top=-1;

    for(i=0; s[i]; ++i)
        switch(s[i]){
        case '[': case '{': case '(':
            push(s[i]);
            break;
        case ']':
            if('['!=pop()) return 0;
            break;
        case '}':
            if('{'!=pop()) return 0;
            break;
        case ')':
            if('('!=pop()) return 0;
            break;
        default:
            break;
        }

    return stempty();
}

int main()
{
    char s[80];
    puts("Enter an expression to verify well-formedness:");

    fgets(s, 80, stdin); s[strlen(s)-1]='\0';

    printf("Expression is %s-formed.\n", isformed(s)?"well":"ill");
    return 0;
}
/* end of wellform.c */
