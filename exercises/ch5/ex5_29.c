/*

Find the greatest common divisor using:
- Euclid's algorithm
- Recursion

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMS 500
#define MIN 1
#define MAX 1000

unsigned int gcd_e(unsigned int num_1, unsigned int num_2);
unsigned int gcd_r(unsigned int num_1, unsigned int num_2);

int main(void)
{

    srand(time(NULL));
    unsigned int num_1 = 0;
    unsigned int num_2 = 0;

    for (unsigned short i = 0; i < NUMS; i++)
    {
        num_1 = MIN + rand() % (MAX - MIN);
        num_2 = MIN + rand() % (MAX - MIN);

        printf("Greatest common divider for %u and %u is: %u (Euclid) %u (Recursive)\n", num_1, num_2,
               gcd_e(num_1, num_2), gcd_r(num_1, num_2));
    }
}

unsigned int gcd_e(unsigned int num_1, unsigned int num_2)
{
    while (num_1 != num_2)
    {
        if (num_1 > num_2)
            num_1 -= num_2;
        else
            num_2 -= num_1;
    }

    return num_1;
}

unsigned int gcd_r(unsigned int num_1, unsigned int num_2)
{
    if (num_2 == 0)
        return num_1;
    else
        return gcd_r(num_2, num_1 % num_2);
}