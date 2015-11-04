/* sparse.c */
/* Date  : 13 September 2015
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <stdlib.h>

/* matrix code */
void mat_read(int m[][80], int r, int c)
{
    int i, j;
    for(i=0; i<r; ++i)
        for(j=0; j<c; ++j)
            scanf(" %d%*c", &m[i][j]);
}

void mat_write(int m[][80], int r, int c)
{
    int i, j;
    for(i=0; i<r; ++i){
        for(j=0; j<c; ++j)
            printf("% 5d ", m[i][j]);
        putchar('\n');
    }
    putchar('\n');
}

void mat_add(int m1[][80], int r1, int c1, int m2[][80], int r2, int c2)
{
    int i, j;
    int m[80][80];
    if(r1!=r2 || c1!=c2) puts("Not Possible");
    else{
        for(i=0; i<r1; ++i)
            for(j=0; j<c1; ++j)
                m[i][j]=m1[i][j]+m2[i][j];
        mat_write(m, r1, c1);
    }
}
/* end of matrix code */

/* sparse code */
void sparsify(int sp[][80], int m[][80], int r, int c)
{
    int i, j, k;
    sp[0][0]=r;
    sp[0][1]=c;
    for(i=k=0; i<r; ++i)
        for(j=0; j<c; ++j)
            if(m[i][j]){
                ++k;
                sp[k][0]=i;
                sp[k][1]=j;
                sp[k][2]=m[i][j];
            }
    sp[0][2]=k;
}

void sp_add(int sp1[][80], int sp2[][80])
{
    int i, j, k, c;
    int sp[80][80];
    if(sp1[0][0]!=sp2[0][0] || sp1[0][1]!=sp1[0][1]){
        puts("Not Possible");
        return;
    }
    sp[0][0]=sp1[0][0];
    sp[0][1]=sp1[0][1];
    i=j=k=1;
    while(i<=sp1[0][2] && j<=sp2[0][2])
        if(sp1[i][0]==sp2[j][0] && sp1[i][1]==sp2[j][1]){
            for(c=0; c<3-1; ++c) sp[k][c]=sp1[i][c];
            sp[k][2]=sp1[i][2]+sp2[j][2];
            ++i, ++j, ++k;
        }
        else if(sp1[i][0]<sp2[j][0] || (sp1[i][0]==sp2[j][0] &&
                sp1[i][1]<sp2[j][1])){
            for(c=0; c<3; ++c) sp[k][c]=sp1[i][c];
            ++i, ++k;
        }
        else if(sp1[i][0]>sp2[j][0] || (sp1[i][0]==sp2[j][0] &&
                sp1[i][1]>sp2[j][1])){
            for(c=0; c<3; ++c) sp[k][c]=sp2[j][c];
            ++j, ++k;
        }

    while(i<=sp1[0][2]){
        for(c=0; c<3; ++c) sp[k][c]=sp1[i][c];
        ++i, ++k;
    }

    while(j<=sp2[0][2]){
        for(c=0; c<3; ++c) sp[k][c]=sp2[j][c];
        ++j, ++k;
    }

    sp[0][2]=k-1;

    mat_write(sp, k, 3);
}
/* end of sparse code */

int main()
{
    int r1, c1, r2, c2, ch;
    int m1[80][80], m2[80][80], sp1[80][80], sp2[80][80];

    puts("Enter row and column numbers of matrices 1 and 2:");
    scanf(" %u %u %u %u%*c", &r1, &c1, &r2, &c2);
    putchar('\n');

    printf("Enter value of Matrix 1 (%ux%u):\n", r1, c1);
    mat_read(m1, r1, c1);
    putchar('\n');
    printf("Enter value of Matrix 2 (%ux%u):\n", r2, c2);
    mat_read(m2, r2, c2);
    putchar('\n');

    sparsify(sp1, m1, r1, c1);
    sparsify(sp2, m2, r2, c2);

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
            mat_write(m1, r1, c1);
            putchar('\n');
            puts("Matrix 2:");
            mat_write(m2, r2, c2);
            break;
        case 2:
            mat_add(m1, r1, c1, m2, r2, c2);
            break;
        case 3:
            puts("Sparse Matrix 1:");
            mat_write(sp1, sp1[0][2]+1, 3);
            putchar('\n');
            puts("Sparse Matrix 2:");
            mat_write(sp2, sp2[0][2]+1, 3);
            break;
        case 4:
            sp_add(sp1, sp2);
            break;
        default:
            puts("Incorrect Choice!");
            break;
        }
        putchar('\n');
    } while(ch);

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
