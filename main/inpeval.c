/* inpeval.c */
/* Date  : 24 July 2015
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <math.h>

int main()
{
    double a, b;
    char op;
    printf("Enter two numbers separated by an operator:\n");
    scanf(" %lf %c %lf%*c", &a, &op, &b);
    printf("%.2lf %c %.2lf = %.2lf\n", a, op, b,
            (double)(op=='+'?a+b:op=='-'?a-b:op=='*'?a*b:op=='/'?a/b:op=='^'?
            pow(a, b):op=='r'?pow(b, 1.0/a):op=='%'?(unsigned)a%(unsigned)b:0));
    return 0;
}
/* end of inpeval.c */
