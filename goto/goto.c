/*
   Implement a cycle with 'goto'
*/

#include <stdio.h>

int main() {
    
    unsigned int counter = 0;

    start:
        if(counter = 10) goto end;
        counter++;
        goto start;

    end:
        printf("Counter is: %d\n", counter);

    return 0;
}
