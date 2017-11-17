#include <stdio.h>
#include <stdlib.h>

int main()
{
    rename("abc.txt", "def.txt");
    remove("def.txt");
    return 0;
}
