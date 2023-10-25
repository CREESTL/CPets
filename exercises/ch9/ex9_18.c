/*

   Does `scanf` ignore ' ' or " " ?

   Test input:
   #1: croft
   #2: 'croft'
   #3: "croft"

*/

#include <stdio.h>

int main(void)
{
    
    char string[501];
    puts("Input a string:");
    scanf("%500s", string);
    printf("%s\n", string);
    return 0;
}