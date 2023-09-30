/*

    Recursive selection sort

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selection_sort(int[], int, int);
void print_nums(int[], int);

int main(void)
{
    int nums[] = {0, 0, 0, 5, 32562, 3, 1, 100, -5};
    print_nums(nums, 9);
    selection_sort(nums, 0, 9);
    print_nums(nums, 9);
    return 0;
}

void print_nums(int nums[], int size)
{
    puts("Array is:");
    for (unsigned int i = 0; i < size; i++)
    {
        printf("%d ", nums[i]);
    }
    puts("");
}

void selection_sort(int nums[], int start, int size)
{
    // Base case
    if (start == size)
        return;
    int least = nums[start];
    int least_pos = start;
    for (unsigned int i = start; i < size; i++)
    {
        if (nums[i] < least)
        {
            least = nums[i];
            least_pos = i;
        }
    }
    int temp = nums[start];
    nums[start] = least;
    nums[least_pos] = temp;
    // Recursive step
    selection_sort(nums, start + 1, size);
}