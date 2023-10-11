/*

    - Translate from English to Morse code
    - Translate from Morse code to English
    - Use 1 space between Morse code symbols
    - Use 3 spaces between Morse code words

*/

/*


   How to encode spaces between words?

*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Max amount of characters in code (including spaces)
#define CODE_LENGTH 5000

// Get user input of Morse code
void get_morse_code(char *, int);
// Translate Morse code words into English letters
void morse_to_english(char *, int);
// Translate English words into Morse code
void english_to_morse(char *, int);
// Check that user input a correct character
bool check_token(char *);

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
    // Split code into words separated with 3 spaces
    char *token_ptr = strtok(code, " ");
    // Pointer to the start of the previous word (not token!)
    // Initially it's the same as current token
    char *prev_word_ptr = token_ptr;
    while (token_ptr != NULL)
    {
        // Only one character between spaces is allowed
        if (!check_token(token_ptr))
        {
            puts("Invalid token");
            exit(EXIT_FAILURE);
        }

        // Pointer to the character following the current token
        char *next_token_ptr = token_ptr + 1;

        token_ptr = strtok(NULL, " ");

        if (token_ptr != NULL)
        {
            // Check that symbol is either a dot or a dash
            // If difference in pointers is 3 bytes, that means
            // there was 3 spaces between them
            // These tokens are different words
            if (token_ptr - next_token_ptr == 3)
            {
                // It should not contain any spaces ( / 2 + 1)
                // It should contain '\0' symbol (+ 1)
                char word[(next_token_ptr - prev_word_ptr) / 2 + 1 + 1];
                unsigned int count = 0;
                for (char *letter_ptr = prev_word_ptr; letter_ptr < next_token_ptr; letter_ptr++)
                {
                    if (*letter_ptr == '.' || *letter_ptr == '-')
                    {
                        puts("add a new letter");
                        word[count] = *letter_ptr;
                        count++;
                    }
                }
                word[count] = '\0';
                puts("Final word is:");
                printf("'%s'\n", word);

                // Place pointer wo the start of current word
                prev_word_ptr = token_ptr;
            }
            else if (token_ptr - next_token_ptr != 1)
            {
                // If difference in pointers is neither 1 nor 3 bytes, that means
                // there was an error in number of spaces. Throw.
                puts("Invlid amount of spaces!");
                exit(EXIT_FAILURE);
            }
        }
        // End of input was reached. Print last word.
        else 
        {
            puts("Word is:");
            for (char *letter_ptr = prev_word_ptr; letter_ptr < next_token_ptr; letter_ptr++)
            {
                printf("%s", letter_ptr);
            }
            puts("");
        }
    }
}


void english_to_morse(char *code, int size)
{
}


bool check_token(char *token)
{
    // Only one character per token is allowed
    if (strlen(token) != 1)
        return false;
    else
    {
        // This character is either a dash or a dot
       if (token[0] != '-' && token[0] != '.') 
           return false;
    }
    return true;
    
}