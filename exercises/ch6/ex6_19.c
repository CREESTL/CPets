/*

   Roll 2 dice 36 000 times and ouput the number of times each sum of points occured
   7 should be the most common sum
   2 and 12 should be the least common sums

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Min and max number of points
#define MIN 1
#define MAX 6

#define ROLLS 36000

// Possible sums of points are 2-12 (11 total) but first 2 also count
#define SIZE 13

// Roll a dice
unsigned short roll_dice();
// Print number of times each sum has occured
void print_times(unsigned short[SIZE]);

int main(void)
{

    srand(time(NULL));

    // Number of times each sum of points occured
    unsigned short times[SIZE] = {0};

    for (unsigned int roll = 0; roll < ROLLS; roll++)
    {
        unsigned short dice_1 = roll_dice();
        unsigned short dice_2 = roll_dice();

        // Increase the amount of times sum occured
        times[dice_1 + dice_2]++;
    }

    // Print the results
    print_times(times);

    return 0;
}

unsigned short roll_dice()
{
    return (short)MIN + rand() % (MAX - MIN + 1);
}

void print_times(unsigned short times[SIZE])
{
    printf("%10s%10s%10s", "Sum", "Times", "Hist\n");
    for (unsigned int i = 2; i < SIZE; i++)
    {
        printf("%10u%10u%5s", i, times[i], "");
        for (unsigned int j = 0; j < times[i] / 100; j++)
        {
            printf("*");
        }
    puts("");
    }
        
}