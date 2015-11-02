/* stringops.c
 * Date  : 26 August 2015
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <string.h>

/* manual string functions */
int str_len(char s[])
{
    int len=0;
    while(s[len]) ++len;
    return len;
}

int str_cmp(char s1[], char s2[])
{
    int i=0, j=0;
    while(s1[i] && s2[j] && s1[i]==s2[j]) ++i, ++j;
    return s1[i]-s2[j];
}

void str_cat(char s1[], char s2[])
{
    int i=0, j=0;
    while(s1[i]) ++i;
    while((s1[i++]=s2[j++]));
}

void str_cpy(char des[], char src[])
{
    int i=0, j=0;
    while((des[i++]=src[j++]));
}
/* end of manual string functions */

int main()
{
    char s1[80], s2[80];
    int ch, len1, len2;
    do{
        puts("What would you like to do?");
        puts(" ( 0) Exit");
        puts(" ( 1) Accept Strings\n");
        puts("Library Functions");
        puts(" ( 2) String Length");
        puts(" ( 3) String Compare");
        puts(" ( 4) String Concatenate");
        puts(" ( 5) String Copy\n");
        puts("Manually");
        puts(" ( 6) String Length");
        puts(" ( 7) String Compare");
        puts(" ( 8) String Concatenate");
        puts(" ( 9) String Copy");
        scanf(" %d%*c", &ch);
        switch(ch){
        case 0:
            puts("Bye!");
            break;
        case 1:
            puts("Enter two strings:");
            fgets(s1, 80, stdin);  /* to avoid the unsafe gets() function */
            s1[strlen(s1)-1]='\0'; /* to avoid a quirk of fgets() */
            fgets(s2, 80, stdin);
            s2[strlen(s2)-1]='\0';
            break;

        /* Library Functions */
        case 2:
            len1=strlen(s1);
            len2=strlen(s2);
            printf("String 1: %d\nString 2: %d\n", len1, len2);
            break;
        case 3:
            if(!strcmp(s1, s2)) puts("Strings are equal.");
            else puts("Strings not equal.");
            break;
        case 4:
            strcat(s1, s2);
            printf("Concatenated String: %s\n", s1);
            break;
        case 5:
            strcpy(s1, s2);
            printf("String 1: %s\nString 2: %s\n", s1, s2);
            break;
        /* end of Library Functions */

        /* Manually */
        case 6:
            printf("String 1: %d\nString 2: %d\n", str_len(s1), str_len(s2));
            break;
        case 7:
            if(!str_cmp(s1, s2)) puts("Strings are equal.");
            else puts("Strings not equal.");
            break;
        case 8:
            str_cat(s1, s2);
            printf("Concatenated String: %s\n", s1);
            break;
        case 9:
            str_cpy(s1, s2);
            printf("String 1: %s\nString 2: %s\n", s1, s2);
            break;
        /* end of Manually */

        default:
            puts("Incorrect Choice!");
            break;
        }
        putchar('\n');
    } while(ch);
    return 0;
}
/* end of stringops.c */

/* OUTPUT

What would you like to do?
 ( 0) Exit
 ( 1) Accept Strings

Library Functions
 ( 2) String Length
 ( 3) String Compare
 ( 4) String Concatenate
 ( 5) String Copy

Manually
 ( 6) String Length
 ( 7) String Compare
 ( 8) String Concatenate
 ( 9) String Copy

1
Enter two strings:
hello
world

2
String 1: 5
String 2: 5

3
Strings not equal.

4
Concatenated String: helloworld

5
String 1: world
String 2: world

1
Enter two strings:
lorem
lorem

6
String 1: 5
String 2: 5

7
Strings are equal.

8
Concatenated String: loremlorem

9
String 1: lorem
String 2: lorem

0
Bye!

*/
