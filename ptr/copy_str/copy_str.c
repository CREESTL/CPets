#include <stdio.h>
#define SIZE 13


void copy_by_index(const char *str1, char *str2) {
    for(int i = 0; (str2[i] = str1[i]) != '\0'; i++) {
        ;
    }
}

void copy_by_offset(const char *str1, char *str2) {
    for(; (*str2 = *str1) != '\0'; str1++, str2++) {
        ;
    }
}

int main(void) {
    
    char str1[SIZE] = "Hello";
    char str2[SIZE];
    char str3[SIZE] = "Good Bye";
    char str4[SIZE];
    
    puts("Initial strings:");
    printf("%s\n", str1);
    printf("%s\n", str2);
    printf("%s\n", str3);
    printf("%s\n", str4);
    
    
    copy_by_index(str1, str2);

    puts("Changed string1 and string2: ");
    printf("%s\n", str1);
    printf("%s\n", str2);

    copy_by_offset(str3, str4);

    puts("Changed string3 and string4: ");
    printf("%s\n", str3);
    printf("%s\n", str4);
    
    return 0;
}