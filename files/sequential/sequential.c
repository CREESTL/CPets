#include <stdio.h>
#define NL 100

void write_file(const char *file_name);
    
void read_file(const char *file_name);



int main(void) {

    
    const char *file_name = "./people.abc";
    
    write_file(file_name);
    
    read_file(file_name);
    
    return 0;
}


void write_file(const char *file_name) {

    int id;
    char name[NL];
    unsigned short int age; 
    
    FILE *fPtr;
    
    if ((fPtr = fopen(file_name, "w")) == NULL) {
        puts("Failed to open a file");
    } else {
        puts("Enter ID, name and age");
        puts("Enter EOF to end input");
        printf("-");
        scanf("%d%s%hu", &id, name, &age);
        
        while(!feof(stdin)) {
            fprintf(fPtr, "%d %s %hu\n", id, name, age);
            printf("-");
            scanf("%d%s%hu", &id, name, &age);

        }
        
        fclose(fPtr);
    }

}

void read_file(const char *file_name) {
    
    int id;
    char name[NL];
    unsigned short int age;
    
    FILE *fPtr;
    
    if ((fPtr = fopen(file_name, "r")) == NULL) {
        puts("Failed to read a file");
    } else {
        printf("%10s\t%30s\t%10s\n", "ID", "Name", "Age");
        
        fscanf(fPtr, "%d%s%hu", &id, name, &age);
        
        while(!feof(fPtr)) {
           printf("%10d\t%30s\t%10d\n", id, name, age);
           fscanf(fPtr, "%d%s%hu", &id, name, &age);
        }
    }
    
    fclose(fPtr);
    
}