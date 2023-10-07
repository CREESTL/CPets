/*

    Print the sum of $ on the receipt. Max number of digits is 8.
    The '*' should be placed on all blank spaces if number of digits
    is less than 8

    Example:

    ***99.87     | Sum
    --------
    12345678     | Digit positions

*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Number of digits in receipt
#define R_SIZE 8

void get_receipt(char *, int);
void pretty_print_receipt(char *, int);

int main(void)
{

    // +1 for '\0'
    char receipt[R_SIZE + 1];
    get_receipt(receipt, R_SIZE + 1);
    pretty_print_receipt(receipt, R_SIZE);

    return 0;
}

void get_receipt(char *receipt, int size)
{
    puts("Input a receipt sum");
    if (fgets(receipt, size, stdin) == NULL)
    {
        puts("Failed to read input!");
        exit(EXIT_FAILURE);
    }
    // Delete any control symbols at the end
    if (iscntrl(receipt[strlen(receipt) - 1]))
    {
        memset(&receipt[strlen(receipt) - 1], '\0', 1);
    }
}

void pretty_print_receipt(char *receipt, int size)
{
    unsigned short length = strlen(receipt);
    printf("Receipt is: '%s'\n", receipt);
    printf("Protected receipt is: '");
    for (unsigned short i = 0; i < (R_SIZE - length); i++)
    {
        printf("%c", '*');
    }
    printf("%s'\n", receipt);
}