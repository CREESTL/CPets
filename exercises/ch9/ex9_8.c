/*

    See the difference between %d and %i in scanf.

    Use input like:
    #1: 10 10
    #2: -10 -10
    #3: 010 010 (%i scans in octal)
    #4: 0x10 0x10 (%i scans in hex)

*/

#include <stdio.h>

int main(void)
{
    int x, y;
    puts("Inputs two numbers: ");
    scanf("%i%d", &x, &y);
    printf("%d %d\n", x, y);
    return 0;
}