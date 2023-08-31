/*
   One company is afraid of telephone line being wiretapped. 
   All data is transmitted as 4-digit integers.
   Integers are encoded as follows:
   1. Each digit is replaced with '(digit + 7) mod 10'
   2. First and third digits switch places
   3. Second and fourth digits switch places
   
*/

#include <stdio.h>
#include <stdlib.h>

// Length of integer
#define L 4

// Max integer user can enter
#define MAX_INT 1e4


// Direction of operations
typedef enum {
    ENCODE,
    DECODE
} Direction;

// Encodes the initial data
int encode(int);

// Decodes the encoded data
int decode(int);

// Replaces digits with encoded versions of them
int * replace_digits(int *, Direction);

// Switches digits' places
int * switch_digits(int *);

// Splits a 4-digit integer into array of digits
int * to_digits(int);

// Forms a 4-digit integer from array of digits
int from_digits(int *);

int main() {
    
    int initial_data;
    int encoded_data;
    int decoded_data;
    
    puts("Enter a 4-digit number: ");
    scanf("%u", &initial_data);
    
    if (initial_data >= MAX_INT ) {
        puts("Integer too big");
        exit(EXIT_FAILURE);
    }

    printf("Initial data is: %u\n", initial_data) ;
    
    encoded_data = encode(initial_data);
    printf("Encoded data is: %u\n", encoded_data) ;
    
    decoded_data = decode(encoded_data);
    printf("Decoded data is: %u\n", decoded_data) ;

    return 0;
}

int encode(int initial_data) {

    int * digits = to_digits(initial_data);
    int * round1_data = replace_digits(digits, ENCODE);
    int * round2_data = switch_digits(round1_data);

    int encoded_data = from_digits(round2_data);
    
    return encoded_data;

}

int decode(int encoded_data) {

    int * digits = to_digits(encoded_data);
    int * round1_data = switch_digits(digits);
    int * round2_data = replace_digits(round1_data, DECODE);
    
    int decoded_data = from_digits(round2_data);
    
    return decoded_data;
    
}

int * replace_digits(int * digits, Direction dir) {
    
    for (int i = 0; i < L; i++) {
        switch (dir) {
            // Encode
            case 0:
                digits[i] = (digits[i] + 7) % 10;
                break;
            // Decode
            case 1:
                if (digits[i] >= 7) {
                    digits[i] = digits[i] - 7;
                } else {
                    digits[i] = digits[i] + 10 - 7;
                }
                break;
        }
    }
    
    return digits;
    
}

int * switch_digits(int * digits) {
    int temp1;
    int temp2;
    
    // Switch 1st and 3rd
    temp1 = digits[0];
    digits[0] = digits[2];
    digits[2] = temp1;
    
    // Switch 2nd and 4th
    temp2 = digits[1];
    digits[1] = digits[3];
    digits[3] = temp2;

    return digits;
}

int * to_digits(int num) {
    static int digits[L];
    int copy = num;
    for (int i = 0; i < L; i++) {
        digits[L - 1 - i] = copy % 10;
        copy /= 10;
    }
    
    return digits;
}

int from_digits(int * digits) {
    
    int data = 0;
    int powers[L] = {1000, 100, 10, 1};
    for (int i = 0; i < L; i++) {
        data += digits[i] * powers[i];
    }

    return data;
}
