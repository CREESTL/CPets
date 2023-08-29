#include <stdio.h>
#include <stdlib.h>

/*
A stack of integers
*/

struct node {
    int data;
    struct node *nextNode;
};

typedef struct node Node; /* alias for node */
typedef Node *NodePtr; /* alias for pointer to a node */


int push(NodePtr *, int); /* places integer on top of the stack */
int pop(NodePtr *); /* deletes an element from the top of the stack */
void printStack(NodePtr); /* prints the stack */
int isEmpty(NodePtr); /* checks that stack is empty */
void instructions(); /* prints instructions */


int main() {
    
    NodePtr topNode = NULL;
    int choice;
    int number;
    
    instructions(); /* print the menu */
    printf("%s", "--- ");
    scanf("%d", &choice);
    
    while(choice != 4) {
        
        switch (choice) {
            case 1:
                printf("Enter an integer to push: ");
                scanf("\n%d", &number);
                if(!push(&topNode, number)) {
                    puts("Push failed");
                }
                break;
            case 2:
                if (isEmpty(topNode)) {
                    puts("Sorry, the stack is empty");
                } else {
                    if (!pop(&topNode)) {
                        puts("Deletion failed");
                    }
                }
                break;
            case 3:
                printStack(topNode);
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
        "1: Place integer on the stack\n"
        "2: Pop integer from the stack\n"
        "3: Print the stack\n"
        "4: Exit\n"
        );
}


void printStack(NodePtr topNode) {
    if(isEmpty(topNode)) {
        puts("The stack is empty");
        return;
    }
    NodePtr currentPtr = topNode;
    puts("The stack is: ");
    while(currentPtr != NULL) {
        printf("%d --> ", currentPtr->data);
        currentPtr = currentPtr->nextNode;
    }
}

int isEmpty(NodePtr topNode) {
    return topNode == NULL;
}

int push(NodePtr *topNode, int number) {
    
    NodePtr newNode;
    
    newNode = malloc(sizeof(Node));
    
    if(newNode == NULL) {
        printf("Sorry, not enough memory");
        return 0;
    } else {
        newNode->data = number;
        newNode->nextNode = *topNode;
        *topNode = newNode;
        
        return 1;
    }
    
}

int pop(NodePtr *topNode) {

    NodePtr tempNode;
    
    tempNode = *topNode;
    *topNode = (*topNode)->nextNode;
    free(tempNode);
    
    return 1;
    
}