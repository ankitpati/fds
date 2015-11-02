/* wellform.c */
/* Date  : 04 October 2015
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <stdlib.h>

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

typedef char stype;

typedef struct{
    stype data[MAX], *top;
} *stack;

stack stk;

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

int isformed(char *s)
{
    size_t i;
    stack br;
    br=st_init();

    for(i=0; s[i]; ++i)
        switch(s[i]){
        case '[': case '{': case '(':
            st_push(br, s[i]);
            break;
        case ']':
            if('['!=st_pop(br)) return 0;
            break;
        case '}':
            if('{'!=st_pop(br)) return 0;
            break;
        case ')':
            if('('!=st_pop(br)) return 0;
            break;
        default:
            break;
        }

    return !st_pop(br);
}

int main()
{
    char *s;
    puts("Enter an expression to verify well-formedness:");
    if(!(s=getstr())) goto alocerr;
    printf("Expression is %s-formed.\n", isformed(s)?"well":"ill");
    free(s);
    return 0;
alocerr:
    fprintf(stderr, "Allocation Error!\n");
    return 12;
}
/* end of wellform.c */
