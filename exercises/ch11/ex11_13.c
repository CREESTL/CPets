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

void check_above(int start, int pos_in_lines[LINES])
{
    for (int l = start; l > 0; l--)
    {
        if (pos_in_lines[l] > COLS - 1)
        {
            pos_in_lines[l - 1]++;
        }
    }
}

void test()
{
    int matrix[LINES][COLS] = {
        {0, 1, 2}, 
        {3, 4, 5}, 
        {6, 7, 8},
        {9, 10, 11}
    };
    

    
    int pos_in_lines[LINES] = {0};

    puts("START");
    int count = 0;
    
    int proc_line = LINES - 1;
    while (pos_in_lines[START_LINE] < LINES)
    {

        /* Check all lines and reset */
        for (int line = 0; line < LINES; line++)
        {
            if (pos_in_lines[line] > COLS - 1 && line > 0)
            {
                /* If that was the proc line - move it up */
                if (line == proc_line)
                {
                    --proc_line;
                }
                /* Reset positions on current line and all lines after current */
                for (int i = line; i < LINES; i++)
                {
                    pos_in_lines[i] = 0;
                }
            }
        }

        for (int line = 0; line < LINES; line++)
        {
            /* Before proc line */
            if (line < proc_line)
            {
                printf("%d", matrix[line][pos_in_lines[line]]);
            }
            /* After proc line */
            if (line > proc_line)
            {
                printf("%d", matrix[line][pos_in_lines[line]]);
                if (line == LINES - 1)
                {
                    /* The only line which increases every time is the last one */
                    pos_in_lines[line]++;
                    if (pos_in_lines[line] > COLS - 1)
                    {
                        check_above(line, pos_in_lines);
                    }
                }
            }
            /* On proc line */
            if (line == proc_line)
            {
                printf("%d", matrix[line][pos_in_lines[line]]);
                if (line == LINES - 1)
                {
                    /* If proc line is the last one - print next number in proc line next time */
                    pos_in_lines[line]++;
                    check_above(line, pos_in_lines);
                }
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