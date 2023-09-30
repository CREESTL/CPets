/*

   Recursive palindromes

*/

#include <stdio.h>
#include <string.h>

int is_palindrome(char *, int, int);

int main(void)
{
    
    char* strings[] = {
        "",
        "A",
        "able was i ere i saw elba",
        "Clearly not a palindrome"
    };
    
    for (unsigned int i = 0; i < sizeof(strings) / sizeof(size_t); i++)
    {
        switch (is_palindrome(strings[i], 0, strlen(strings[i]) - 1))
        {
            case 1:
                printf("String \"%s\" is a palindrome\n", strings[i]);
                break;
            case 0:
                printf("String \"%s\" IS NOT a palindrome\n", strings[i]);
                break;
        }
    }

    return 0;
}

int is_palindrome(char* phrase, int start, int end)
{
    if (start - end == 1 || start == end)
        return 1;
    if (phrase[start] != phrase[end]){
        return 0;
    }
    is_palindrome(phrase, start + 1, end - 1);

}