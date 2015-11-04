/* linklist.c */
/* Date  : 26 August 2015
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct{
    char name[80];
    struct{
        unsigned y, m, d;
    } dob, doj;
} empl;

typedef struct Node{
    empl data;
    struct Node *next;
} node;

node *first=NULL;

void push(empl data)
{
    node *tmp;
    if(!first){
        first=malloc(sizeof(*first));
        first->data=data;
        first->next=NULL;
        return;
    }
    for(tmp=first; tmp->next; tmp=tmp->next);
    tmp->next=malloc(sizeof(*first));
    tmp->next->data=data;
    tmp->next->next=NULL;
}

empl pop()
{
    node *tmp, *prev;
    empl ret={"", {0, 0, 0}, {0, 0, 0}};
    if(!first){
        fprintf(stderr, "pop(): Stack underflow!\n");
        return ret;
    }
    for(tmp=first; tmp->next; tmp=tmp->next) prev=tmp;
    if(tmp!=first) prev->next=NULL;
    else first=NULL;
    ret=tmp->data;
    free(tmp);
    return ret;
}

void del(unsigned n)
{
    unsigned i;
    node *tmp, *prev;
    if(!first) return;
    --n;
    for(tmp=first, i=0; tmp->next && i<n; tmp=tmp->next, ++i) prev=tmp;
    if(tmp!=first) prev->next=tmp->next;
    else first=tmp->next;
    free(tmp);
}

void mod(empl data, unsigned n)
{
    unsigned i;
    node *tmp;
    if(!first) return;
    --n;
    for(tmp=first, i=0; tmp->next && i<n; tmp=tmp->next, ++i);
    tmp->data=data;
}

void accept(empl *a)
{
    char *s;
    puts("Enter details (all dates in ISO yyyy-mm-dd format):");
    printf("- Name : "); s=getstr(); strcpy(a->name, s); free(s);
    printf("- DOB  : "); scanf(" %u-%u-%u%*c", &(a->dob.y), &(a->dob.m), &(a->dob.d));
    printf("- DOJ  : "); scanf(" %u-%u-%u%*c", &(a->doj.y), &(a->doj.m), &(a->doj.d));
}

void display(empl a)
{
    printf("- Name : %s\n- DOB  : %.4u-%.2u-%.2u\n- DOJ  : %.4u-%.2u-%.2u\n\n",
            a.name, a.dob.y, a.dob.m, a.dob.d, a.doj.y, a.doj.m, a.doj.d);
}

void linkdisp()
{
    node *tmp;
    for(tmp=first; tmp; tmp=tmp->next) display(tmp->data);
}

int main()
{
    unsigned ch, pos;
    empl data;
    do{
        puts("What would you like to do?");
        puts(" ( 0) Exit");
        puts(" ( 1) Add");
        puts(" ( 2) Display Last");
        puts(" ( 3) Delete");
        puts(" ( 4) Modify");
        puts(" ( 5) Display All");
        scanf(" %u%*c", &ch);
        switch(ch){
        case 0:
            puts("Bye!");
            break;
        case 1:
            accept(&data);
            push(data);
            break;
        case 2:
            display(pop());
            break;
        case 3:
                puts("Position?");
                scanf(" %u%*c", &pos);
                del(pos);
                break;
        case 4:
                puts("Position?");
                scanf(" %u%*c", &pos);
                accept(&data);
                mod(data, pos);
                break;
        case 5:
                linkdisp();
                break;
        default:
            puts("Incorrect Choice!");
            break;
        }
    } while(ch);
    putchar('\n');
    return 0;
}
/* end of linklist.c */

/* OUTPUT

What would you like to do?
 ( 0) Exit
 ( 1) Add
 ( 2) Display Last
 ( 3) Delete
 ( 4) Modify
 ( 5) Display All

1
Enter details (all dates in ISO yyyy-mm-dd format):
- Name : Tiashaa Chatterjee
- DOB  : 1995-12-13
- DOJ  : 2003-08-01

1
Enter details (all dates in ISO yyyy-mm-dd format):
- Name : Ankit Pati
- DOB  : 1996-04-02
- DOJ  : 2006-02-07

5
- Name : Tiashaa Chatterjee
- DOB  : 1995-12-13
- DOJ  : 2003-08-01

- Name : Ankit Pati
- DOB  : 1996-04-02
- DOJ  : 2006-02-07

3
Position?
2

5
- Name : Tiashaa Chatterjee
- DOB  : 1995-12-13
- DOJ  : 2003-08-01

4
Position?
1
Enter details (all dates in ISO yyyy-mm-dd format):
- Name : Tiashaa Chatterjee
- DOB  : 1995-12-13
- DOJ  : 2003-12-05

5
- Name : Tiashaa Chatterjee
- DOB  : 1995-12-13
- DOJ  : 2003-12-05

0
Bye!

*/
