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
}

#define SIZE 3
#define START_LINE 0

// TODO make it not square
void test()
{
    int matrix[3][3] = {
        {0, 1, 2}, 
        {3, 4, 5}, 
        {6, 7, 8}
    };

    puts("START");
    int count = 0;

    /* 
        Iterate over the first line of matrix. Look for all possible 
        combinations from other lines for each number of the first line.
    */
    for (int i = START_LINE; i < SIZE; i++)
    {
        int check = 1;
        int pos_in_line = 0;
        int pos_in_last_line = 0;
        while (check == 1)
        {
            printf("%d", matrix[0][i]);
            /* Iterate over other lines */
            for (int j = START_LINE + 1; j < SIZE; j++)
            {
                /* Last line */
                if (j == SIZE - 1)
                {
                    printf("%d", matrix[j][pos_in_last_line]);
                    count++;
                    pos_in_last_line++;
                    /* Reached the end of last line */
                    if (pos_in_last_line > SIZE - 1)
                    {
                        /* The next time the last line will be printed from the beginning */
                        pos_in_last_line = 0;
                        /* Switch to next number in the not last line */
                        pos_in_line++;
                        /* Reached the end of not last line*/
                        if (pos_in_line > SIZE - 1)
                        {
                            /* The next time the not last line will be printed from the beginning */
                            pos_in_line = 0;
                            /* All combinations for the number from the first line were found */
                            check = 0;
                        }
                    }
                }
                /* Not last line */
                else
                {
                    printf("%d", matrix[j][pos_in_line]);
                }
            }
            puts("");
        }
        puts("======");
    }

    printf("Total number: %d\n", count);
}

int main(void)
{

    char num[NUM_LENGTH];

    // get_user_num(num);
    // find_words(0, num, digits, letters);
    test();

    return 0;
}