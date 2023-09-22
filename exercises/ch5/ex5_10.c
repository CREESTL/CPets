/*

   Round input to the closest integer

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
        printf("Result is: %d\n", (int)floor(input + 0.5));
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