/*

   Recursive inverse string

*/

#include <stdio.h>
#include <string.h>

void inverse_string(char*, int);

int main(void)
{
    char* string = "?skcus tsuR";
    int length = strlen(string);
    inverse_string(string, length - 1);
    return 0;
}

void inverse_string(char* string, int pos)
{
    if (pos < 0)
    {
        puts("");
        return;
    }
    printf("%c", string[pos]);
    inverse_string(string, pos - 1);
}