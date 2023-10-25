/*

   Output 100.453627 rounded down to int, tenths, hundredths, thousandths

*/

#include <stdio.h>

int main(void)
{
    float a = 100.453627;
    printf("%.0f\n", a);
    printf("%.1f\n", a);
    printf("%.2f\n", a);
    printf("%.3f\n", a);

    return 0;
}