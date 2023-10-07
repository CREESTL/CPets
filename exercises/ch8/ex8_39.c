/*

    - Translate from English to Morse code
    - Translate from Morse code to English
    - Use 1 space between Morse code symbols
    - Use 3 spaces between Morse code words

*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Max amount of characters in code (including spaces)
#define CODE_LENGTH 5000

void get_morse_code(char *, int);
void morse_to_english(char *, int);
void english_to_morse(char *, int);

int main(void)
{
    char code[CODE_LENGTH];
    get_morse_code(code, CODE_LENGTH);
    morse_to_english(code, CODE_LENGTH);

    return 0;
}

void get_morse_code(char *code, int size)
{
    puts("Input Morse code.\
        \nUse 1 space between dots and dashes.\
        \nUse 3 spaces between words\n");
    if (fgets(code, size, stdin) == NULL)
    {
        puts("Failed to read input!");
        exit(EXIT_FAILURE);
    }
    // Delete any control symbols at the end
    if (iscntrl(code[strlen(code) - 1]))
    {
        memset(&code[strlen(code) - 1], '\0', 1);
    }
    printf("Morse code is: %s\n", code);
}

void morse_to_english(char *code, int size)
{
    // Split code into tokens separated with 3 spaces
    char *token_ptr = strtok(code, " ");
    while (token_ptr != NULL)
    {
        // Only one character between spaces is allowed
        if (strlen(token_ptr) != 1)
        {
            puts("Invalid amount of characters between spaces!");
            exit(EXIT_FAILURE);
        }

        // Pointer to the character following the current token
        char *prev_ptr = token_ptr + 1;
        token_ptr = strtok(NULL, " ");
        if (token_ptr != NULL)
        {
            // If difference in pointers is 3 bytes, that means
            // there was 3 spaces between them
            // These tokens are different words
            if (token_ptr - prev_ptr == 3)
            {
                printf("Word is: %s\n", token_ptr);
            }
            else if (token_ptr - prev_ptr != 1)
            {
                // If difference in pointers is neither 1 nor 3 bytes, that means
                // there was an error in number of spaces. Throw.
                puts("Invlid amount of spaces!");
                exit(EXIT_FAILURE);
            }
        }
    }
}

void english_to_morse(char *code, int size)
{
}