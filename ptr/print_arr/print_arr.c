#include <stdio.h>
#define SIZE 4

int main(void) {
    
    int arr[SIZE] = {9, 88, 4, 11};
    int *arrPtr = arr;
    
    // Print with indexes
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }
    puts("");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", arrPtr[i]);
    }
    puts("");
    
    // Print with offsets
    for (int offset = 0; offset < SIZE; offset++) {
        printf("%d ", *(arr + offset));
    }
    puts("");
    for (int offset = 0; offset < SIZE; offset++) {
        printf("%d ", *(arrPtr + offset));
    }
    puts("");
    


    
    return 0;
}