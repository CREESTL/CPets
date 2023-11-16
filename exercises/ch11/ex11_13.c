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

#define COLS 3
#define LINES 4
#define START_LINE 0

/* Move to the next num in upper line if the end of lower line reached */
void check_above(int pos_in_lines[LINES])
{
    for (int l = LINES - 1; l > 0; l--)
    {
        if (pos_in_lines[l] > COLS - 1)
        {
            pos_in_lines[l - 1]++;
        }
    }
}

/* 
    If the end of any line is reached, reset position in that line
    and all lines after that
*/
void check_all_and_reset(int pos_in_lines[LINES])
{
    int start = 0;
    int change = 0;
    for (int line = 0; line < LINES; line++)
    {
        if (pos_in_lines[line] > COLS - 1 && line > 0)
        {
            /* Remember the line and allow to change */
            start = line;
            change = 1;
        }
        if (change == 1 && line >= start)
        {
            /* Reset lines below */
            pos_in_lines[line] = 0;
        }
    }
}

void test()
{
    char matrix[LINES][COLS] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
        {9, 10, 11},
    };
    
    int pos_in_lines[LINES] = {0};

    int count = 0;
    
    while (1)
    {
        
        check_above(pos_in_lines);
        check_all_and_reset(pos_in_lines);
        
        /* Stop if the end of first line reached */
        if (pos_in_lines[0] > COLS - 1)
            break;

        for (int line = 0; line < LINES; line++)
        {
            printf("%d", matrix[line][pos_in_lines[line]]);
            if (line == LINES - 1)
            {
                /* Each run num from last line changes */
                pos_in_lines[line]++;
            }
        }
        puts("");
        count++;
    }

    printf("Total number: %d\n", count);
}

int main(void)
{

    // char num[NUM_LENGTH];

    // get_user_num(num);
    // find_words(0, num, digits, letters);
    test();

    return 0;
}