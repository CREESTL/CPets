/*
   
   Calculate factorial of an integer

*/

#include <stdio.h>

int fact(unsigned int number);

int main() {
    
    unsigned int number;
    puts("Input an integer: ");
    scanf("%d", &number);
    
    printf("The factorial of that integer is: %d\n", fact(number));
    
    return 0;
}


int fact(unsigned int number) {
    
    if (number == 1 || number == 0) {
        return number;
    }
    
    return number * fact(number - 1);
    
}