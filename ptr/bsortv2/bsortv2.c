#include <stdio.h>

#define SIZE 10

void bubbleSort(
    int arr[SIZE],
    int (*order) (int, int)
);

int ascending(int, int);
int descending(int, int);
void swap(int *aPtr, int *bPtr);

void printArr(int arr[SIZE]);


int main(void) {

    int order;
    int arr[SIZE] = {2, 6, 4, 8, 10, 12, 89, 68, 45, 37};
    puts("Enter '1' for ascending and '2' for descending order of sorting: ");
    scanf("%d", &order);
    
    puts("Initial array: ");
    printArr(arr); 
    puts("");

    switch (order) {
        case 1: 
            bubbleSort(arr, ascending);
            break;
        case 2: 
            bubbleSort(arr, descending);
    }
    
    puts("Sorted array: ");
    printArr(arr); 
    puts("");
    
    return 0;
}

void printArr(int arr[SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }
}

void bubbleSort(
    int arr[SIZE],
    int (*order) (int a, int b)
) {
    for(int pass = 0; pass < SIZE - 1;  pass++) {
        for(int i = 0; i < SIZE - 1; i++) {
            if ((*order)(arr[i], arr[i + 1]) == 0) {
                swap(&arr[i + 1], &arr[i]);
            }
        }
    }
}

int ascending(int a, int b) {
    return a < b;
}

int descending (int a, int b) {
    return a > b;
}

void swap(int *aPtr, int *bPtr) {
    int hold;
    hold = *bPtr;
    *bPtr = *aPtr;
    *aPtr = hold;
}