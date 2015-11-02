/* expr.c */
/* Date  : 15 July 2015
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

double expr(char *s) /* s MUST be allocated with malloc() */
{
    double tmp, froms;
    unsigned opi, i, j, k, len, tmi, tlen;
    char op[]="^r/*%+-", curop[10], tms[320]; /* 320: more than maximum digits in "%lf" */

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
                    for(j=s[i+1]=='-'?i+2:i+1; s[j] && (isdigit(s[j]) || s[j]=='.'); ++j);
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
    char *s;
    printf("Enter an expression:\n");
    if(!(s=getstr())) goto alocerr;
    printf("= %lf\n", expr(s));
    free(s);
    return 0;
alocerr:
    fprintf(stderr, "Allocation Error! Core Dumped!\n");
    return 1;
}
/* end of expr.c */
