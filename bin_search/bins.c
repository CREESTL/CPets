#include <stdio.h>
#define SIZE 10
void printArr(int arr[]) {
	for(int i = 0; i < SIZE; i++) {
		printf("%d ", arr[i]);
	}
	puts("");
}
int binSearch(int arr[], int key, int low, int high) {
	int middle;
	while(low < high) {
		middle = (low + high) / 2;
		if (arr[middle] == key) return middle;
		else if (key < arr[middle]) high = middle - 1;
		else if (key > arr[middle]) low = low + 1;
	}
	return -1;
}
int main() {
	int arr[SIZE] = {-89, -8, 0, 0, 1, 88, 98, 108, 999, 2023};
	printArr(arr);
	int res = binSearch(arr, -8, 0, SIZE - 1);
	if (res == -1) puts("Not found");
	else printf("Found key on position %d\n", res);
	return 0;
};
