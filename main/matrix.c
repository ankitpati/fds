/* matrix.c */
/* Date  : 03 August 2015
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

mat mat_cpy(mat m)
{
    unsigned i, j;
    mat t;
    if(!(t=mat_alloc(m.r, m.c)).r) return t;
    t.r=m.r;
    t.c=m.c;
    for(i=0; i<m.r; ++i)
        for(j=0; j<m.c; ++j)
            *mat_indx(t, i, j)=*mat_indx(m, i, j);
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
mat mat_trn(mat m)
{
    unsigned i, j;
    mat t;
    t=mat_alloc(m.c, m.r);
    t.r=m.c;
    t.c=m.r;
    for(i=0; i<m.r; ++i)
        for(j=0; j<m.c; ++j)
            *mat_indx(t, j, i)=*mat_indx(m, i, j);
    return t;
}

mat mat_add(mat m1, mat m2)
{
    unsigned i, j;
    mat t;
    if(m1.r!=m2.r || m1.c!=m2.c){
        t.r=t.c=0;
        return t;
    }
    t=mat_alloc(m1.r, m1.c);
    t.r=m1.r;
    t.c=m1.c;
    for(i=0; i<m1.r; ++i)
        for(j=0; j<m1.c; ++j)
            *mat_indx(t, i, j)=*mat_indx(m1, i, j)+*mat_indx(m2, i, j);
    return t;
}

mat mat_sub(mat m1, mat m2)
{
    unsigned i, j;
    mat t;
    if(m1.r!=m2.r || m1.c!=m2.c){
        t.r=t.c=0;
        return t;
    }
    t=mat_alloc(m1.r, m1.c);
    t.r=m1.r;
    t.c=m1.c;
    for(i=0; i<m1.r; ++i)
        for(j=0; j<m1.c; ++j)
            *mat_indx(t, i, j)=*mat_indx(m1, i, j)-*mat_indx(m2, i, j);
    return t;
}

mat mat_mul(mat m1, mat m2)
{
    unsigned i, j, k;
    mat t;
    if(m1.c!=m2.r){
        t.r=t.c=0;
        return t;
    }
    if(!(t=mat_alloc(m1.r, m2.c)).r) return t;
    for(i=0; i<m1.r; ++i)
        for(j=0; j<m2.c; ++j)
            for(k=*mat_indx(t, i, j)=0; k<m2.r; ++k)
                *mat_indx(t, i, j)+=*mat_indx(m1, i, k)**mat_indx(m2, k, j);
    return t;
}

int issymm(mat m)
{
    unsigned i, j;
    if(m.r!=m.c) return 0;
    for(i=0; i<m.r; ++i)
        for(j=0; j<m.c; ++j)
            if(*mat_indx(m, i, j)!=*mat_indx(m, j, i))
                return 0;
    return 1;
}
/* end of matrix mathematical operations */

/* matrix miscellaneous operations */
void lo_tri(mat m)
{
    unsigned i, j;
    if(m.r!=m.c) puts("Not a Square Matrix");
    else{
        printf("Upper Triangular Matrix:\n");
        for(i=0; i<m.r; ++i){
            for(j=0; j<m.c; ++j)
                if(i<j)
                    printf("% 5d ", 0);
                else
                    printf("% 5d ", *mat_indx(m, i, j));
            putchar('\n');
        }
    }
}

void up_tri(mat m)
{
    unsigned i, j;
    if(m.r!=m.c) puts("Not a Square Matrix");
    else{
        printf("Lower Triangular Matrix:\n");
        for(i=0; i<m.r; ++i){
            for(j=0; j<m.c; ++j)
                if(i>j)
                    printf("% 5d ", 0);
                else
                    printf("% 5d ", *mat_indx(m, i, j));
            putchar('\n');
        }
    }
}

void row_great(mat m)
{
    unsigned i, j;
    mat_type gr;
    printf("Greatest Number:\n");
    for(i=0; i<m.r; ++i){
        for(j=0, gr=*mat_indx(m, i, 0); j<m.c; ++j)
            if(gr<*mat_indx(m, i, j))
                gr=*mat_indx(m, i, j);
        printf("Row %u: %u\n", i+1, gr);
    }
}

void add_major(mat m)
{
    unsigned i, j, sum;
    if(m.r!=m.c) puts("Not a Square Matrix");
    else{
        for(i=sum=0; i<m.r; ++i)
            for(j=0; j<m.c; ++j)
                if(i==j) sum+=*mat_indx(m, i, j);
        printf("Major Diagonal Sum: %u\n", sum);
    }
}

void add_minor(mat m)
{
    unsigned i, j, sum;
    if(m.r!=m.c)
        puts("Not a Square Matrix");
    else{
        for(i=sum=0; i<m.r; ++i)
            for(j=0; j<m.c; ++j)
                if(i==m.c-(j+1))
                    sum+=*mat_indx(m, i, j);
        printf("Minor Diagonal Sum: %u\n", sum);
    }
}
/* end of matrix miscellaneous operations */

int main()
{
    unsigned r1, c1, r2, c2, ch;
    mat m1, m2, t;

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

    do{
        puts("What would you like to do?");
        puts(" ( 0) Exit");
        puts(" ( 1) Display");
        puts(" ( 2) Transpose");
        puts(" ( 3) Sum");
        puts(" ( 4) Difference");
        puts(" ( 5) Product");
        puts(" ( 6) Greatest Element of Rows");
        puts(" ( 7) Sum of Major Diagonal");
        puts(" ( 8) Sum of Minor Diagonal");
        puts(" ( 9) Check Symmetricity");
        puts(" (10) Upper-Triangular Matrix");
        puts(" (11) Lower-Triangular Matrix");
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
            t=mat_trn(m1);
            mat_write(t);
            mat_free(t);
            break;
        case 3:
            if((t=mat_add(m1, m2)).r){
                mat_write(t);
                mat_free(t);
            }
            else puts("Not Possible");
            break;
        case 4:
            if((t=mat_sub(m1, m2)).r){
                mat_write(t);
                mat_free(t);
            }
            else puts("Not Possible");
            break;
        case 5:
            if((t=mat_mul(m1, m2)).r){
                mat_write(t);
                mat_free(t);
            }
            else puts("Not Possible");
            break;
        case 6:
            row_great(m1);
            break;
        case 7:
            add_major(m1);
            break;
        case 8:
            add_minor(m1);
            break;
        case 9:
            if(issymm(m1)) puts("Symmetric");
            else puts("Unsymmetric");
            break;
        case 10:
            up_tri(m1);
            break;
        case 11:
            lo_tri(m1);
            break;
        default:
            puts("Incorrect Choice!");
            break;
        }
        putchar('\n');
    } while(ch);

    mat_free(m1);
    mat_free(m2);
    return 0;
}
/* end of matrix.c */

/* OUTPUT

Enter row and column numbers of matrices 1 and 2:
3 3
3 3

Enter value of Matrix 1 (3x3):
4 5 4
5 6 5
4 5 4

Enter value of Matrix 2 (3x3):
2 6 7
3 2 1
6 5 0

What would you like to do?
 ( 0) Exit
 ( 1) Display
 ( 2) Transpose
 ( 3) Sum
 ( 4) Difference
 ( 5) Product
 ( 6) Greatest Element of Rows
 ( 7) Sum of Major Diagonal
 ( 8) Sum of Minor Diagonal
 ( 9) Check Symmetricity
 (10) Upper-Triangular Matrix
 (11) Lower-Triangular Matrix

1
Matrix 1:
    4     5     4
    5     6     5
    4     5     4

Matrix 2:
    2     6     7
    3     2     1
    6     5     0

2
    4     5     4
    5     6     5
    4     5     4

3
    6    11    11
    8     8     6
   10    10     4

4
    2    -1    -3
    2     4     4
   -2     0     4

5
   47    54    33
   58    67    41
   47    54    33

6
Greatest Number:
Row 1: 5
Row 2: 6
Row 3: 5

7
Major Diagonal Sum: 14

8
Minor Diagonal Sum: 14

9
Symmetric

10
Lower Triangular Matrix:
    4     5     4
    0     6     5
    0     0     4

11
Upper Triangular Matrix:
    4     0     0
    5     6     0
    4     5     4

0
Bye!

*/
