/*

   Simple histogram

*/

#include <stdio.h>
#include <stdlib.h>
#include <error.h>


#define N 5

void input_nums(unsigned int *);
void print_hist(unsigned int *);

int main() {
    
    unsigned int nums[N];
    
    input_nums(nums);
    print_hist(nums);

    return 0;
}

void input_nums(unsigned int *nums) {

    printf("Input %d integers: \n", N);
    
    for (unsigned int i = 0; i < N; i++) {
        int scanned = scanf("%u", &nums[i]);
        
        if (!scanned) {
            puts("Invalid input");
            exit(EXIT_FAILURE);
        }
    }
    
}

void print_hist(unsigned int *nums) {
    puts("The histogram looks like this: ");
    for (unsigned int i = 0; i < N; i++) {
        for (unsigned int j = 0; j < nums[i]; j++) {
            printf("%s", "*");
        }
        puts(" ");
    }
}