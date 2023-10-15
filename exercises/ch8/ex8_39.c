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
// Write Morse code word into array
void read_morse_word(char *, int, const char *, const char *);
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
    // Pointer to one token
    char *token_ptr = strtok(code, " ");
    // Pointer to the start of the previous word (not token!)
    // Initially it's the same as current token
    char *prev_word_ptr = token_ptr;
    while (token_ptr != NULL)
    {
        // Check that token is valid
        if (!check_token(token_ptr))
        {
            puts("Invalid token");
            exit(EXIT_FAILURE);
        }

        // Pointer to the character following the current token
        char *next_char_ptr = token_ptr + 1;

        // Find next token
        token_ptr = strtok(NULL, " ");

        if (token_ptr != NULL)
        {
            // If difference in pointers is 3 bytes, that means
            // there was 3 spaces between them
            // These tokens are different words
            if (token_ptr - next_char_ptr == 3)
            {
                // Copy previous word into array
                // It should not contain any spaces (2 + 1)
                // It should contain '\0' symbol (+ 1)
                int word_size = (next_char_ptr - prev_word_ptr) / 2 + 1 + 1;
                char word[word_size];
                read_morse_word(word, word_size, prev_word_ptr, next_char_ptr);
                puts("Final word is:");
                printf("'%s'\n", word);

                // Place pointer to the start of current word
                prev_word_ptr = token_ptr;
            }
            else if (token_ptr - next_char_ptr != 1)
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
            int word_size = (next_char_ptr - prev_word_ptr) / 2 + 1 + 1;
            char word[word_size];
            read_morse_word(word, word_size, prev_word_ptr, next_char_ptr);
            puts("Final word is:");
            printf("'%s'\n", word);
        }
    }
}


void english_to_morse(char *code, int size)
{
}

void read_morse_word(char *word, int word_size, const char *prev_word_ptr, const char *next_char_ptr)
{
    unsigned int count = 0;
    for (char *letter_ptr = prev_word_ptr; letter_ptr < next_char_ptr; letter_ptr++)
    {
        if (*letter_ptr == '.' || *letter_ptr == '-')
        {
            word[count] = *letter_ptr;
            count++;
        }
    }
    word[count] = '\0';
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