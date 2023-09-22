/*

   Calculate the power of the integer


*/

#include <error.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int power(unsigned int, unsigned short);

int main(void)
{

    unsigned int num;
    unsigned short pow;
    int scanned = 0;

    puts("Input a number: ");
    scanned = scanf("%u", &num);
    if (!scanned)
    {
        puts("Invalid input");
        exit(EXIT_FAILURE);
    }
    puts("Input a power: ");
    scanned = scanf("%hu", &pow);
    if (!scanned)
    {
        puts("Invalid input");
        exit(EXIT_FAILURE);
    }

    printf("The result is: %u\n", power(num, pow));

    return 0;
}

unsigned int power(unsigned int num, unsigned short pow)
{
    unsigned int res = 0;
    if (pow == 0)
        // Any number to the power of 0 is 1
        res = 1;
    else
    {
        for (unsigned short i = 0; i < pow; i++)
        {
            if (res == 0)
                res = num;
            else if (res * num > SHRT_MAX)
            {
                puts("Overflow");
                exit(EXIT_FAILURE);
            }
            res *= num;
        }
    }

    return res;
}
