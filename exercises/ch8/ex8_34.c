/*

   1. Read user input and count number of times each letter occured in the text
   2. Read user input and count number of words containing 1 letters, 2 letters, etc.

*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Max size of input
#define TEXT_SIZE 5000
// Number of letter in English alphabet
#define AL_SIZE 26
// Max length of word in text
#define WORD_LENGTH 100

void count_chars(char[], const char[], int);
void count_words(char[], int);

int main(void)
{

    const char alphabet[AL_SIZE] = "abcdefghijklmnopqrstuvwxyz";

    // Get user input
    char text[TEXT_SIZE];
    printf("%s", "Input a text to count how many times each letter occurs in it:");
    fgets(text, TEXT_SIZE, stdin);

    count_chars(text, alphabet, TEXT_SIZE);

    printf("%s", "Input a text to count words containing 1 letters, 2 letters, etc.:");
    fgets(text, TEXT_SIZE, stdin);
    count_words(text, TEXT_SIZE);

    return 0;
}

void count_chars(char text[], const char alphabet[], int size)
{

    printf("%-15s%-10s\n", "Letter", "Times");
    // Iterate over the alphabet
    for (unsigned int i = 0; i < AL_SIZE - 1; i++)
    {
        char *copy_ptr = text;

        int count = 0;
        char letter = alphabet[i];
        while (strchr(copy_ptr, letter) != NULL)
        {
            count++;
            // Cut off all letters before and including the found one
            copy_ptr = strchr(copy_ptr, letter) + 1;
        }
        if (count != 0)
            printf("%-15c%-10d\n", letter, count);
    }
}

void count_words(char text[], int size)
{

    // The number on n-th position equals to the number of words containing n letters
    unsigned int words_table[WORD_LENGTH] = {0};

    // Split the text into tokens with spaces
    // Each token is a word
    char *token_ptr = NULL;

    token_ptr = strtok(text, " ");

    while (token_ptr != NULL)
    {
        int num_letters = strlen(token_ptr);
        // Delete any control symbols
        if (iscntrl(token_ptr[num_letters - 1]))
            num_letters--;
        if (num_letters < WORD_LENGTH)
        {
            words_table[num_letters]++;
        }
        else
        {
            puts("Invalid word length");
            exit(EXIT_FAILURE);
        }

        token_ptr = strtok(NULL, " ");
    }

    printf("%-20s%-20s\n", "Word length", "Number of words");
    for (unsigned int length = 0; length < WORD_LENGTH - 1; length++)
    {
        if (words_table[length] != 0)
            printf("%-20u%-20u\n", length, words_table[length]);
    }
}