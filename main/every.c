/* every.c */
/* Date  : 31 July 2015
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

char *strrev(char *s)
{
    unsigned i, j;
    char t;
    for(i=0, j=strlen(s); i<j; ++i){
        t=s[i];
        s[i]=s[--j];
        s[j]=t;
    }
    return s;
}

unsigned revnum(unsigned n)
{
    unsigned rev=0;
    do rev=rev*10+n%10;
    while(n/=10);
    return rev;
}

int isleap(unsigned year)
{
    return year%400?year%100?year%4?0:1:0:1;
}

int iseven(unsigned n)
{
    return n&1?0:1;
    /* return n-(n>>1<<1)?0:1; */
    /* return n%2?0:1; */
}

int issquare(unsigned n)
{
    unsigned i;
    if(n==1) return 1;
    for(i=1; i<n && n!=i*i; ++i);
    return i==n?0:1;
}

int isprime(unsigned n)
{
    unsigned i;
    if(n==2 || n==3) return 1;
    else if(n==4) return 0;
    for(i=2; i<n/2 && n%i; ++i);
    return i==n/2;
}

int max(int a, int b, int c)
{
    return a>=b&&a>=c?a : b>=a&&b>=c?b : c;
}

void tobin(unsigned dec)
{
    unsigned i=0;
    char bin[sizeof(dec)*8+1];
    do bin[i++]='0'+dec%2;
    while(dec/=2);
    bin[i]='\0';
    printf("= %s in binary.\n", strrev(bin));
}

unsigned todec(unsigned bin)
{
    unsigned dec=0, p=1;
    do{
        dec+=bin%10*p;
        p*=2;
    } while(bin/=10);
    return dec;
}

void tooct(unsigned dec)
{
    unsigned i=0;
    char oct[32];
    do oct[i++]='0'+dec%8;
    while(dec/=8);
    oct[i]='\0';
    printf("= %s in octal.\n", strrev(oct));
}

void oct2bin(unsigned oct)
{
    char bin[32];
    bin[0]='\0';
    do{
        switch(oct%10){
        case 0:
            strcat(bin, "000");
            break;
        case 1:
            strcat(bin, "100");
            break;
        case 2:
            strcat(bin, "010");
            break;
        case 3:
            strcat(bin, "110");
            break;
        case 4:
            strcat(bin, "001");
            break;
        case 5:
            strcat(bin, "101");
            break;
        case 6:
            strcat(bin, "011");
            break;
        case 7:
            strcat(bin, "111");
            break;
        }
    } while(oct/=10);
    printf("= %s in binary.", strrev(bin));
}

void table(unsigned n)
{
    unsigned i;
    for(i=1; i<=10; ++i)
        printf("%2u x %2u = %3u\n", n, i, n*i);
}

void primefac(unsigned n)
{
    unsigned i=2;
    printf("Prime Factors: ");
    while(n>1)
        if(n%i==0 && isprime(i)) printf(" %u", i), n/=i;
        else ++i;
    putchar('\n');
}

void fibseq(unsigned n)
{
    unsigned i, x, y, t;
    puts("Fibonacci Series:");
    for(i=0, x=y=1; i<n; ++i){
        printf(" %u", t=x);
        x=y;
        y+=t;
    }
    putchar('\n');
}

void floyd(unsigned n)
{
    unsigned i, j, k;
    for(i=k=1; i<=n; ++i){
        for(j=0; j<i; ++j, ++k)
            printf(" %.2u", k);
        putchar('\n');
    }
}

void bill(unsigned units)
{
    double bill;
         if(units<= 50) bill = 0.5*units;
    else if(units<=150) bill = 0.5*50 + 0.75*(units-50);
    else if(units<=250) bill = 0.5*50 + 0.75*100 + 1.2*(units-150);
    else                bill = 0.5*50 + 0.75*100 + 1.2*100 + 1.5*(units-250);
    bill*=1.3;
    printf("Bill: %.2lf\n", bill);
}

double expr(char *s)
{
    double tmp, froms;
    unsigned opi, i, j, k, len, tmi, tlen;
    char op[]="^r/*%+-", curop[10], tms[320]; /* 320: maximum digits in "%lf" */

    for(opi=0; opi<4; ++opi)
        for(i=0; s[i]; ++i){
            switch(opi){
            case 0:
                strcpy(curop, "^");
                break;
            case 1:
                strcpy(curop, "r");
                break;
            case 2:
                strcpy(curop, "/*%");
                break;
            case 3:
                strcpy(curop, "+-");
                break;
            default:
                break;
            }

            tmp=s[i]=='-'?-atof(s+i+1):atof(s+i);

            for(tmi=i; s[i]; ++i){
                if(i && strchr(curop, s[i])){
                    len=strlen(s);

                    froms=s[i+1]=='-'?-atof(s+i+2):atof(s+i+1);
                    tmp=(double)(
                        s[i]=='+'?tmp+froms:
                        s[i]=='-'?tmp-froms:
                        s[i]=='*'?tmp*froms:
                        s[i]=='/'?tmp/froms:
                        s[i]=='^'?pow(tmp, froms):
                        s[i]=='r'?pow(froms, 1.0/tmp):
                        s[i]=='%'?(unsigned)tmp%(unsigned)froms:
                        0
                    );

                    sprintf(tms, "%lf", tmp);

                    tlen=strlen(tms);
                    for(
                        j=s[i+1]=='-'?i+2:i+1;
                        s[j] && (isdigit(s[j]) || s[j]=='.');
                        ++j
                    );
                    tlen+=len-(j-tmi);
                    if(len<tlen){
                        if(!(s=realloc(s, tlen+1))) return 0.0;
                        for(k=len-1; k>=j; --k) s[k+(tlen-len)]=s[k];
                    }
                    else{
                        for(k=j; k<len; ++k) s[k-(len-tlen)]=s[k];
                        if(!(s=realloc(s, tlen+1))) return 0.0;
                    }
                    for(k=0; tms[k]; ++k) s[tmi+k]=tms[k];
                    s[tlen]='\0';
                    i=tmi;
                }
                else if(i && strchr(op, s[i]) && !strchr(op, s[i-1])) break;
            }
        }
    return atof(s);
}

int main()
{
    unsigned a, b, c, ch;
    char *s;
    do{
        puts("What would you like to do?");
        puts(" ( 0) Exit");
        puts(" ( 1) Reverse String");
        puts(" ( 2) Reverse Number");
        puts(" ( 3) Evaluate Expression");
        puts(" ( 4) Even/Odd");
        puts(" ( 5) Maximum of 3 numbers");
        puts(" ( 6) Decimal to Binary");
        puts(" ( 7) Binary  to Decimal");
        puts(" ( 8) Octal   to Binary");
        puts(" ( 9) Decimal to Octal");
        puts(" (10) Print even numbers from 1 to 100");
        puts(" (11) Multiplication Table");
        puts(" (12) Reciprocal");
        puts(" (13) Electricity Bill");
        puts(" (14) Perfect Square");
        puts(" (15) Prime Factors");
        puts(" (16) Fibonacci Series");
        puts(" (17) Leap Year");
        puts(" (18) Floyd's Triangle");
        scanf(" %u%*c", &ch);
        switch(ch){
        case 0:
            puts("Bye!");
            break;
        case 1:
            puts("String?");
            s=getstr();
            if(!s) goto alocerr;
            printf("Reversed String: %s\n", strrev(s));
            free(s);
            break;
        case 2:
            puts("Number?");
            scanf(" %u%*c", &a);
            printf("Reversed Number: %u\n", revnum(a));
            break;
        case 3:
            puts("Expression?");
            s=getstr();
            if(!s) goto alocerr;
            printf("= %lf\n", expr(s));
            free(s);
            break;
        case 4:
            puts("Number?");
            scanf(" %u%*c", &a);
            printf("%s\n", iseven(a)?"Even":"Odd");
            break;
        case 5:
            puts("3 numbers?");
            scanf(" %u %u %u%*c", &a, &b, &c);
            printf("max = %u\n", max(a, b, c));
            break;
        case 6:
            puts("Decimal?");
            scanf(" %u%*c", &a);
            tobin(a);
            break;
        case 7:
            puts("Binary?");
            scanf(" %u%*c", &a);
            printf("%u in decimal.\n", todec(a));
            break;
        case 8:
            puts("Octal?");
            scanf(" %u%*c", &a);
            oct2bin(a);
            break;
        case 9:
            puts("Decimal?");
            scanf(" %u%*c", &a);
            tooct(a);
            break;
        case 10:
            for(c=2; c<=100; c+=2)
                printf("%4u", c);
            putchar('\n');
            break;
        case 11:
            puts("Number?");
            scanf(" %u%*c", &a);
            table(a);
            break;
        case 12:
            puts("Number?");
            s=getstr();
            if(!s) goto alocerr;
            printf("Reciprocal = %lf\n", 1.0/expr(s));
            free(s);
            break;
        case 13:
            puts("Units Consumed?");
            scanf(" %u%*c", &a);
            bill(a);
            break;
        case 14:
            puts("Number?");
            scanf(" %u%*c", &a);
            printf("The number is %sperfect square.\n", issquare(a)?"":"not ");
            break;
        case 15:
            puts("Number?");
            scanf(" %u%*c", &a);
            primefac(a);
            break;
        case 16:
            puts("Number of Elements?");
            scanf(" %u%*c", &a);
            fibseq(a);
            break;
        case 17:
            puts("Year?");
            scanf(" %u%*c", &a);
            printf("%u is %s.\n", a, isleap(a)?"leap":"not leap");
            break;
        case 18:
            puts("Number of Rows?");
            scanf(" %u%*c", &a);
            floyd(a);
            break;
        default:
            puts("Incorrect Choice!");
        }
        putchar('\n');
    } while(ch);
    return 0;
alocerr:
    fprintf(stderr, "Allocation Error!\nCore Dumped!\n");
    return 1;
}
/* end of every.c */

/* OUTPUT

What would you like to do?
 ( 0) Exit
 ( 1) Reverse String
 ( 2) Reverse Number
 ( 3) Evaluate Expression
 ( 4) Even/Odd
 ( 5) Maximum of 3 numbers
 ( 6) Decimal to Binary
 ( 7) Binary  to Decimal
 ( 8) Octal   to Binary
 ( 9) Decimal to Octal
 (10) Print even numbers from 1 to 100
 (11) Multiplication Table
 (12) Reciprocal
 (13) Electricity Bill
 (14) Perfect Square
 (15) Prime Factors
 (16) Fibonacci Series
 (17) Leap Year
 (18) Floyd's Triangle

1
String?
hello, world
Reversed String: dlrow ,olleh

2
Number?
435
Reversed Number: 534

3
Expression?
43/5.2*5-52+5.3^3
= 138.223154

4
Number?
43
Odd

5
3 numbers?
56 45 21
max = 56

6
Decimal?
43
= 101011 in binary.

7
Binary?
1000
8 in decimal.

8
Octal?
751
= 111101001 in binary.
9
Decimal?
16
= 20 in octal.

10
   2   4   6   8  10  12  14  16  18  20  22  24  26  28  30  32  34  36  38 40
  42  44  46  48  50  52  54  56  58  60  62  64  66  68  70  72  74  76 78  80
  82  84  86  88  90  92  94  96  98 100

11
Number?
37
37 x  1 =  37
37 x  2 =  74
37 x  3 = 111
37 x  4 = 148
37 x  5 = 185
37 x  6 = 222
37 x  7 = 259
37 x  8 = 296
37 x  9 = 333
37 x 10 = 370

12
Number?
19
Reciprocal = 0.052632

13
Units Consumed?
53
Bill: 35.43

14
Number?
64
The number is perfect square.

15
Number?
1024
Prime Factors:  2 2 2 2 2 2 2 2 2 2

16
Number of Elements?
7
Fibonacci Series:
 1 1 2 3 5 8 13

17
Year?
1800
1800 is not leap.

18
Number of Rows?
5
 01
 02 03
 04 05 06
 07 08 09 10
 11 12 13 14 15

0
Bye!

*/
