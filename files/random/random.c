#include <stdio.h>
#define NP 20

typedef struct {
    int id;
    char name[30];
    unsigned short int age; 
} Person;

void write_file(const char *file_name);
    
void read_file(const char *file_name);

void update_file(const char *file_name);

int main(void) {

    
    const char *file_name = "./people.abc";
    
    write_file(file_name); /* Create an empty file */
    
    read_file(file_name); /* Read an empty file */
    
    update_file(file_name); /* Add two real persons */

    read_file(file_name); /* Read updated file */
    
    return 0;
}


void write_file(const char *file_name) {
    
    FILE *fPtr;
    unsigned int i;
    
    if ( (fPtr = fopen(file_name, "rb+")) == NULL) {
        puts("Failed to open a file");
    } else {
        Person person = {0, " ", 0};
        for (i = 0; i < NP; i++) {
            fwrite(&person, sizeof(Person), 1, fPtr);
        }
        
        fclose(fPtr);
    }
     
}

void read_file(const char *file_name) {
    
    FILE *fPtr;
    unsigned int i;
    
    if ( (fPtr = fopen(file_name, "rb")) == NULL) {
        puts("Failed to open a file");
    } else {
        Person person = {0, " ", 0};
        printf("%4s%30s%4s\n", "ID", "Name", "Age");
        for (i = 0; i < NP; i++) {
            fread(&person, sizeof(Person), 1, fPtr);
            printf("%4d%30s%4d\n", person.id, person.name, person.age);
        }

        fclose(fPtr);
    }
    
}

void update_file(const char *file_name) {

    FILE *fPtr;
    unsigned int i;

    if ( (fPtr = fopen(file_name, "rb+")) == NULL) {
        puts("Failed to open a file");
    } else {
        Person persons[] = {
            {4, "Agatha", 21},
            {20, "Creestl", 23},
        };
        for(i = 0; i < 2; i++) {
            Person p = persons[i];
            fseek(fPtr, (p.id - 1) * sizeof(Person), SEEK_SET);
            fwrite(&p, sizeof(Person), 1, fPtr);
            puts("Adding new person");
        }

        fclose(fPtr);
    }
    
}