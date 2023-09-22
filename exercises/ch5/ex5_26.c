/*

   Find perfect numbers 1-1000
   Perfect number is a number that is equal to the 
   sum of its divisors

*/

#include <stdio.h>
#include <stdbool.h>

#define MAX 1e4

bool is_perfect(unsigned int);
void print_divisors(unsigned int);

int main(void)
{
    
    for (unsigned int i = 1; i < MAX; i++) {
        if (is_perfect(i))
        {
            printf("\n=== Perfect number: %u ===\n", i);
            print_divisors(i);
        }
    }
    return 0;
}



bool is_perfect(unsigned int num)
{
    unsigned int sum = 0;
    for (unsigned int i = 1; i < num; i++)
    {
        if (num % i == 0)
        {
            sum += i;
        }
    }
    return sum == num;
}

void print_divisors(unsigned int num)
{
    printf("Its divisors are:\n");
    for (unsigned int i = 1; i < num; i++)
    {
        if (num % i == 0)
        {
            printf("%u\n", i);
        }
    }
}