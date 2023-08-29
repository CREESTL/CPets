#include <stdio.h>
#define SIZE 10


void print_arr(int arr[]) {
    for(int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }
    puts("");
}

/*
   Bubble sort
*/

int main(void) {
    
    int arr[SIZE] = {6, 2, 99, 17, 0, -4, -4, 4, 0, 32000};
    int temp;
    
    print_arr(arr);

    for(int pass = 0; pass < SIZE - 1; pass++) {
        for(int i = 0; i < SIZE - 1; i++) {

            if (arr[i] > arr[i + 1]) {
                temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
            }
        }
    }
    
    print_arr(arr);

    return 0;
}