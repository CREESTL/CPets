/*

   Find distance between two points

*/


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_X 1
#define MIN_Y 1
#define MAX_X 50
#define MAX_Y 100


float distance(float, float, float, float);

int main(void)
{
    srand(time(NULL));
    
    float x_1, y_1, x_2, y_2;
    // Random number [0; 1]
    float scale = rand() / (float) RAND_MAX;
    // Random float numbers
    x_1 = MIN_X + rand() % (MAX_X - MIN_X + 1) + scale;
    y_1 = MIN_Y + rand() % (MAX_Y - MIN_Y + 1) + scale;
    x_2 = MIN_X + rand() % (MAX_X - MIN_X + 1) + scale;
    y_2 = MIN_Y + rand() % (MAX_Y - MIN_Y + 1) + scale;

    printf("x1 is: %lf\n", x_1);
    printf("y1 is: %lf\n", y_1);
    printf("x2 is: %lf\n", x_2);
    printf("y2 is: %lf\n", y_2);
    
    printf("The distance is: %f\n", distance(x_1, y_1, x_2, y_2));
    return 0;
}

float distance(float x_1, float y_1, float x_2, float y_2)
{
    
    return (float)sqrt(pow(x_2 - x_1, 2) + pow(y_2 - y_1, 2));
}