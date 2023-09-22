/*

   Round input to tens, hundredths and thousandths


*/

#include <error.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{

    float input = 0;
    int scanned = 0;

    puts("Input an number to round it down (-1 to exit): ");
    scanned = scanf("%f", &input);
    if (!scanned)
    {
        puts("Invalid input");
        exit(EXIT_FAILURE);
    }

    while (input != -1)
    {
        printf("Rounded to tens: %lf\n", floor(input * 10 + 0.5) / 10);
        printf("Rounded to hundredths: %lf\n", floor(input * 100 + 0.5) / 100);
        printf("Rounded to thousandths: %lf\n", floor(input * 1000 + 0.5) / 1000);
        puts("Input an number to round it down (-1 to exit): ");
        scanned = scanf("%f", &input);
        if (!scanned)
        {
            puts("Invalid input");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}