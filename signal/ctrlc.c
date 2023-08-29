/*
   Process the interrupting signal (ctrl+c)
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>


void signalHandler();

int main() {

    signal(SIGINT, signalHandler);

    while (1) {
        raise(SIGINT);
    } 
    
    return 0;
}


void signalHandler() {
    
    unsigned int choice;
    
    printf("'CTRL+C' was registered. Would you like to continue?(1 - yes, 2 - no): ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        signal(SIGINT, signalHandler);
    } else {
        exit(EXIT_SUCCESS);
    }
}