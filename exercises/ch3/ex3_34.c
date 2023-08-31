/*

Draw an empty square

*/

#include <stdio.h>


int main() {

    unsigned int size; 
    puts("Enter the size: ");
    scanf("%d", &size);
    
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if ( (row != 0 && row != (size - 1)) && (col != 0 && col != (size - 1)) ) {
                printf("%c ", ' ');
            } else {
                printf("%c ", '*');
            }
        }
        puts("");
        
    }
    
    return 0;
}

