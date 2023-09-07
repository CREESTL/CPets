/*

   Input the limited number of integers. Calculate the sum of these integers.

*/

#include <stdio.h>
#include <stdlib.h>
#include <error.h>

int main() {
    
    unsigned int n; // number of integers
    unsigned int sum = 0; 
    unsigned int number;
    
    printf("Input the amount of integers: ");
    int scanned = scanf("%u", &n);
    
    if (!scanned) {
        puts("Invalid input");
        exit(EXIT_FAILURE);
    }

    for (unsigned int i = 0; i < n; i++) {
        printf("Input an integer: ");
        int scanned = scanf("%u", &number);

        if (!scanned) {
            puts("Invalid input");
            exit(EXIT_FAILURE);
        }

        sum += number;
    }
    
    printf("The total sum is: %u\n", sum);

    return 0;
}