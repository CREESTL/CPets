#include <stdio.h>
#include <stdlib.h>

/*
A queue of integers
*/

struct node {
    int data;
    struct node *nextNode;
};

typedef struct node Node; /* alias for node */
typedef Node *NodePtr; /* alias for pointer to a node */

int enqueue(NodePtr *, NodePtr*, int); /* places integer to the end of queue */
int dequeue(NodePtr *, NodePtr*); /* removes integer from the head of queue */
void printQueue(NodePtr); /* prints the queue */
int isEmpty(NodePtr); /* checks that queue is empty */
void instructions(); /* prints instructions */


int main() {
    
    NodePtr headNode = NULL;
    NodePtr tailNode = NULL;
    int choice;
    int number;
    
    instructions(); /* print the menu */
    printf("%s", "--- ");
    scanf("%d", &choice);
    
    while(choice != 4) {
        
        switch (choice) {
            case 1:
                printf("Enter an integer to add to queue: ");
                scanf("\n%d", &number);
                if(!enqueue(&headNode, &tailNode, number)) {
                    puts("Addition failed");
                }
                break;
            case 2:
                if (isEmpty(headNode)) {
                    puts("Sorry, the queue is empty");
                } else {
                    if (!dequeue(&headNode, &tailNode)) {
                        puts("Deletion failed");
                    }
                }
                break;
            case 3:
                printQueue(headNode);
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
        "1: Place integer to the end of queue\n"
        "2: Remove integer from the head of queue\n"
        "3: Print the queue\n"
        "4: Exit\n"
        );
}


void printQueue(NodePtr headNode) {
    if(isEmpty(headNode)) {
        puts("The queue is empty");
        return;
    }
    NodePtr currentPtr = headNode;
    puts("The queue is: ");
    while(currentPtr != NULL) {
        printf("%d --> ", currentPtr->data);
        currentPtr = currentPtr->nextNode;
    }
}

int isEmpty(NodePtr headNode) {
    return headNode == NULL;
}

int enqueue(NodePtr *headNode, NodePtr *tailNode, int number) {
    
    NodePtr newNode;
    
    newNode = malloc(sizeof(Node));
    
    if(newNode == NULL) {
        printf("Sorry, not enough memory");
        return 0;
    } else {
        newNode->data = number;
        newNode->nextNode = NULL;
        /* First integer in queue */
        if (isEmpty(*headNode)) {
            *headNode = newNode;
        } else {
            (*tailNode)->nextNode = newNode;
        }
        
        *tailNode = newNode;

        return 1;
    }
    
}

int dequeue(NodePtr *headNode, NodePtr *tailNode) {

    NodePtr tempNode;
    
    tempNode = *headNode;
    *headNode = (*headNode)->nextNode;

    /* If that was the only integer in queue */
    if (*headNode == NULL) {
        *tailNode = NULL;
    }

    free(tempNode);
    
    return 1;
    
}