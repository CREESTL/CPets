/*

   Inverse digits of the number

*/

#include <stdio.h>
#include <time.h>

#define TIMES 10
#define MAX 10000

unsigned int reverse(unsigned int);
unsigned short count_digits(unsigned int);

int main(void)
{

    srand(time(NULL));

    unsigned int num = 0;
    unsigned int r_num = 0;

    // Generate 10 random numbers to reverse
    for (unsigned int i = 0; i < TIMES; i++)
    {
        num = 1 + rand() % (MAX - 1);
        r_num = reverse(num);
        printf("%20s%u\n%s%u\n\n", "Number is: ", num, "Reversed number is: ", r_num);
    }
}

unsigned int reverse(unsigned int num)
{
    unsigned short num_digits = count_digits(num);
    unsigned int res = 0;
    unsigned short digit = 0;

    unsigned int count = num_digits;
    while (num > 0)
    {
        digit = num % 10;
        num /= 10;

        unsigned int ten = 1;
        for (unsigned int i = 1; i < count; i++)
        {
            ten *= 10;
        }
        res += digit * ten;

        count--;
    }
    return res;
}

unsigned short count_digits(unsigned int num)
{
    unsigned short count = 0;
    while (num > 0)
    {
        count += 1;
        num /= 10;
    }
    return count;
}