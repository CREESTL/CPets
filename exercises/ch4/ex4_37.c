/*

Reformat code to avoid using 'break';

*/



#include <stdio.h>
#include <error.h>
#include <stdlib.h>


/* Old function with break */
void with_break();
/* New function without break */
void no_break();

int main() {
    
    with_break();
    no_break();

    return 0;
}


void with_break() {
    for (unsigned int i = 0; i < 10; i++) {
        if (i == 5)
            break;
        printf("%u\n", i);
    }
    puts("Broke out of the loop with break");
}

void no_break() {
    for (unsigned int i = 0; i < 10 && i != 5; i++) 
        printf("%u\n", i);
    puts("Broke out of the loop with condition");
}