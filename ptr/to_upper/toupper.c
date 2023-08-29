#include <stdio.h>
#include <ctype.h>

void convertToUpper(char *);

int main(void) {
    
    char string[] = "deez nuts";
    printf("Initial string is: %s\n", string);
    convertToUpper(string);
    printf("Converted string is: %s\n", string);
    return 0;
} 


void convertToUpper(char * stringPtr) {
    for(; * stringPtr != '\0'; stringPtr++) {
        if (islower(* stringPtr)) {
            * stringPtr = toupper(* stringPtr);
        }
    }
}


const int * const iPtr;