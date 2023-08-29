#include <stdio.h>
#include <stdlib.h>

/*
A queue of integers
*/

struct node {
    int data;
    struct node *leftNode;
    struct node *rightNode;
};

typedef struct node Node; /* alias for node */
typedef Node *NodePtr; /* alias for pointer to a node */

int insert(NodePtr *, int); /* places leaf of a tree in it's position */
int isEmpty(NodePtr); /* checks that queue is empty */
void inOrder(NodePtr); /* prints tree element from the least to the greatest */
void preOrder(NodePtr); /* prints root, then left subtree, then right subtree */
void pastOrder(NodePtr); /* prints left subtree, then right subtree, then the rott */
void instructions(); /* prints instructions */


int main() {
    
    NodePtr rootNode = NULL;
    int choice;
    int number;
    
    instructions(); /* print the menu */
    printf("%s", "--- ");
    scanf("%d", &choice);
    
    while(choice != 5) {
        
        switch (choice) {
            case 1:
                printf("Enter an integer to add to tree: ");
                scanf("\n%d", &number);
                if(!insert(&rootNode, number)) {
                    puts("Addition failed");
                }
                break;
            case 2:
                inOrder(rootNode);
                break;
            case 3:
                preOrder(rootNode);
                break;
            case 4:
                pastOrder(rootNode);
                break;
            default:
                puts("Invalid choice");
                break;
        }

        printf("\n%s", "--- ");
        scanf("%d", &choice);
    }

    return 0;
}

void instructions() {
    puts("Enter your choice: \n"
        "1: Place integer into the tree\n"
        "2: Iterate over tree in order\n"
        "3: Iterate over tree in preorder\n"
        "4: Iterate over tree in pastorder\n"
        "5: Exit\n"
        );
}


int isEmpty(NodePtr rootNode) {
    return rootNode == NULL;
}

int insert(NodePtr *rootNode, int number) {
    
    NodePtr newNode;
    
    /* If tree (or subtree) is empty */
    if(isEmpty(*rootNode)) {
        *rootNode = malloc(sizeof(Node));
        if(*rootNode == NULL) {
            printf("Sorry, not enough memory");
            return 0;
        } else {
            (*rootNode)->data = number;
            (*rootNode)->rightNode = NULL;
            (*rootNode)->leftNode = NULL;
        } 
    } else {
        if (number > (*rootNode)->data) {
            insert(&((*rootNode)->rightNode), number);
        } else if (number < (*rootNode)->data) {
            insert(&((*rootNode)->leftNode), number);
        } else {
            printf("Dublicate number: %d", number);
        }
    }
    return 1;
}

void inOrder(NodePtr rootNode) {

    if (rootNode != NULL) {
        inOrder(rootNode->leftNode);
        printf("%3d", rootNode->data);
        inOrder(rootNode->rightNode);
    }
}

void preOrder(NodePtr rootNode) {

    if (rootNode != NULL) {
        printf("%3d", rootNode->data);
        preOrder(rootNode->leftNode);
        preOrder(rootNode->rightNode);
    }
}

void pastOrder(NodePtr rootNode) {

    if (rootNode != NULL) {
        pastOrder(rootNode->leftNode);
        pastOrder(rootNode->rightNode);
        printf("%3d", rootNode->data);
    }
}
    