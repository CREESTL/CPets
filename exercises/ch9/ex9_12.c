/*

   Input a string and output it to the field double the length of the string

*/

#include <stdio.h>

#define L 5000

int main(void)
{
    char string[L];

    puts("Input a string:");
    // Explicitly use 'scanf' instead of 'fgets' here
    // Do not stop reading on spaces
    scanf("%[^\n]", string);

    int length = 0;

    for (unsigned int i = 0; i < L; i++)
    {
        char z = string[i];
        if (z != '\0')
        {
            length += 1;
        }
        else
        {
            break;
        }
    }

    printf("String length: %d\n", length);
    printf("%*s\n", 2 * length, string);

    return 0;
}