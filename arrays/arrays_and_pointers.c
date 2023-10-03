/*

   Arrays and array pointers are the same thing in C

*/

#include <stdio.h>

void print(int arr[])
{
    for (int i = 0; i < 4; i++)
    {
        printf("%d ", arr[i]);
    }
    puts("");
}

// Array name + index
void increment_1(int arr[])
{
    for (int i = 0; i < 4; i++)
        arr[i]++;
}

// Array name + offset
void increment_2(int arr[])
{
    for (int i = 0; i < 4; i++)
        (*(arr + i))++;
}

// Pointer + index
void increment_3(int *arr_ptr)
{
    for (int i = 0; i < 4; i++)
        arr_ptr[i]++;
}

// Pointer + offset
void increment_4(int *arr_ptr)
{
    for (int i = 0; i < 4; i++)
        (*(arr_ptr + i))++;
}


int main(void)
{
    int arr[4] = {0};
    int* arr_ptr = &arr[0];
    // This is the same
    // int* arr_ptr = arr;

    // Increment all elements 4 times
    
    // First 2 functions take array name parameter
    print(arr);
    increment_1(arr);
    print(arr);
    increment_2(arr);
    // Last 2 functions take array pointer parameter
    print(arr);
    increment_3(arr_ptr);
    print(arr);
    increment_4(arr_ptr);
    print(arr);
    
    // We can pass pointer instead of array name
    increment_1(arr_ptr);
    print(arr);
    increment_2(arr_ptr);
    print(arr);
    
    // We can pass array name instead of pointer
    increment_3(arr);
    print(arr);
    increment_4(arr);
    print(arr);

    // Print first element in different ways 
    arr[0] = 999;

    // Array name
    printf("%d\n", *arr);
    // This won't work
    // printf("%d\n", arr);

    // Array name + index
    printf("%d\n", arr[0]);
    // Pointer + index
    printf("%d\n", arr_ptr[0]);

    // Array name + referece + index
    printf("%d\n", *(&arr[0]));
    // Pointer + reference + index
    printf("%d\n", *(&arr_ptr[0]));
}