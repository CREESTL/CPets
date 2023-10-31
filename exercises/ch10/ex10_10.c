/*

   Shift an integer 4 bits to the right
   Print it in binary

*/

void to_bits(int x)
{
    printf("Binary representation of %d is: ", x);
    unsigned int mask = 1 << 31;
    for (int i = 0; i < 32; i++)
    {
        putchar(mask & x ? '1' : '0');
        x <<= 1;
    }
    puts("");
}

int main(void)
{
    int num = 1941;
    to_bits(num);
    num >>= 4;
    to_bits(num);

    return 0;
}