/*

   Fibonacci numbers without recursion

*/

#include <stdio.h>

#define MAX 30

// Calculate the n-th fibonacci number
double find_fibs(unsigned int);

int main(void)
{
    
    for (unsigned int i = 3; i < MAX + 1; i++)
    {
        printf("Fibonacci number #%u: %lf\n", i, find_fibs(i));
    }
    
    return 0;
}

double find_fibs(unsigned int n)
{
    
    unsigned int cur_num = 0;
    unsigned int next_num = 1;
    unsigned int count = 2;
    unsigned int sum = cur_num + next_num;
    
    while (count != n)
    {
        cur_num = next_num;
        next_num = sum;
        sum = cur_num + next_num;
        count++;
    }
    return next_num;
}