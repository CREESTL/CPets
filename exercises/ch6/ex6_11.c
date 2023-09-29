/*

Upgraded ascending bubblesort

*/

#include <stdbool.h>
#include <stdio.h>

#define SIZE 10

void bubble_sort(int[SIZE]);
void print_arr(int[SIZE]);

int main()
{

    // Full run
    int nums_1[SIZE] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    print_arr(nums_1);
    bubble_sort(nums_1);
    print_arr(nums_1);

    puts("");

    // Already sorted
    int nums_2[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    print_arr(nums_2);
    bubble_sort(nums_2);
    print_arr(nums_2);

    // Negative and positive
    int nums_3[SIZE] = {-10, -9, -10, 8, 8, 9, 555, 0, 1, 0};
    print_arr(nums_3);
    bubble_sort(nums_3);
    print_arr(nums_3);

    return 0;
}

void bubble_sort(int nums[SIZE])
{

    bool moved = false;
    for (unsigned int run = 0; run < SIZE - 1; run++)
    {
        printf("Run: %u\n", run);
        for (unsigned int i = 0; i < SIZE - 1 - run; i++)
        {
            printf("Comparing %d and %d\n", nums[i + 1], nums[i]);
            if (nums[i + 1] < nums[i])
            {
                puts("Switching them");
                int temp = nums[i];
                nums[i] = nums[i + 1];
                nums[i + 1] = temp;
                moved = true;
            }
        }
        // If no nums were moved, array is sorted
        if (!moved)
        {
            puts("No moves were made. Array is sorted");
            return;
        }
    }
}

void print_arr(int nums[SIZE])
{
    puts("Array is:");
    for (unsigned int i = 0; i < SIZE; i++)
    {
        printf("%d ", nums[i]);
    }
    puts("");
}