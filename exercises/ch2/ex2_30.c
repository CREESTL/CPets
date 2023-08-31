/*
   Split 5-digit integer into digits
*/

#define LENGTH 5

#include <stdio.h>

int main() {
    
    unsigned int number;
    unsigned short digits[LENGTH];

    puts("Enter a number: ");
    scanf("%d", &number);
    
    for (unsigned int i = 0; i < LENGTH; i++) {
        digits[LENGTH - 1 - i] = number % 10;
        number /= 10;
    }
    
    for (unsigned int j = 0; j < LENGTH; j++) {
        printf("%d   ", digits[j]);
    }
    
    puts("");

    return 0;
}