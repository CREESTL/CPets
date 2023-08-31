/*

   Determine if the number is a palindrome

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_palindrome(unsigned int num);

int main() {

    unsigned int num;

    puts("Enter a number: ");
    scanf("%d", &num);

    if (is_palindrome(num)) {
        puts("The number IS a palindrome!");
    } else {
        puts("The number IS NOT a palindrome!");
    }
    
    return 0;
}

bool is_palindrome(unsigned int num) {

    unsigned short counter = 0;
    unsigned int num_copy = num;

    // Count digits
    while (num != 0) {
        counter++;
        num /= 10;
    }
    
    if (counter % 2 == 0) {
        puts("Incorrent input!");
        exit(EXIT_FAILURE);
    }
     
    // Split into digits
    unsigned short digits[counter];
    for (int i = 0; i < counter; i++) {
        digits[i] = num_copy % 10;
        num_copy /= 10;
    }
    
    bool is = true;

    // Compare digits
    for (int j = 0; j < counter / 2; j++) {
        if (digits[j] != digits[counter - 1 - j]) 
            is = false;
    } 

   return is;
}