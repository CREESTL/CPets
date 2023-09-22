/*

   Flip a coin

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FLIPS 1e5

#define MIN 1
#define MAX 2

typedef enum
{
    Heads,
    Tails
} Sides;

Sides flip(void);

int main(void)
{
    srand(time(NULL));

    unsigned short times_heads = 0;
    unsigned short times_tails = 0;

    for (unsigned int i = 0; i < FLIPS; i++)
    {
        Sides side = flip();
        if (side == Heads)
            times_heads++;
        else if (side == Tails)
            times_tails++;
    }

    // Number of heads and tails should me somewhat equal
    printf("Number of heads: %hu\nNumber of tails: %hu\n", times_heads, times_tails);
}

Sides flip(void)
{

    unsigned short side = MIN + random() % (MAX - MIN + 1);

    switch (side)
    {
    case 1:
        return Heads;
        break;
    case 2:
        return Tails;
        break;
    }
}
