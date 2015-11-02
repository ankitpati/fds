/* posteval.c */
/* Date  : 06 October 2015
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define SIZE 40
struct stack          { float s[SIZE]; int top;  } st;
int stfull()          { return st.top >= SIZE-1; }
void push(float item) { st.s[++st.top]=item;     }
int stempty()         { return st.top==-1;       }
float pop()           { return st.s[st.top--];   }

float posteval(char *s)
{
    int i;
    float t1, t2; /* 1/2 = 0.5 in float, 0 in int */

    st.top=-1;

    for(i=0; s[i]; ++i){
        if(isspace(s[i])) continue;
        if( isdigit(s[i]) ){
            push(atoi(s+i));
            while( !isspace(s[i+1]) ) ++i;
        }
        else{
            t2=pop();
            t1=pop();
            switch(s[i]){
            case '+': push(t1+t2);        break;
            case '-': push(t1-t2);        break;
            case '/': push(t1/t2);        break;
            case '*': push(t1*t2);        break;
            case '%': push(fmod(t1, t2)); break;
            case '^': push(pow(t1, t2));  break;
            }
        }
    }
    return pop();
}

int main()
{
    char s[80];
    puts("Postfix Expression?");

    fgets(s, 80, stdin); s[strlen(s)-1]='\0';

    printf("= %f\n", posteval(s));
    return 0;
}
/* end of posteval.c */
