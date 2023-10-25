/*

    Output 10 random numbers from array.
    Output total amount of printed characters.

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10
#define MIN 1
#define MAX 1000

void fill_arr(int *nums, int size)
{
    for (unsigned short i = 0; i < size - 1; i++)
    {
        nums[i] = MIN + rand() % (MAX - MIN + 1);
    }
}

void print_arr(int *nums, int size)
{
    unsigned int total_chars = 0;
    unsigned int string_chars = 0;
    printf("%s\t%s\n", "Value", "Total Characters");
    for (unsigned short i = 0; i < size - 1; i++)
    {
        printf("%d%n", nums[i], &string_chars);
        total_chars += string_chars;
        printf("\t%u\n", total_chars);
    }
}

int main(void)
{
    srand(time(NULL));
    int nums[SIZE];
    fill_arr(nums, SIZE);
    print_arr(nums, SIZE);
    return 0;
}
