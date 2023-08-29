#include <stdio.h>

int main(void) {
    int a;
    int b;
    int sum;

    printf("Input first numder: ");
    // Potantial bug! User can input string
    scanf("%d", &a);

    printf("Input second numder: ");
    scanf("%d", &b);
    
    sum = a + b;

    printf("The sum is: %d\n", sum);

    return 0;

}