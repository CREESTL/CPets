/*

   Find the smallest float number among three

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float smallest(float, float, float);

int main(void)
{
    srand(time(NULL));
    const int MIN = 1e2;
    const int MAX = 1e5;

    // Generate 2 ints, convert to floats and divide
    // The result are 3 positive floats
    float num_1 = (float)(MIN + rand() % (MAX - MIN + 1)) / (float)(MIN + rand() % (MAX - MIN + 1));
    float num_2 = (float)(MIN + rand() % (MAX - MIN + 1)) / (float)(MIN + rand() % (MAX - MIN + 1));
    float num_3 = (float)(MIN + rand() % (MAX - MIN + 1)) / (float)(MIN + rand() % (MAX - MIN + 1));

    // Make some floats negative
    if (rand() > (RAND_MAX * 0.75))
    {
        num_1 *= (-1);
    }

    printf("The numbers are: %f %f %f\n", num_1, num_2, num_3);

    printf("The smallest number is: %f\n", smallest(num_1, num_2, num_3));
    
    return 0;
}

float smallest(float num_1, float num_2, float num_3)
{

    if (num_1 <= num_2)
    {
        if (num_1 < num_3 || num_1 == num_3)
            return num_1;
        else
            return num_3;
    }
    else
    {
        if (num_2 < num_3 || num_2 == num_3)
            return num_2;
        else
            return num_3;
    }
}