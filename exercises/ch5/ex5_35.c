/*

   This program guesses the number 1-1000

*/

#include <stdio.h>
#include <stdlib.h>

#define MIN 1
#define MAX 1000

void bin_search(unsigned int, unsigned int);

int main(void)
{

    unsigned int input = 0;
    puts("Input a number from 1 to 1000:\n");
    unsigned short scanned = scanf("%u", &input);
    switch (scanned)
    {
    case 0:
        puts("Invalid input!");
        exit(EXIT_FAILURE);
    case 1:
        if (input < MIN || input > MAX)
        {
            puts("Invalid input!");
            exit(EXIT_FAILURE);
        }
    }

    bin_search(MIN, MAX);
    return 0;
}

void bin_search(unsigned int min, unsigned int max)
{
    unsigned int guess = (max + min) / 2;
    printf("Guess is: %u\n", guess);

    unsigned int choice = 0;
    puts("Is this your number?\n1-No, mine is greater\n2-No, mine is less\n3-Yes\n");
    unsigned short scanned = scanf("%u", &choice);
    switch (scanned)
    {
    case 0:
        puts("Invalid choice!");
        exit(EXIT_FAILURE);
    case 1:
        if (choice < 1 || choice > 3)
        {
            puts("Invalid choice!");
            exit(EXIT_FAILURE);
        }
    }

    switch (choice)
    {
    case 3:
        puts("Great!");
        exit(EXIT_SUCCESS);
    case 1:
        bin_search((max + min) / 2, max);
        break;
    case 2:
        bin_search(min, (max + min) / 2);
    }
}