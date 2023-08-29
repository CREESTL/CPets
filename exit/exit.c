#include <stdio.h>
#include <stdlib.h>


void printOnExit();
    
int main() {

    unsigned int i; 
    atexit(printOnExit);
    puts("Running the program...");
    
    for(i = 0; i < 10; i++) {
        printf("%d\n", i);
    }
    
    exit(EXIT_SUCCESS);
    return 0;
}


void printOnExit() {
    puts("This is the end of the program");
}