/*

   Use '%g' to output the same number with different precisions

*/

#include <stdio.h>

int main(void)
{
    float num = 9876.12345;
    for (unsigned int p = 0; p < 10; p++)
    {
        printf("%.*g\n", p, num);
    }

    return 0;
}