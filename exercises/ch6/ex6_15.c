/*

Input 20 numbers 10-100
Only output unique numbers

*/

#include <stdbool.h>
#include <stdio.h>

#define SIZE 20

int main(void)
{

    unsigned int nums[SIZE];
    bool used[SIZE] = {};

    for (unsigned short i = 0; i < SIZE - 1; i++)
    {
        puts("Input a number");
        scanf("%u", &nums[i]);
        if (!used[nums[i]])
        {
            printf("A new unique number is: %u\n", nums[i]);
        }
        used[nums[i]] = true;
    }
    return 0;
}