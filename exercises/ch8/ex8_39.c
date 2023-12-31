/*

    - Translate from English to Morse code
    - Translate from Morse code to English

*/

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./hashmap_lib/map.h"

// Max amount of characters in code (including spaces)
#define CODE_LENGTH 5000
// Max amount of characters in English  text
#define TEXT_LENGTH 5000
// Max amount of characters for user choice
// 1 char for option, 1 char for '\0' symbol
#define CHOICE_LENGTH 2

// Get user input of Morse code
void get_morse_code(char *, int);
// Translate Morse code words into English letters
void morse_to_english(char *, int, hashmap *);
// Check that user input a correct character
bool check_token(char *);
// Read Morse code word into array
void read_morse_word(char *, int, char *, const char *);
// Translate Morse code word into English letter
void morse_word_to_eng_letter(char *, hashmap *);

// Get user input of English words
void get_english_text(char *, int);
// Translate English text into Morse code
void english_to_morse(char *, int, hashmap *);
// Read English word into array
void read_english_word(char *, int, char *, const char *);
// Translate English word into Morse code
void eng_word_to_morse_words(char *, hashmap *);

// Fill Morse code dictionary with translations of each word (letter)
void fill_dicts(hashmap *, hashmap *);
// Free memory allocated for both dicts
void free_dicts(hashmap *, hashmap *);

// Remove remaining characters from keyboard input buffer until next newline
void remove_remaining_chars(FILE *f);
// Find and remove newline from string
int truncate_newline(char *str);
// Remove newline from string or excess characters from input buffer
void clean_string(char *str, FILE *f);

// Show supported English symbols
void show_dict(hashmap *);

int main(void)
{
    // Create dictionary to translate from Morse code word into English letters
    // and vice versa
    hashmap *eng_to_morse_dict = hashmap_create();
    hashmap *morse_to_eng_dict = hashmap_create();
    fill_dicts(eng_to_morse_dict, morse_to_eng_dict);

    // User can choose one option:
    // An option number with a '\0\' and '\n' symbol
    char choice[CHOICE_LENGTH];
    printf("%s\n", "Choose one option \
            \n1)Translate Morse into English\
            \n2)Translate English into Morse\
    ");

    if (fgets(choice, CHOICE_LENGTH, stdin) == NULL)
    {
        puts("Failed to read input!");
        exit(EXIT_FAILURE);
    }
    clean_string(choice, stdin);

    if (choice[0] != '1' && choice[0] != '2')
    {
        puts("Invalid option");
        exit(EXIT_FAILURE);
    }

    switch (choice[0])
    {
    // Morse -> English
    case '1':
        char code[CODE_LENGTH];
        get_morse_code(code, CODE_LENGTH);
        morse_to_english(code, CODE_LENGTH, morse_to_eng_dict);
        break;

    // English -> Morse
    case '2':
        char text[TEXT_LENGTH];
        show_dict(eng_to_morse_dict);
        get_english_text(text, TEXT_LENGTH);
        english_to_morse(text, TEXT_LENGTH, eng_to_morse_dict);
        break;
    }

    // Clean up
    free_dicts(morse_to_eng_dict, eng_to_morse_dict);

    return 0;
}

/*
//////////////////////////
/////MORSE -> ENGLISH/////
//////////////////////////
*/

void get_morse_code(char *code, int size)
{
    puts("Input Morse code.\
        \nUse 1 space between dots and dashes.\
        \nUse 3 spaces between letters. \
        \nUse '\\' between words.\n");
    if (fgets(code, size, stdin) == NULL)
    {
        puts("Failed to read input!");
        exit(EXIT_FAILURE);
    }
    clean_string(code, stdin);
}

void morse_to_english(char *code, int size, hashmap *morse_to_eng_dict)
{
    // Pointer to one token
    char *token_ptr = strtok(code, " ");
    // Pointer to the start of the previous word (not token!)
    // Initially it's the same as current token
    char *prev_word_ptr = token_ptr;
    puts("Result in English:");
    printf("'");
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
                // It should contain '\0' symbol
                int word_size = (next_char_ptr - prev_word_ptr) / 2 + 1;
                char word[word_size];
                read_morse_word(word, word_size, prev_word_ptr, next_char_ptr);
                morse_word_to_eng_letter(word, morse_to_eng_dict);

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
            int word_size = (next_char_ptr - prev_word_ptr) / 2 + 1;
            char word[word_size];
            read_morse_word(word, word_size, prev_word_ptr, next_char_ptr);
            morse_word_to_eng_letter(word, morse_to_eng_dict);
        }
    }
    puts("'");
}

bool check_token(char *token)
{
    // Only one character per token is allowed
    if (strlen(token) != 1)
        return false;
    else
    {
        // This character is either a dash, a dot, or a backslash
        if (token[0] != '-' && token[0] != '.' && token[0] != '/')
            return false;
    }
    return true;
}

void read_morse_word(char *word, int word_size, char *prev_word_ptr, const char *next_char_ptr)
{
    unsigned int count = 0;
    for (char *letter_ptr = prev_word_ptr; letter_ptr < next_char_ptr; letter_ptr++)
    {
        if (*letter_ptr == '.' || *letter_ptr == '-' || *letter_ptr == '/')
        {
            word[count] = *letter_ptr;
            count++;
        }
    }
    word[count] = '\0';
}

void morse_word_to_eng_letter(char *word, hashmap *morse_to_eng_dict)
{
    uintptr_t result;
    if (hashmap_get(morse_to_eng_dict, word, strlen(word), &result))
    {
        printf("%s", (char *)result);
    }
    else
    {
        printf("Unable to find word '%s' in the dictionary", word);
    }
}

/*
//////////////////////////
/////ENGLISH -> MORSE/////
//////////////////////////
*/

void get_english_text(char *text, int size)
{
    puts("Input English text.\n");
    if (fgets(text, size, stdin) == NULL)
    {
        puts("Failed to read input!");
        exit(EXIT_FAILURE);
    }
    clean_string(text, stdin);
}

void english_to_morse(char *text, int size, hashmap *eng_to_morse_dict)
{
    // Pointer to one word
    char *word_ptr = strtok(text, " ");
    puts("Result in Morse:");
    while (word_ptr != NULL)
    {
        // Pointer to the start of the previous word (not token!)
        char *prev_word_ptr = word_ptr;

        // Pointer to the character following the word
        char *next_char_ptr = word_ptr + strlen(word_ptr);

        // Find next word
        word_ptr = strtok(NULL, " ");

        if (word_ptr != NULL)
        {
            // If difference in pointers is 1 byte, that means
            // there was 1 space between them. These are separate words
            if (word_ptr - next_char_ptr == 1)
            {

                // Copy previous word into array
                // It should contain '\0' symbol (+ 1)
                int word_size = (next_char_ptr - prev_word_ptr) + 1;
                char word[word_size];
                read_english_word(word, word_size, prev_word_ptr, next_char_ptr);
                eng_word_to_morse_words(word, eng_to_morse_dict);

                // Translate space as well
                eng_word_to_morse_words(" ", eng_to_morse_dict);
            }
            else if (word_ptr - next_char_ptr > 1)
            {
                // If difference in pointers is more than 1 bytes, that means
                // there were multiple spaces between words, which is incorrect
                puts("Invalid amount of spaces!");
                exit(EXIT_FAILURE);
            }
        }
        // End of input was reached. Print last word.
        else
        {
            int word_size = (next_char_ptr - prev_word_ptr) + 1;
            char word[word_size];
            read_english_word(word, word_size, prev_word_ptr, next_char_ptr);
            eng_word_to_morse_words(word, eng_to_morse_dict);
        }
    }
    puts(" ");
}

void read_english_word(char *word, int word_size, char *prev_word_ptr, const char *next_char_ptr)
{
    unsigned int count = 0;
    for (char *letter_ptr = prev_word_ptr; letter_ptr < next_char_ptr; letter_ptr++)
    {
        word[count] = *letter_ptr;
        count++;
    }
    word[count] = '\0';
}

void eng_word_to_morse_words(char *word, hashmap *eng_to_morse_dict)
{
    // Translate each letter of the word
    for (unsigned int i = 0; i < strlen(word); i++)
    {
        uintptr_t result;
        char letter = word[i];

        // Convert letter to uppercase in any case
        letter = toupper(letter);

        if (hashmap_get(eng_to_morse_dict, &letter, 1, &result))
        {
            for (unsigned int j = 0; j < strlen((char *)result); j++)
            {
                // Place 1 space between each token of result
                printf("%c ", ((char *)result)[j]);
            }
            // Place 2 spaces between letters (one is after last char)
            printf("  ");
        }
        else
        {
            printf("Unable to find letter '%c' in the dictionary", letter);
        }
    }
}

/*
//////////////////////////
////////DICTIONARY////////
//////////////////////////
*/

void fill_dicts(hashmap *eng_to_morse_dict, hashmap *morse_to_eng_dict)
{

    // [English to Morse]

    // Letters
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("A"), (uintptr_t) ".-");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("B"), (uintptr_t) "-...");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("C"), (uintptr_t) "-.-.");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("D"), (uintptr_t) "-..");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("E"), (uintptr_t) ".");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("F"), (uintptr_t) "..-.");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("G"), (uintptr_t) "--.");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("H"), (uintptr_t) "....");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("I"), (uintptr_t) "..");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("J"), (uintptr_t) ".---");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("K"), (uintptr_t) "-.-");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("L"), (uintptr_t) ".-..");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("M"), (uintptr_t) "--");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("N"), (uintptr_t) "-.");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("O"), (uintptr_t) "---");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("P"), (uintptr_t) ".--.");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("Q"), (uintptr_t) "--.-");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("R"), (uintptr_t) ".-.");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("S"), (uintptr_t) "...");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("T"), (uintptr_t) "-");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("U"), (uintptr_t) "..-");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("V"), (uintptr_t) "...-");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("W"), (uintptr_t) ".--");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("X"), (uintptr_t) "-..-");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("Y"), (uintptr_t) "-.--");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("Z"), (uintptr_t) "--..");

    // Digits
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("1"), (uintptr_t) ".----");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("2"), (uintptr_t) "..---");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("3"), (uintptr_t) "...--");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("4"), (uintptr_t) "....-");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("5"), (uintptr_t) ".....");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("6"), (uintptr_t) "-....");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("7"), (uintptr_t) "--...");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("8"), (uintptr_t) "---..");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("9"), (uintptr_t) "----.");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("0"), (uintptr_t) "-----");

    // Punctuation
    hashmap_set(eng_to_morse_dict, hashmap_str_lit(" "), (uintptr_t) "/");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("."), (uintptr_t) ".-.-.-");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("'"), (uintptr_t) ".----.");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("("), (uintptr_t) "-.--.");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit(")"), (uintptr_t) "-.--.-");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit(":"), (uintptr_t) "---...");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("+"), (uintptr_t) ".-.-.");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit(","), (uintptr_t) "--..--");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("!"), (uintptr_t) "-.-.--");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit(";"), (uintptr_t) "-.-.-.");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("-"), (uintptr_t) "-....-");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("?"), (uintptr_t) "..--..");
    hashmap_set(eng_to_morse_dict, hashmap_str_lit("="), (uintptr_t) "-...-");

    // [Morse to English]

    // Letters
    hashmap_set(morse_to_eng_dict, hashmap_str_lit(".-"), (uintptr_t) "A");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("-..."), (uintptr_t) "B");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("-.-."), (uintptr_t) "C");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("-.."), (uintptr_t) "D");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("."), (uintptr_t) "E");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("..-."), (uintptr_t) "F");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("--."), (uintptr_t) "G");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("...."), (uintptr_t) "H");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit(".."), (uintptr_t) "I");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit(".---"), (uintptr_t) "J");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("-.-"), (uintptr_t) "K");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit(".-.."), (uintptr_t) "L");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("--"), (uintptr_t) "M");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("-."), (uintptr_t) "N");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("---"), (uintptr_t) "O");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit(".--."), (uintptr_t) "P");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("--.-"), (uintptr_t) "Q");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit(".-."), (uintptr_t) "R");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("..."), (uintptr_t) "S");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("-"), (uintptr_t) "T");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("..-"), (uintptr_t) "U");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("...-"), (uintptr_t) "V");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit(".--"), (uintptr_t) "W");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("-..-"), (uintptr_t) "X");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("-.--"), (uintptr_t) "Y");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("--.."), (uintptr_t) "Z");

    // Digits
    hashmap_set(morse_to_eng_dict, hashmap_str_lit(".----"), (uintptr_t) "1");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("..---"), (uintptr_t) "2");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("...--"), (uintptr_t) "3");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("....-"), (uintptr_t) "4");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("....."), (uintptr_t) "5");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("-...."), (uintptr_t) "6");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("--..."), (uintptr_t) "7");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("---.."), (uintptr_t) "8");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("----."), (uintptr_t) "9");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("-----"), (uintptr_t) "0");

    // Punctuation
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("/"), (uintptr_t) " ");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit(".-.-.-"), (uintptr_t) ".");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit(".----."), (uintptr_t) "'");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("-.--."), (uintptr_t) "(");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("-.--.-"), (uintptr_t) ")");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("---..."), (uintptr_t) ":");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit(".-.-."), (uintptr_t) "+");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("--..--"), (uintptr_t) ",");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("-.-.--"), (uintptr_t) "!");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("-.-.-."), (uintptr_t) ";");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("-....-"), (uintptr_t) "-");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("..--.."), (uintptr_t) "?");
    hashmap_set(morse_to_eng_dict, hashmap_str_lit("-...-"), (uintptr_t) "=");
}

void free_dicts(hashmap *morse_to_eng_dict, hashmap *eng_to_morse_dict)
{
    free(morse_to_eng_dict);
    free(eng_to_morse_dict);
}

/*
//////////////////////////
////////GENERAL////////
//////////////////////////
*/

void remove_remaining_chars(FILE *f)
{
    int c;
    // Read characters from input and do nothing
    while ((c = fgetc(f)) != EOF && c != '\n')
    {
    }
}

int truncate_newline(char *str)
{
    int res = 0;
    if (str != NULL)
    {
        char *new_line_ptr = strchr(str, '\n');
        if (new_line_ptr != NULL)
        {
            res = 1;
            *new_line_ptr = '\0';
        }
    }
    return res;
}

void clean_string(char *str, FILE *f)
{
    if (!truncate_newline(str))
    {
        remove_remaining_chars(f);
    }
}

void print_symbol(void *key, size_t ksize, uintptr_t value, void *user)
{
    printf("%s", (char *)key);
}

void show_dict(hashmap *eng_to_morse_dict)
{
    puts("Supported English symbols are:");
    hashmap_iterate(eng_to_morse_dict, print_symbol, NULL);
    puts("");
}
