#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Face 0 is ignored
#define SIZE 7

int main(void) {
    
    int face;
    int roll;
    int freqs[SIZE] = {0};

    srand(time(NULL));

    for (roll = 1; roll <= 6000; roll++) {

        face = 1 + rand() % 6;
        
        freqs[face]++;
        
    }
    
    /*
       Each of 6 dice faces should have ~1000 times
    */
    
    printf("%4s%20s\n", "Face", "Number of times");
    for(face = 1; face < SIZE; face++) {
        printf("%2d%15d\n", face, freqs[face]);
    }
    
    
    return 0;
}