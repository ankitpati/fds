/* poly.c */
/* Date  : 13 August 2015
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    double c, e;
} poly, mat_type;

/* matrix handling code */
typedef struct{
    mat_type *m;
    size_t r, c;
} mat;

mat_type *mat_indx(mat m, size_t r, size_t c)
{
    return m.m+m.c*r+c;
}

mat mat_alloc(size_t r, size_t c)
{
    mat m;
    if(!(m.m=malloc(sizeof(*m.m)*r*c))){
        m.r=m.c=0;
        return m;
    }
    m.r=r;
    m.c=c;
    return m;
}

mat mat_free(mat m)
{
    if(m.r && m.c) free(m.m);
    m.r=m.c=0;
    return m;
}
/* end of matrix handling code */

/* polynomial handling code */
size_t n;

poly *addpoly(poly *p1, size_t n1, poly *p2, size_t n2)
{
    size_t i, j, k;
    poly *p;
    i=j=k=n=0;
    if(!(p=malloc(sizeof(*p)*(n1+n2)))) return NULL;

    for(i=0; i<n1; ++i)
        for(j=0; j<n2; ++j)
            if(p1[i].e==p2[j].e){
                for(k=0; k<n && p1[i].e!=p[k].e; ++k);
                if(k==n){
                    p[n].c=p1[i].c+p2[j].c;
                    p[n].e=p1[i].e;
                    ++n;
                }
                else p[k].c=p1[i].c+p2[j].c;
            }
            else{
                for(k=0; k<n && p1[i].e!=p[k].e; ++k);
                if(k==n){
                    p[n].c=p1[i].c;
                    p[n].e=p1[i].e;
                    ++n;
                }
            }

    for(j=0; j<n2; ++j)
        for(i=0; i<n1; ++i)
            if(p2[j].e!=p1[i].e){
                for(k=0; k<n && p2[j].e!=p[k].e; ++k);
                if(k==n){
                    p[n].c=p2[j].c;
                    p[n].e=p2[j].e;
                    ++n;
                }
            }

    if(!(p=realloc(p, sizeof(*p)*(n)))) return NULL;

    return p;
}

poly *subpoly(poly *p1, size_t n1, poly *p2, size_t n2)
{
    size_t j;
    poly *p;
    for(j=0; j<n2; ++j) p2[j].c=-p2[j].c;
    p=addpoly(p1, n1, p2, n2);
    for(j=0; j<n2; ++j) p2[j].c=-p2[j].c;
    return p;
}

poly *mulpoly(poly *p1, size_t n1, poly *p2, size_t n2)
{
    size_t i, j, k;
    mat p;
    poly *f, *tmp;
    i=j=k=0;

    p=mat_alloc(n1, n2);

    for(i=0; i<n1; ++i)
        for(j=0; j<n2; ++j){
            mat_indx(p, i, j)->c=p1[i].c*p2[j].c;
            mat_indx(p, i, j)->e=p1[i].e+p2[j].e;
        }

    f=addpoly(mat_indx(p, 0, 0), n2, mat_indx(p, 1, 0), n2);
    for(i=2; i<n1; ++i){
        tmp=f;
        f=addpoly(f, n2, mat_indx(p, i, 0), n2);
        free(tmp);
    }

    mat_free(p);
    return f;
}

poly *readpoly(size_t n)
{
    size_t i;
    poly *p;
    if(!(p=malloc(sizeof(*p)*n))) return NULL;
    for(i=0; i<n; ++i)
        if(scanf(" %lf x ^ %lf%*c", &p[i].c, &p[i].e)<2) p[i].e=0;
    return p;
}

void writepoly(poly *p, size_t n)
{
    size_t i;
    for(i=0; i<n; ++i)
        printf("+ %.2lfx^%.2lf ", p[i].c, p[i].e);
}
/* end of polynomial handling code */

int main()
{
    poly *p, *q, *r;
    size_t i, j;
    unsigned ch;

    puts("Number of terms for 1st polynomial:");
    scanf(" %lu%*c", &i);
    puts("Terms of polynomial:");
    p=readpoly(i);
    putchar('\n');

    puts("Number of terms for 2nd polynomial:");
    scanf(" %lu%*c", &j);
    puts("Terms of polynomial:");
    q=readpoly(j);
    putchar('\n');

    do{
        puts("What would you like to do?");
        puts(" ( 0) Exit");
        puts(" ( 1) Add");
        puts(" ( 2) Subtract");
        puts(" ( 3) Multiply");
        scanf(" %u%*c", &ch);
        switch(ch){
        case 0:
            puts("Bye!");
            break;
        case 1:
            puts("Addition:");
            r=addpoly(p, i, q, j);
            writepoly(r, n);
            free(r);
            break;
        case 2:
            puts("Subtraction:");
            r=subpoly(p, i, q, j);
            writepoly(r, n);
            free(r);
            break;
        case 3:
            puts("Multiplication:");
            r=mulpoly(p, i, q, j);
            writepoly(r, n);
            free(r);
            break;
        default:
            puts("Incorrect Choice!");
            break;
        }
        putchar('\n');
        putchar('\n');
    } while(ch);

    return 0;
}
/* end of poly.c */

/* OUTPUT

Number of terms for 1st polynomial:
3
Terms of polynomial:
43x^1 12x^2 45x^3

Number of terms for 2nd polynomial:
4
Terms of polynomial:
4x^2 45x^3 45x^4 2x^5

What would you like to do?
 ( 0) Exit
 ( 1) Add
 ( 2) Subtract
 ( 3) Multiply

1
Addition:
+ 43.00x^1.00 + 16.00x^2.00 + 90.00x^3.00 + 45.00x^4.00 + 2.00x^5.00

2
Subtraction:
+ 43.00x^1.00 + 8.00x^2.00 + 0.00x^3.00 + -45.00x^4.00 + -2.00x^5.00

3
Multiplication:
+ 172.00x^3.00 + 1983.00x^4.00 + 2655.00x^5.00 + 2651.00x^6.00 + 2025.00x^7.00 + 90.00x^8.00

0
Bye!

*/
