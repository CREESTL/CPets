/*
    On old cell phones with buttons each digit 2-9 represents
    3 letters:

    2: A B C
    3: D E F
    4: G H I
    5: J K L
    6: M N O
    7: P R S
    8: T U V
    9: X Y Z

    So some people try to remember phone numbers as words.
    For example: 825-3688 means "TAKEOUT". A good number for a restaurant.

    Find all possible works for a given 7-digit number and write them into a file

    There are 2187 (3^7) possible words for each 7-digit number
*/

#include <stdio.h>
#include <stdlib.h>

#define NUM_LENGTH 8
#define LETTERS_PER_DIGIT 3

/* Map from digits to letters */
char digits[NUM_LENGTH] = {'2', '3', '4', '5', '6', '7', '8', '9'};
char *letters[NUM_LENGTH] = {"ABC", "DEF", "GHI", "JKL", "MNO", "PRS", "TUV", "XYZ"};

void get_user_num(char *num)
{
    puts("Input a 7-digit number: ");
    fgets(num, NUM_LENGTH + 1, stdin);
}

void find_words(int pos, char *num, char *digits, char *letters[])
{
    // TODO should be 2187 at the end
    static int count = 0;
    static int last_letter = 0;
    // printf("\n\nPOS IS: %d\n", pos);
    // printf("AT POS: %c\n", num[pos]);
    // printf("COUNT IS: %d\n", count);

    /* Find the digit in the map */
    for (int i = 0; i < NUM_LENGTH - 1; i++)
    {
        if (digits[i] == num[pos])
        {
            /* Print letters of the digit */
            for (int j = 0; j < LETTERS_PER_DIGIT - 1; j++)
            {
                if (pos < NUM_LENGTH - 2)
                {
                    /* Print all letters except the last. One by one. */
                    printf("%c", letters[i][j]);
                    count++;
                    find_words(pos + 1, num, digits, letters);
                }
                else
                {
                    /* Print all 3 possible last letters without changing previous letters */
                    printf("%c", letters[i][last_letter]);
                    puts("");
                    last_letter++;
                    if (last_letter > LETTERS_PER_DIGIT - 1)
                    {
                        last_letter = 0;
                    }
                    count++;
                    find_words(0, num, digits, letters);
                }
            }

        }
    }
}

int main(void)
{

    char num[NUM_LENGTH];

    get_user_num(num);
    find_words(0, num, digits, letters);

    return 0;
}