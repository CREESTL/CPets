/*

    Multiply integer by 2^N with bits shifting

*/

#include <stdio.h>

int power2(unsigned int num, unsigned int power)
{
    return num << power;
}

int main(void)
{
    int num = 7;
    // 7 * 2^5 = 224
    printf("%d\n", power2(num, 5));
    return 0;
}