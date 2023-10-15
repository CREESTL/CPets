/*

    - Translate from English to Morse code
    - Translate from Morse code to English
    - Use 1 space between Morse code symbols
    - Use 3 spaces between Morse code words

*/

/*

    TODO iterate over all keys in hashmap to free them and 
        then free the map itself

*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "./hashmap_lib/map.h"

// Max amount of characters in code (including spaces)
#define CODE_LENGTH 5000


// Fill Morse code dictionary with translations of each word (letter)
void fill_dict(hashmap *, hashmap *);
// Get user input of Morse code
void get_morse_code(char *, int);
// Translate Morse code words into English letters
void morse_to_english(char *, int, hashmap *);
// Write Morse code word into array
void read_morse_word(char *, int, char *, const char *);
// Translate Morse code word into English letter
void translate_morse_to_eng(char *, hashmap *);
// Translate English words into Morse code
void english_to_morse(char *, int);
// Check that user input a correct character
bool check_token(char *);

int main(void)
{
    // Create dictionary to translate from Morse code word into English letters
    hashmap *eng_to_morse_dict = hashmap_create();
    hashmap *morse_to_eng_dict = hashmap_create();
    fill_dict(eng_to_morse_dict, morse_to_eng_dict);

    char code[CODE_LENGTH];
    get_morse_code(code, CODE_LENGTH);
    morse_to_english(code, CODE_LENGTH, morse_to_eng_dict);

    return 0;
}

void fill_dict(hashmap *eng_to_morse_dict, hashmap *morse_to_eng_dict)
{
    
    // English to Morse
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("A"), (uintptr_t)".-");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("B"), (uintptr_t)"-...");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("C"), (uintptr_t)"-.-.");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("D"), (uintptr_t)"-..");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("E"), (uintptr_t)".");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("F"), (uintptr_t)"..-.");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("G"), (uintptr_t)"--.");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("H"), (uintptr_t)"....");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("I"), (uintptr_t)"..");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("K"), (uintptr_t)".---");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("L"), (uintptr_t)".-..");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("M"), (uintptr_t)"--");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("N"), (uintptr_t)"-.");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("O"), (uintptr_t)"---");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("P"), (uintptr_t)".--.");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("Q"), (uintptr_t)"--.-");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("R"), (uintptr_t)".-.");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("S"), (uintptr_t)"...");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("T"), (uintptr_t)"-");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("U"), (uintptr_t)"..-");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("V"), (uintptr_t)"...-");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("W"), (uintptr_t)".--");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("X"), (uintptr_t)"-..-");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("Y"), (uintptr_t)"-.--");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("Z"), (uintptr_t)"--..");

    hashmap_set(eng_to_morse_dict, hashmap_str_lit("1"), (uintptr_t)".----");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("2"), (uintptr_t)"..---");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("3"), (uintptr_t)"...--");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("4"), (uintptr_t)"....-");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("5"), (uintptr_t)".....");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("6"), (uintptr_t)"-....");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("7"), (uintptr_t)"--...");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("8"), (uintptr_t)"---..");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("9"), (uintptr_t)"----.");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("0"), (uintptr_t)"-----");

    // Morse to English
    hashmap_set(morse_to_eng_dict, hashmap_str_lit(".-"), (uintptr_t)"A");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("-..."), (uintptr_t)"B");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("-.-."), (uintptr_t)"C");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("-.."), (uintptr_t)"D");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("."), (uintptr_t)"E");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("..-."), (uintptr_t)"F");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("--."), (uintptr_t)"G");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("...."), (uintptr_t)"H");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit(".."), (uintptr_t)"I");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit(".---"), (uintptr_t)"K");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit(".-.."), (uintptr_t)"L");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("--"), (uintptr_t)"M");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("-."), (uintptr_t)"N");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("---"), (uintptr_t)"O");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit(".--."), (uintptr_t)"P");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("--.-"), (uintptr_t)"Q");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit(".-."), (uintptr_t)"R");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("..."), (uintptr_t)"S");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("-"), (uintptr_t)"T");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("..-"), (uintptr_t)"U");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("...-"), (uintptr_t)"V");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit(".--"), (uintptr_t)"W");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("-..-"), (uintptr_t)"X");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("-.--"), (uintptr_t)"Y");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("--.."), (uintptr_t)"Z");

    hashmap_set(morse_to_eng_dict, hashmap_str_lit(".----"), (uintptr_t)"1");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("..---"), (uintptr_t)"2");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("...--"), (uintptr_t)"3");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("....-"), (uintptr_t)"4");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("....."), (uintptr_t)"5");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("-...."), (uintptr_t)"6");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("--..."), (uintptr_t)"7");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("---.."), (uintptr_t)"8");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("----."), (uintptr_t)"9");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("-----"), (uintptr_t)"0");
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


void morse_to_english(char *code, int size, hashmap *morse_to_eng_dict)
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
                translate_morse_to_eng(word, morse_to_eng_dict);

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
            translate_morse_to_eng(word, morse_to_eng_dict);
        }
    }
}


void english_to_morse(char *code, int size)
{
}

void read_morse_word(char *word, int word_size, char *prev_word_ptr, const char *next_char_ptr)
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

void translate_morse_to_eng(char *word, hashmap *morse_to_eng_dict)
{
    uintptr_t result;
    if (hashmap_get(morse_to_eng_dict, word, strlen(word), &result))
    {
        printf("Word %s translates to letter '%s'\n", word, (char *)result);
    }
    else 
    {
        printf("Unable to find word '%s' in the dictionary", word);
    }
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