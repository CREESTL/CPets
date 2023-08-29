/*
   Copies characters from one file to another
*/

#include <stdio.h>


int main(int argc, char *argv[]) {
    
    if (argc < 3) {
        puts("Invalid amount of args");
        return 1;
    }
    
    FILE *outFilePtr;
    FILE *inFilePtr;
    int character;
    
    if ((outFilePtr = fopen(argv[1], "r")) == NULL) {
        puts("Failed to open output file");
    } else {
        if ((inFilePtr = fopen(argv[2], "w+")) == NULL) {
            puts("Failed to open input file");
        } else {
            
            while ((character = fgetc(outFilePtr)) != EOF) {
                fputc(character, inFilePtr);
            }
            
        }
    }
    return 0;
}

