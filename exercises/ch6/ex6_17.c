/*

   Recursive sum

*/

#include <stdio.h>

#define SIZE 10

int recursiveSum(const int[], int);

int main(void)
{
    
    int a[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    int x = recursiveSum(a, SIZE);
    printf("The result is: %d\n", x);

    return 0;
}

int recursiveSum(const int b[], int p)
{
    if (p == 1)
        return b[0];
    else
        return b[p - 1] + recursiveSum(b, p - 1);
}