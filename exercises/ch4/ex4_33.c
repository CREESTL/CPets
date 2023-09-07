/*
 *
 * Convert integers 1-100 from arabic to roman numerals
 *
 */

#include <stdio.h>
#include <error.h>
#include <stdlib.h>

#define MAX 100

/* Converts arabic into roman */
void ar_to_rom(const int); 
/* Converts one digit to roman */
void one_digit(const int);
/* Converts two digits to roman */
void two_digits(const int, unsigned short);

int main() {
    
    for (unsigned int i = 1; i <= MAX; i++) {
        ar_to_rom(i);
    }
    
    return 0;
}


void ar_to_rom(const int num) {
    
    if (num > 100) {
        puts("Invalid number"); 
        exit(EXIT_FAILURE);
    }

    printf("Arabic number: %d\n", num);

    printf("Roman number: ");
    if (num < 10) {
        one_digit(num);
    } else if (num < 100) {
        two_digits(num, num / 10);
    } else {
        printf("C\n");
    }
    puts("\n");
    
}

void one_digit(const int num) {
    if (num < 5) {
        if (num == 4) {
            printf("IV");
        } else {
            for (unsigned int i = 0; i < num; i++) {
                printf("I");
            }
        }
    } else if (num == 5) {
        printf("V");
    } else if (num < 10) {
        if (num == 9) {
            printf("IX");
        } else {
            printf("V");
            for (unsigned int i = 0; i < num - 5; i++) {
                printf("I");
            }
        }
    }
}

void two_digits(const int num, unsigned short tens) {
    if (num == 10) {
        printf("X");
    } else if (num < 50) {
        if (num < 40) {
            for (unsigned int i = 0; i < tens; i++) {
                printf("X");
            }
        } else {
            printf("XL");
        }
        one_digit(num % 10);
    } else if (num == 50) {
        printf("L");
    } else if (num < 100) {
        if (num < 90) {
            printf("L");
            for (unsigned int i = 0; i < (num - 50) / 10; i++) {
                printf("X");
            }
            one_digit(num % 10);
        } else if (num == 90) {
            printf("XC");
        } else {
            printf("XC");
            one_digit(num % 10);
        }
    }
}