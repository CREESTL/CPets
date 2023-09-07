/*

Reformat code to avoid using 'continue';

*/



#include <stdio.h>
#include <error.h>
#include <stdlib.h>


/* Old function with continue */
void with_continue();
/* New function without continue */
void no_continue();

int main() {
    
    with_continue();
    no_continue();

    return 0;
}


void with_continue() {
    for (unsigned int i = 0; i < 10; i++) {
        if (i == 5)
            continue;
        printf("%u\n", i);
    }
    puts("Skipped iteration with continue");
}

void no_continue() {
    for (unsigned int i = 0; i < 10; i == 4 ? i+=2 : i++ ) {
        printf("%u\n", i);
    }
    puts("Skipped iteration without continue");
}