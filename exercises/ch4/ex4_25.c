/*
   
   Output the same integer in octal, hexadecimal and binary formats

*/

#include <stdio.h>

int main() {
    
    const unsigned int num = 5;
    
    printf("Octal: %o\n", num);
    printf("Hexadecimal : %x\n", num);
    printf("Binary : %b\n", num);

    return 0;
}