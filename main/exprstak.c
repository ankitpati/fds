/* exprstak.c */
/* Date  : 25 September 2015
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* end of string handling code */
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

char *revexpr(char *s)
{
    size_t i, j, n;
    char temp;
    n=strlen(s);
    for(i=0, j=strlen(s); i<j; ++i){
        temp=s[i];
        s[i]=s[--j];
        s[j]=temp;
    }
    for(i=0; i<n; ++i) s[i]=='('?s[i]=')':s[i]==')'?s[i]='(':0;
    return s;
}
/* end of string handling code */

/* stack handling code */
#define MAX 40

typedef char stype;

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
/* end of stack handling code */

/* expression handling code */
char *in2pos(char *s)
{
#define STORE(CHAR) \
    {\
        char *tmp;\
        if(!(tmp=realloc(ret, rc+1))) goto alocerr;\
        ret=tmp;\
        ret[rc++]=(CHAR);\
    }

    stype curop, lc, *off, *ret, oplist[]=")^r/*%+-(";
    size_t i, rc;
    stack op;

    op=st_init();
    if(!(ret=malloc(1))) return NULL;
    rc=0;

    for(i=0; s[i]; ++i){
        if(isspace(s[i])) continue;

        if(!strchr(oplist, s[i])) STORE(s[i]);
        while(s[i+1] && !strchr(oplist, s[i])) ++i;

        switch(s[i]){
        case '+': case '-':             lc='-'; break;
        case '/': case '*': case '%':   lc='%'; break;
        case 'r':                       lc='r'; break;
        case '^':                       lc='^'; break;

        case ')':
            while((curop=st_pop(op)) && curop!='(') STORE(curop);
            continue;
        case '(':
            st_push(op, s[i]);
            continue;
        default:
            continue;
        }

        off=strchr(oplist, lc)+1;
        while((curop=st_pop(op)) && !strchr(off, curop)) STORE(curop);

        if(curop) st_push(op, curop);
        st_push(op, s[i]);
    }

    while((curop=st_pop(op))) STORE(curop);
    free(op);
    STORE('\0');
    return ret;
alocerr:
    free(ret);
    return NULL;
#undef STORE
}

char *in2pre(char *s)
{
    char *ret;
    revexpr(s);
    ret=revexpr(in2pos(s));
    revexpr(s);
    return ret;
}
/* end of expression handling code */

int main()
{
    unsigned ch;
    char *s;
    do{
        puts("What would you like to do?");
        puts(" ( 0) Exit");
        puts(" ( 1) Infix to Postfix");
        puts(" ( 2) Infix to Prefix");
        scanf(" %u%*c", &ch);
        switch(ch){
        case 0:
            puts("Bye!");
            break;
        case 1:
            puts("Expression?");
            if(!(s=getstr())) goto alocerr;
            printf("= %s\n", in2pos(s));
            free(s);
            break;
        case 2:
            puts("Expression?");
            if(!(s=getstr())) goto alocerr;
            printf("= %s\n", in2pre(s));
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
/* end of exprstak.c */

/* OUTPUT

What would you like to do?
 ( 0) Exit
 ( 1) Infix to Postfix
 ( 2) Infix to Prefix

1
Expression?
(A+(B-C))*((D-E)/(F-G+H))
= ABC-+DE-FG-H+/*

2
Expression?
(A+B-C)*D+E/F
= +*+A-BCD/EF

0
Bye!

*/
