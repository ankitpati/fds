/* expreval.c */
/* Date  : 25 September 2015
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

char *getstr()
{
    int c;
    size_t n;
    char *s, *t;
    if(!(s=t=malloc(1))) return NULL;
    for(n=0; (c=getchar())!=EOF && c-'\n' && (t=realloc(s, n+2)); s[n++]=c) s=t;
    if(!t){
        free(s);
        return NULL;
    }
    s[n]='\0';
    return s;
}

/* stack handling code */
#define MAX 40

/* operand stack */
typedef double stype;

typedef struct{
    stype data[MAX], *top;
} *stack;

stack st_init()
{
    stack stk;
    if(!(stk=malloc(sizeof(*stk)))) return NULL;
    stk->top=stk->data;
    return stk;
}

void st_push(stack stk, stype data)
{
    if(stk->top<stk->data+MAX) *stk->top++=data;
}

stype st_pop(stack stk)
{
    if(stk->top!=stk->data) return *--stk->top;
    return (stype)0;
}
/* end of operand stack */

/* operator stack */
typedef char optype;

typedef struct{
    optype data[MAX], *top;
} *opstk;

opstk op_init()
{
    opstk stk;
    if(!(stk=malloc(sizeof(*stk)))) return NULL;
    stk->top=stk->data;
    return stk;
}

void op_push(opstk stk, optype data)
{
    if(stk->top<stk->data+MAX) *stk->top++=data;
}

optype op_pop(opstk stk)
{
    if(stk->top!=stk->data) return *--stk->top;
    return (optype)0;
}
/* end of operator stack */
/* end of stack handling code */

/* expression evaluation code */
static char oplist[]=")^r/*%+-(";

#define EVAL(VAL_A, OPER, VAL_B) \
{\
    (VAL_A)=st_pop(ob);\
    (VAL_B)=st_pop(ob);\
    switch(OPER){\
    case '+': t1+=t2; break;\
    case '-': t1-=t2; break;\
    case '/': t1/=t2; break;\
    case '*': t1*=t2; break;\
    case '%': t1=fmod(t1, t2); break;\
    case 'r': t1=pow(t2, 1.0/t1); break;\
    case '^': t1=pow(t1, t2); break;\
    }\
    st_push(ob, t1);\
}

stype poseval(char *s)
{
    size_t i;
    stype t1, t2, ret;
    stack ob;

    ob=st_init();

    for(i=0; s[i]; ++i){
        if(isspace(s[i])) continue;
        if(isdigit(s[i]) || s[i]=='.'){
            st_push(ob, atof(s+i));
            while(s[i+1] && !isspace(s[i+1]) && !strchr(oplist, s[i+1])) ++i;
        }
        else EVAL(t2, s[i], t1);
    }

    ret=st_pop(ob);
    free(ob);
    return ret;
}

/* prefix */
stype precore(char *s, size_t *n)
{
    stype ret;
    optype curop;

    while(s[*n] && isspace(s[*n])) ++*n;
    if(strchr(oplist, s[*n])){
        curop=s[*n];
        ++*n;
        ret=precore(s, n);
        switch(curop){
        case '+': ret+=precore(s, n); break;
        case '-': ret-=precore(s, n); break;
        case '/': ret/=precore(s, n); break;
        case '*': ret*=precore(s, n); break;
        case '%': ret=fmod(ret, precore(s, n));    break;
        case 'r': ret=pow(precore(s, n), 1.0/ret); break;
        case '^': ret=pow(ret, precore(s, n));     break;
        }
    }
    else if(isdigit(s[*n])){
        ret=atof(s+*n);
        while(s[*n] && (isdigit(s[*n])  || s[*n]=='.')) ++*n;
    }

    return ret;
}

stype preeval(char *s)
{
    size_t n=0;
    return precore(s, &n);
}
/* end of prefix */

stype ineval(char *s)
{
    char curop, lc, *off;
    size_t i;
    stype t1, t2, ret;
    stack ob;
    opstk op;

    ob=st_init();
    op=op_init();

    for(i=0; s[i]; ++i){
        if(isspace(s[i])) continue;

        if(isdigit(s[i]) || s[i]=='.') st_push(ob, atof(s+i));
        while(s[i+1] && !strchr(oplist, s[i])) ++i;

        switch(s[i]){
        case '+': case '-':             lc='-'; break;
        case '/': case '*': case '%':   lc='%'; break;
        case 'r':                       lc='r'; break;
        case '^':                       lc='^'; break;

        case ')':
            while((curop=op_pop(op)) && curop!='(') EVAL(t2, curop, t1);
            continue;
        case '(':
            op_push(op, s[i]);
            continue;
        default:
            continue;
        }

        off=strchr(oplist, lc)+1;
        while((curop=op_pop(op)) && !strchr(off, curop)) EVAL(t2, curop, t1);

        if(curop) op_push(op, curop);
        op_push(op, s[i]);
    }

    while((curop=op_pop(op))) EVAL(t2, curop, t1);
    ret=st_pop(ob);
    free(ob);
    free(op);
    return ret;
}

#undef EVAL
/* end of expression evaluation code */

int main()
{
    unsigned ch;
    char *s;
    do{
        puts("What would you like to do?");
        puts(" ( 0) Exit");
        puts(" ( 1) Postfix Evaluation");
        puts(" ( 2) Prefix  Evaluation");
        puts(" ( 3) Infix   Evaluation");
        scanf(" %u%*c", &ch);
        switch(ch){
        case 0:
            puts("Bye!");
            break;
        case 1:
            puts("Expression?");
            if(!(s=getstr())) goto alocerr;
            printf("= %.2lf\n", poseval(s));
            free(s);
            break;
        case 2:
            puts("Expression?");
            if(!(s=getstr())) goto alocerr;
            printf("= %.2lf\n", preeval(s));
            free(s);
            break;
        case 3:
            puts("Expression?");
            if(!(s=getstr())) goto alocerr;
            printf("= %.2lf\n", ineval(s));
            free(s);
            break;
        default:
            puts("Incorrect Choice!");
            break;
        }
        putchar('\n');
    } while(ch);

    return 0;
alocerr:
    fprintf(stderr, "Allocation Error! Core Dumped!\n");
    return 12;
}
/* expreval.c */

/* OUTPUT

What would you like to do?
 ( 0) Exit
 ( 1) Postfix Evaluation
 ( 2) Prefix  Evaluation
 ( 3) Infix   Evaluation

1
Expression?
1 2 0 - + 4 5 - 6 7 - 8 + / *
= -0.43

2
Expression?
+ * + 1 - 2 3 4 / 5 6
= 0.83

3
Expression?
(5+6)*21-10/2
= 226.00

0
Bye!

*/
