/*

   Calculate the number of seconds passed since 12 o'clock

*/

#include <error.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int to_seconds(unsigned short, unsigned short, unsigned short);

int main(void)
{

    unsigned short hours;
    unsigned short minutes;
    unsigned short seconds;
    int scanned_1 = 0, scanned_2 = 0, scanned_3 = 0;

    puts("Input a number of hours: ");
    scanned_1 = scanf("%hu", &hours);
    puts("Input a number of minutes: ");
    scanned_2 = scanf("%hu", &minutes);
    puts("Input a number of seconds: ");
    scanned_3 = scanf("%hu", &seconds);

    if (!scanned_1 || !scanned_2 || !scanned_3)
    {
        puts("Invalid input");
        exit(EXIT_FAILURE);
    }

    // Range is 12 hours
    if (hours > 12 || minutes > 12 * 60 || seconds > 3600 * 12)
    {
        puts("Out of range");
        exit(EXIT_FAILURE);
    }

    printf("The result is: %u\n", to_seconds(hours, minutes, seconds));

    return 0;
}

unsigned int to_seconds(unsigned short hours, unsigned short minutes, unsigned short seconds)
{
    return hours * 3600 + minutes * 60 + seconds;
}
