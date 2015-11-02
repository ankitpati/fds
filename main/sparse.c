/* sparse.c */
/* Date  : 13 September 2015
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <stdlib.h>

/* matrix handling code */
typedef int mat_type;

typedef struct{
    mat_type *m;
    unsigned r, c;
} mat;

mat_type *mat_indx(mat m, unsigned r, unsigned c)
{
    return m.m+m.c*r+c;
}

mat mat_alloc(unsigned r, unsigned c)
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

mat mat_realloc(mat m, unsigned r, unsigned c)
{
    unsigned i, j;
    mat t;
    if(!(t=mat_alloc(r, c)).r) return t;
    t.r=r;
    t.c=c;
    for(i=0; i<m.r && i<r; ++i)
        for(j=0; j<m.c && j<c; ++j)
            *mat_indx(t, i, j)=*mat_indx(m, i, j);
    mat_free(m);
    return t;
}
/* end of matrix handling code */

/* matrix I/O code */
mat mat_read(mat m)
{
    unsigned i, j;
    for(i=0; i<m.r; ++i)
        for(j=0; j<m.c; ++j)
            scanf(" %d%*c", mat_indx(m, i, j));
    return m;
}

mat mat_write(mat m)
{
    unsigned i, j;
    for(i=0; i<m.r; ++i){
        for(j=0; j<m.c; ++j)
            printf("% 5d ", *mat_indx(m, i, j));
        putchar('\n');
    }
    return m;
}
/* end of matrix I/O code */

/* matrix mathematical operations */
mat mat_add(mat m1, mat m2)
{
    unsigned i, j;
    mat t;
    if(m1.r!=m2.r || m1.c!=m2.c){
        t.r=t.c=0;
        return t;
    }
    else{
        t=mat_alloc(m1.r, m1.c);
        t.r=m1.r;
        t.c=m1.c;
        for(i=0; i<m1.r; ++i)
            for(j=0; j<m1.c; ++j)
                *mat_indx(t, i, j)=*mat_indx(m1, i, j)+*mat_indx(m2, i, j);
    }
    return t;
}
/* end of matrix mathematical operations */

/* sparse handling code */
mat sp_alloc(mat rg)
{
    unsigned i, j, k;
    mat sp;
    sp=mat_alloc(1, 3);
    *mat_indx(sp, 0, 0)=rg.r;
    *mat_indx(sp, 0, 1)=rg.c;
    for(i=k=0; i<rg.r; ++i)
        for(j=0; j<rg.c; ++j)
            if(*mat_indx(rg, i, j)){
                sp=mat_realloc(sp, k+2, 3);
                ++k;
                *mat_indx(sp, k, 0)=i;
                *mat_indx(sp, k, 1)=j;
                *mat_indx(sp, k, 2)=*mat_indx(rg, i, j);
            }
    *mat_indx(sp, 0, 2)=k;
    return sp;
}
/* end of sparse handling code */

/* sparse mathematical operations */
mat sp_add(mat sp1, mat sp2)
{
    unsigned i, j, k;
    mat sp;
    if(
        *mat_indx(sp1, 0, 0)!=*mat_indx(sp2, 0, 0) ||
        *mat_indx(sp1, 0, 1)!=*mat_indx(sp2, 0, 1)
    ){
        sp.r=sp.c=0;
        return sp;
    }
    sp=mat_alloc(1, 3);
    *mat_indx(sp, 0, 0)=sp1.r;
    *mat_indx(sp, 0, 1)=sp1.c;
    i=j=k=1;
    while(i<sp1.r && j<sp2.r)
        if(*mat_indx(sp1, i, 0)==*mat_indx(sp2, j, 0) &&
           *mat_indx(sp1, i, 1)==*mat_indx(sp2, j, 1)){
            sp=mat_realloc(sp, k+1, 3);
            *mat_indx(sp, k, 0)=*mat_indx(sp1, i, 0);
            *mat_indx(sp, k, 1)=*mat_indx(sp1, i, 1);
            *mat_indx(sp, k, 2)=*mat_indx(sp1, i, 2)+*mat_indx(sp2, j, 2);
            ++i, ++j, ++k;
        }
        else if(*mat_indx(sp1, i, 0)<*mat_indx(sp2, j, 0) ||
                (*mat_indx(sp1, i, 0)==*mat_indx(sp2, j, 0) &&
                 *mat_indx(sp1, i, 1)<*mat_indx(sp2, j, 1))){
            sp=mat_realloc(sp, k+1, 3);
            *mat_indx(sp, k, 0)=*mat_indx(sp1, i, 0);
            *mat_indx(sp, k, 1)=*mat_indx(sp1, i, 1);
            *mat_indx(sp, k, 2)=*mat_indx(sp1, i, 2);
            ++i, ++k;
        }
        else if(*mat_indx(sp1, i, 0)>*mat_indx(sp2, j, 0) ||
                (*mat_indx(sp1, i, 0)==*mat_indx(sp2, j, 0) &&
                 *mat_indx(sp1, i, 1)>*mat_indx(sp2, j, 1))){
            sp=mat_realloc(sp, k+1, 3);
            *mat_indx(sp, k, 0)=*mat_indx(sp2, j, 0);
            *mat_indx(sp, k, 1)=*mat_indx(sp2, j, 1);
            *mat_indx(sp, k, 2)=*mat_indx(sp2, j, 2);
            ++j, ++k;
        }

    while(i<sp1.r){
        sp=mat_realloc(sp, k+1, 3);
        *mat_indx(sp, k, 0)=*mat_indx(sp1, i, 0);
        *mat_indx(sp, k, 1)=*mat_indx(sp1, i, 1);
        *mat_indx(sp, k, 2)=*mat_indx(sp1, i, 2);
        ++i, ++k;
    }

    while(j<sp2.r){
        sp=mat_realloc(sp, k+1, 3);
        *mat_indx(sp, k, 0)=*mat_indx(sp2, j, 0);
        *mat_indx(sp, k, 1)=*mat_indx(sp2, j, 1);
        *mat_indx(sp, k, 2)=*mat_indx(sp2, j, 2);
        ++j, ++k;
    }

    *mat_indx(sp, 0, 2)=k-1;
    return sp;
}
/* end of sparse mathematical operations */

int main()
{
    unsigned r1, c1, r2, c2, ch;
    mat m1, m2, sp1, sp2, t;

    puts("Enter row and column numbers of matrices 1 and 2:");
    scanf(" %u %u %u %u%*c", &r1, &c1, &r2, &c2);
    putchar('\n');

    m1=mat_alloc(r1, c1);
    m2=mat_alloc(r2, c2);

    printf("Enter value of Matrix 1 (%ux%u):\n", r1, c1);
    mat_read(m1);
    putchar('\n');
    printf("Enter value of Matrix 2 (%ux%u):\n", r2, c2);
    mat_read(m2);
    putchar('\n');

    sp1=sp_alloc(m1);
    sp2=sp_alloc(m2);

    do{
        puts("What would you like to do?");
        puts(" ( 0) Exit");
        puts(" ( 1) Display");
        puts(" ( 2) Sum");
        puts(" ( 3) Sparse Display");
        puts(" ( 4) Sparse Sum");
        scanf(" %u%*c", &ch);
        switch(ch){
        case 0:
            puts("Bye!");
            break;
        case 1:
            puts("Matrix 1:");
            mat_write(m1);
            putchar('\n');
            puts("Matrix 2:");
            mat_write(m2);
            break;
        case 2:
            if((t=mat_add(m1, m2)).r){
                mat_write(t);
                mat_free(t);
            }
            else puts("Not Possible");
            break;
        case 3:
            puts("Sparse Matrix 1:");
            mat_write(sp1);
            putchar('\n');
            puts("Sparse Matrix 2:");
            mat_write(sp2);
            break;
        case 4:
            if((t=sp_add(sp1, sp2)).r){
                mat_write(t);
                mat_free(t);
            }
            else puts("Not Possible");
            break;
        default:
            puts("Incorrect Choice!");
            break;
        }
        putchar('\n');
    } while(ch);

    mat_free(m1);
    mat_free(m2);
    mat_free(sp1);
    mat_free(sp2);
    return 0;
}
/* end of sparse.c */

/* OUTPUT

Enter row and column numbers of matrices 1 and 2:
3 3
3 3

Enter value of Matrix 1 (3x3):
0 0 0
1 3 0
0 0 0

Enter value of Matrix 2 (3x3):
0 3 0
0 5 0
0 0 0

What would you like to do?
 ( 0) Exit
 ( 1) Display
 ( 2) Sum
 ( 3) Sparse Display
 ( 4) Sparse Sum

1
Matrix 1:
    0     0     0
    1     3     0
    0     0     0

Matrix 2:
    0     3     0
    0     5     0
    0     0     0

2
    0     3     0
    1     8     0
    0     0     0

3
Sparse Matrix 1:
    3     3     2
    1     0     1
    1     1     3

Sparse Matrix 2:
    3     3     2
    0     1     3
    1     1     5

4
    3     3     3
    0     1     3
    1     0     1
    1     1     8

0
Bye!

*/
