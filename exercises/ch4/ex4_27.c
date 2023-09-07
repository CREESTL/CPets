/*

   Brute-force Pythogoris Triplets for integers 1-500

*/

#include <stdio.h>
#include <error.h>
#include <stdlib.h>

#define MAX 500

int main() {
    
    for (unsigned int cat1 = 1; cat1 < MAX; cat1++) {
        for (unsigned int cat2 = 1; cat2 < MAX; cat2++) {
            for (unsigned int hyp = 1; hyp < MAX; hyp++) {
                if (cat1 * cat1 + cat2 * cat2 == hyp * hyp) {
                    printf("Pythogoris Triplet found: \n\tCathet #1: %u\n\tCathet #2: %u\n\tHypotenuse: %u\n", cat1, cat2, hyp);
                }
            }
        }
    }

    return 0;
}


