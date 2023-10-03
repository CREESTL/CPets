/*

   Recursive quicksort

*/

#include <stdio.h>

#define SIZE 10

// Performs a quick sort algorithm
void quick_sort(int *, int, int);
// Swaps two values
void swap(int *, int *);
// Places the pivot to it's correct position in the current array
// and returns this position
int move_pivot_and_split(int *, int, int);
// Prints the array
void print_arr(int *, int);

int main(void)
{
    int arr[SIZE] = {37, 2, 0, 4, 89, -400, 10, 12, 68, 45};
    print_arr(arr, SIZE);
    quick_sort(arr, 0, SIZE - 1);
    print_arr(arr, SIZE);
    return 0;
}

void quick_sort(int *arr, int start, int end)
{
    if (start < end)
    {
        // Place the pivot to it's correct position and arrange smaller and
        // and greater elements on the sides
        int new_pivot_pos = move_pivot_and_split(arr, start, end);
        // Apply quick sort onto the elements on the left side of the pivot
        quick_sort(arr, start, new_pivot_pos - 1);
        // Apply quick sort onto the elements on the right side of the pivot
        quick_sort(arr, new_pivot_pos + 1, end);
    }
}

int move_pivot_and_split(int *arr, int start, int end)
{
    // Pivot is always the last element of the array
    int pivot = arr[end];
    // Index of the last found element smaller than the pivot
    // Default value is -1
    int last_smaller = start - 1;
    for (unsigned int current = start; current < end; current++)
    {
        // If current element is smaller than the pivot,
        // swap this element and the element next to the last one found
        if (arr[current] < pivot)
        {
            swap(&arr[++last_smaller], &arr[current]);
        }
    }
    // Swap the pivot and the element next to the last one found
    swap(&arr[last_smaller + 1], &arr[end]);

    // As a result, all elements to the left of the pivot are smaller
    // than the pivot. And all elements to the right of the pivot are greater
    // than the pivot.

    // Return the new index of the pivot
    return (last_smaller + 1);
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void print_arr(int *arr, int size)
{
    puts("Array is:");
    for (unsigned int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    puts("");
}