#include <stdio.h>
#include <stdlib.h>

/*
A list of characters in alphabetic order
*/

struct node {
    char data;
    struct node *nextNode;
};

typedef struct node Node; /* alias for node */
typedef Node *NodePtr; /* alias for pointer to a node */


int insert(NodePtr *, char); /* inserts an element to a list */
int delete(NodePtr *, char); /* deletes an element from the list */
void printList(NodePtr); /* prints the list */
int isEmpty(NodePtr); /* checks that list is empty */
void instructions(); /* prints instructions */


int main() {
    
    NodePtr startPtr = NULL;
    int choice;
    char character;
    
    instructions(); /* print the menu */
    printf("%s", "--- ");
    scanf("%d", &choice);
    
    while(choice != 4) {
        
        switch (choice) {
            case 1:
                printf("Enter a character to insert: ");
                scanf("\n%c", &character);
                if(!insert(&startPtr, character)) {
                    puts("Insert failed");
                }
                break;
            case 2:
                printf("Enter a character to delete: ");
                scanf("\n%c", &character);
                
                /* Check that list is not empty */
                if (isEmpty(startPtr)) {
                    puts("Sorry, the list is empty");
                } else {
                    if (!delete(&startPtr, character)) {
                        puts("Deletion failed");
                    }
                }
                break;
            case 3:
                printList(startPtr);
                break;
            default:
                puts("Incorrect input");
                instructions();
                break;
        }

        printf("\n%s", "--- ");
        scanf("%d", &choice);
    }

    return 0;
}

void instructions() {
    puts("Enter your choice: \n"
        "1: Insert character into the list\n"
        "2: Delete character from the list\n"
        "3: Print the list\n"
        "4: Exit\n"
        );
}


void printList(NodePtr startPtr) {
    if(isEmpty(startPtr)) {
        puts("The list is empty");
        return;
    }
    NodePtr currentPtr = startPtr;
    puts("The list is: ");
    while(currentPtr != NULL) {
        printf("%c ", currentPtr->data);
        currentPtr = currentPtr->nextNode;
    }
}

int isEmpty(NodePtr startPtr) {
    return startPtr == NULL;
}

int insert(NodePtr *startPtr, char character) {
    
    NodePtr newNode;
    NodePtr prevNode;
    NodePtr curNode;
    
    newNode = malloc(sizeof(Node));
    
    if(newNode == NULL) {
        printf("Sorry, not enough memory");
        return 0;
    } else {
        newNode->data = character;
        newNode->nextNode = NULL;
        
        prevNode = NULL;
        curNode = *startPtr;

        while(curNode != NULL && curNode->data < character) {
            prevNode = curNode;
            curNode = curNode->nextNode;
        }
        
        /* Place new character as the first element of the list */
        if (prevNode == NULL) {
            newNode->nextNode = *startPtr;
            *startPtr = newNode; /* Assign the first element of array */
        /* Place new character between two other characters*/
        } else {
            newNode->nextNode = curNode;
            prevNode->nextNode = newNode;
        }
        return 1;
    }
    
}

int delete(NodePtr *startPtr, char character) {

    NodePtr prevNode = NULL;
    NodePtr curNode = *startPtr; 
    NodePtr tempNode;
    
    /* Delete the first character */
    if (character == (*startPtr)->data) {
       tempNode = *startPtr;
       *startPtr = (*startPtr)->nextNode; /* Assign a new start of list */
       free(tempNode);
       return 1;
    }

    while(curNode != NULL && curNode->data != character) {
        prevNode = curNode;
        curNode = curNode->nextNode;
    }
   
    if (curNode == NULL) { /* No character found */
        return 0;
    } else {
        prevNode->nextNode = curNode->nextNode;
        free(curNode);
        return 1;
    }
}