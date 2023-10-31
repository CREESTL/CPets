/*

   Print unions in different ways

*/

#include <stdio.h>

typedef union {
    char c;
    short s;
    int i;
    long b;
} Integer;

typedef union {
    float f;
    double d;
    long double x;
} Float;

int main(void)
{
    /*
       These print OK
    */

    Integer num1;
    num1.c = 97;
    printf("%c\n", num1);

    Integer num2;
    num2.s = 5;
    printf("%hd\n", num2);

    Integer num3;
    num3.i = 31000;
    printf("%d\n", num3);

    Integer num4;
    num4.b = 64000000;
    printf("%ld\n", num4);

    /*
       These print all zeros
    */

    Float num5;
    num5.f = 3.14;
    printf("%f\n", num5);

    Float num6;
    num6.d = 3.1415926535;
    printf("%lf\n", num6);

    Float num7;
    num7.x = 483923.1415926535;
    printf("%lf\n", num7);

    return 0;
}