#include <stdio.h>


void function1(int a);
void function2(int a);
void function3(int a);


int main(void) {

    void (*funcArr[3]) (int) = {function1, function2, function3};

    int choice;
    
    printf("%s", "Input number of function to call\n\t#1\n\t#2\n\t#3(to stop)\n");
    scanf("%d", &choice);
    
    while (choice >= 1 && choice < 3) {
        (*funcArr[choice - 1])(choice);
        printf("%s", "\nInput number of function to call\n\t#1\n\t#2\n\t#3(to stop)\n");
        scanf("%d", &choice);
    }
    
    return 0;
}


void function1(int a) {
    printf("Function #1 was called with parameter: %d", a);
}
void function2(int a) {
    printf("Function #2 was called with parameter: %d", a);
}
void function3(int a) {
    printf("Function #3 was called with parameter: %d", a);

}