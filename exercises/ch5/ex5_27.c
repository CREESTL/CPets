
/*

   Find simple numbers 1-1000
   Simple number is a number that can only be divided
   by 1 and by itself

*/

#include <stdbool.h>
#include <stdio.h>

bool is_simple(unsigned int);
void print_divisors(unsigned int);

int main(void)
{
    for (unsigned int i = 1; i <= 1000; i++) 
    {
        if (is_simple(i))
        {
            printf("Simple number found: %u\n", i);
        }
    }

}


bool is_simple(unsigned int num) 
{
    for (unsigned int j = 2; j < num; j++)
    {
        if (num % j == 0)
            return false;
    }
    return true;
}