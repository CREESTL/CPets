/*

   Generate random numbers within given ranges


*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{

    srand(time(NULL));

    // Borders included
    printf("random [1;2]: %d\n", 1 + rand() % (2 - 1 + 1));
    printf("random [1;100]: %d\n", 1 + rand() % (100 - 1 + 1));
    printf("random [0;9]: %d\n", 0 + rand() % (9 - 0 + 1));
    printf("random [1000;1123]: %d\n", 1000 + rand() % (1123 - 1000 + 1));
    printf("random [-3;11]: %d\n", -3 + rand() % (11 - (-3) + 1));
}