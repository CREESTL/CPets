/*

   Inverse bits of user's input

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

unsigned inverse(unsigned num)
{
    unsigned ret_val = 0;
    // Used to find '1' bits in num
    unsigned scan_mask = (unsigned)1 << sizeof num * 8 - 1;
    for (int i = 0; i < sizeof num * 8; i++)
    {
        if (scan_mask & num)
        {
            // Used to put '1' bits in the inversed place in returned value
            unsigned replace_mask = (unsigned)1 << i;
            ret_val |= replace_mask;
        }
        scan_mask >>= 1;
    }

    return ret_val;
}

int main(void)
{
    unsigned num = 0;
    unsigned inversed = 0;
    puts("Input one number");
    scanf("%u", &num);

    puts("Original bits order:");
    to_bits(num);

    inversed = inverse(num);
    puts("Inversed bits order:");
    to_bits(inversed);

    return 0;
}