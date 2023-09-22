/*

   Exponentiate a number using recursion

*/

#include <stdio.h>

#define MAX_BASE 50
#define MAX_EXP 20


unsigned int pow(unsigned int, unsigned int);

int main(void)
{
    for (unsigned short base = 1; base < MAX_BASE + 1; base++)
    {
        for (unsigned short exp = MAX_EXP; exp > 0; exp--)
        {
            printf("%hu to the power of %hu is %u\n", base, exp, pow(base, exp));
        }
    }

    return 0;
}


unsigned int pow(unsigned int base, unsigned int exp)
{
    if (exp == 0)
        return 1;
    return base * pow(base, exp - 1);
}