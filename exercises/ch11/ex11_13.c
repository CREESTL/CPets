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

/* Length of string representation of number. Contains '\n' character. */
#define NUM_LENGTH 8
/* Length of string representing a digit */
#define LETTERS_PER_DIGIT 3

/* Map from digits to letters */
char digits[NUM_LENGTH] = {'2', '3', '4', '5', '6', '7', '8', '9'};
char *letters[NUM_LENGTH] = {"ABC", "DEF", "GHI", "JKL", "MNO", "PRS", "TUV", "XYZ"};

/* Positions of printed letters in matrix */
int pos_in_lines[NUM_LENGTH - 1] = {0};

void get_user_num(char *num)
{
    puts("Input a 7-digit number: ");
    fgets(num, NUM_LENGTH + 1, stdin);
}

void form_matrix(const char *const num, char const digits[NUM_LENGTH], char *const letters[NUM_LENGTH],
                 char matrix[NUM_LENGTH][LETTERS_PER_DIGIT])
{
    int count = 0;
    for (int i = 0; i < NUM_LENGTH; i++)
    {
        for (int j = 0; j < NUM_LENGTH; j++)
        {
            if (num[i] == digits[j])
            {
                for (int k = 0; k < LETTERS_PER_DIGIT; k++)
                {
                    matrix[count][k] = letters[j][k];
                }
                count++;
            }
        }
    }

    puts("MATRIX IS: ");
    for (int i = 0; i < NUM_LENGTH; i++)
    {
        for (int j = 0; j < LETTERS_PER_DIGIT; j++)
        {
            printf("%c ", matrix[i][j]);
        }
        puts("");
    }
    puts("============");
}

/* Move to the next num in upper line if the end of lower line reached */
void check_above(int pos_in_lines[NUM_LENGTH - 1])
{
    for (int l = NUM_LENGTH - 2; l > 0; l--)
    {
        if (pos_in_lines[l] > LETTERS_PER_DIGIT - 1)
        {
            pos_in_lines[l - 1]++;
        }
    }
}

/*
    If the end of any line is reached, reset position in that line
    and all lines after that
*/
void check_all_and_reset(int pos_in_lines[NUM_LENGTH - 1])
{
    int start = 0;
    int change = 0;
    for (int line = 0; line < NUM_LENGTH - 1; line++)
    {
        if (pos_in_lines[line] > LETTERS_PER_DIGIT - 1 && line > 0)
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

void find_words(char matrix[NUM_LENGTH][LETTERS_PER_DIGIT])
{

    int count = 0;
    while (1)
    {
        /**
         * 
         * DEF
         * DEF
         * DEF
         * GHI
         * GHI
         * GHI
         * ABC 
         * 
        */

        check_above(pos_in_lines);
        check_all_and_reset(pos_in_lines);

        /* Stop if the end of first line reached */
        if (pos_in_lines[0] > LETTERS_PER_DIGIT - 1)
            break;

        for (int line = 0; line < NUM_LENGTH - 1; line++)
        {
            printf("%c ", matrix[line][pos_in_lines[line]]);
            if (line == NUM_LENGTH - 2)
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

    char num[NUM_LENGTH];
    char matrix[NUM_LENGTH][LETTERS_PER_DIGIT];

    get_user_num(num);
    form_matrix(num, digits, letters, matrix);
    find_words(matrix);

    return 0;
}