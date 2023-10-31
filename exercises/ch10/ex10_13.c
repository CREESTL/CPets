/*

    - Pack 4 1-byte chars into 1 4-byte integer
    - Unpack 1 4-byte integer into 4 1-byte chars

*/

#include <stdio.h>

void to_bits(unsigned a)
{
    unsigned mask = (unsigned)1 << sizeof a * 8 - 1;
    for (int i = 0; i < sizeof a * 8; i++)
    {
        putchar(mask & a ? '1' : '0');
        a <<= 1;
    }
    puts("");
}

unsigned pack(const char a, const char b)
{
    puts("\n[PACKING]");

    unsigned res = a;
    res <<= 8;
    res |= b;

    return res;
}

void unpack(char *a, char *b, unsigned packed)
{
    puts("\n[UNPACKING]");
    // 00000000 00000000 11111111 00000000
    unsigned first_char_mask = 65280;
    // 00000000 00000000 00000000 11111111
    unsigned second_char_mask = 255;

    *a = (packed & first_char_mask) >> 8;
    *b = packed & second_char_mask;
}

int main(void)
{

    // Pack
    char a, b;
    puts("Input 2 characters with no space:");
    scanf("%c%c", &a, &b);
    printf("Initial characters are: '%c' '%c'\n", a, b);
    unsigned res = pack(a, b);
    puts("Packing result:");
    to_bits(res);

    // Unpack
    char c, d;
    unpack(&c, &d, res);
    puts("Unpacking result:");
    printf("'%c' '%c'\n", c, d);

    return 0;
}