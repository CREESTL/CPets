/**
 *
 * 1. Convert algebraic expression from infix to postfix form
 *    Example: (6 + 2) * 5 - 8 / 4 => 6 2 + 5 * 8 4 / -
 * 2. Evaluate postfix expression
 *
 */


/*

TODO
1. Stop reading infix after newline char. It's 100 length. No need for all.

*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Max length of algebraic expression a user can input */
#define MAX_CHARS 100

/* Max amount of allowed operators */
#define MAX_ALLOWED 6
/* Chars below this index have the 1st order */
#define FO_INDEX 2

// TODO not sure about the order
char allowed[MAX_ALLOWED] = "^*/%+-";


/* Stack node represents one char from expression */
typedef struct stackNode
{
    char data;
    struct stackNode *next_node;
} StackNode;

typedef StackNode *StackNodePtr;


/* Gets array of chars from user */
void get_user_input(char *infix)
{
    puts("Input an algebraic expression: ");
    fgets(infix, MAX_CHARS, stdin);
}

/* Checks if stack is empty */
bool is_empty(const StackNodePtr const *stack_top)
{
    // TODO top is not NULL after last pop???
    return (*stack_top) == NULL;
}

/* Pushes one char onto the stack */
void push(StackNodePtr *stack_top, char value)
{
    if (is_empty(stack_top))
    {
        puts("Invalid stack pointer!");
        exit(EXIT_FAILURE);
    }
    StackNodePtr new_node = malloc(sizeof(StackNode));
    if (new_node != NULL)
    {
        new_node->data = value;
        new_node->next_node = *stack_top;
        *stack_top = new_node;
    }
}

/* Pops one char off the stack */
char pop(StackNodePtr *stack_top)
{
    if (is_empty(stack_top))
    {
        puts("Invalid stack pointer!");
        exit(EXIT_FAILURE);
    }
    StackNodePtr to_free = *stack_top;
    char ret_val = (*stack_top)->data;
    *stack_top = (*stack_top)->next_node;
    free(to_free);
    return ret_val;
}

/* Returns the value at the top of the stack without popping it */
char get_top(StackNodePtr *stack_top)
{
    if (is_empty(stack_top))
    {
        puts("Invalid stack pointer!");
        exit(EXIT_FAILURE);
    }
    return (*stack_top)->data;
}


/* Prints the stack */
void print_stack(StackNodePtr *stack_top)
{
    if (is_empty(stack_top))
    {
        puts("Invalid stack pointer!");
        exit(EXIT_FAILURE);
    }
    while ((*stack_top)->next_node != NULL)
    {
        printf("%c", (*stack_top)->data);
        (*stack_top) = (*stack_top)->next_node;
    }
}

/* Checks if char is an operator */
bool is_operator(char c)
{
    for (int i = 0; i < MAX_ALLOWED; i++)
    {
        if (allowed[i] == c)
            return true;
    }
    return false;
}

/* Checks which of the operators is more important */
int order(char op1, char op2)
{
    if (is_operator(op1) && is_operator(op2))
    {
        int pos1 = -1;
        int pos2 = -1;
        for (int i = 0; i < MAX_ALLOWED; i++)
        {
            if (allowed[i] == op1)
                pos1 = i;
            if (allowed[i] == op2)
                pos2 = i;
        }
        if (pos1 == -1 || pos2 == -1)
        {
            puts("Not found in allowed");
            exit(EXIT_FAILURE);
        }

        if (pos1 == pos2)
        {
            return 0;
        }
        else
        {
            /* Both in first order */
            if (pos1 <= FO_INDEX && pos2 <= FO_INDEX)
                return -1;
            /* Both in second order */
            else if (pos1 >= FO_INDEX && pos2 >= FO_INDEX)
                return 1;
            /* In different orders */
            else
            {
                /* First in first order, second in second order */
                if (pos2 > pos1)
                    return -1;
                /* Second in first order, first in second order */
                else
                    return 1;
            }
        }
    }
    else
    {
        puts("Not operator");
        exit(EXIT_FAILURE);
    }
}

void to_postfix(char *const infix, char *const postfix, StackNodePtr stack)
{
    
    /* Add ( to the stack */
    push(&stack, '(');
    /* Add ) to infix */
    for (int i = 0; i < MAX_CHARS; i++)
    {
        if (infix[i] == '\n')
        {
            infix[i] = ')';
            break;
        }
    }
    /* Current position in infix */
    int in_pos = 0;
    /* Current position in postfix */
    int p_pos = 0;

    while (!is_empty(&stack))
    {
        char el = infix[in_pos];
        /* Ignore spaces */
        if (el == ' ')
        {
            in_pos++;
            continue;
        }
        printf("%c\n", el);
        /* If current char in infix is a digit - copy it to postfix */
        if (isdigit(el))
        {
            postfix[p_pos] = el;
            p_pos++;
        }
        /* If current char in infix is ( - put it on stack */
        else if (el == '(')
        {
            push(&stack, el);
        }
        /* 
        If current char in infix is ) - pop operations from the stack and 
        place them to postfix until ( shows up on the top of the stack.
        Pop ( from the stack and forget about it.
        */
        else if (el == ')')
        {
            while (!is_empty(&stack))
            {
                if (get_top(&stack) == '(')
                {
                    pop(&stack);
                    break;
                } 
                else 
                {
                    if (is_operator(get_top(&stack)))
                    {
                        char from_stack = pop(&stack);
                        postfix[p_pos] = from_stack;
                        p_pos++;
                    }
                }
            }
        }
        /* 
        If current char in infix is operation - pop operations from the 
        stack (if any) if they have greater order than this operation. Place
        them to postfix after that. 
        Place current char in infix on stack
        */
        else if (is_operator(el))
        {
            while (!is_empty(&stack) && is_operator(get_top(&stack)))
            {
                if (order(el, get_top(&stack)) == 1)
                {
                    char from_stack = pop(&stack);
                    postfix[p_pos] = from_stack;
                    p_pos++;
                }
            }
            push(&stack, el);
        }
        /* Increases each run */
        in_pos++;
    }

}

int main(void)
{

    /* Array storing infix form of expression */
    char infix[MAX_CHARS] = {0};
    /*
    Array storing postfix form of expression. It cannot contain more chars
    than the infix
    */
    char postfix[MAX_CHARS] = {0};
    /* Stack for temporary chars */
    StackNodePtr stack = malloc(sizeof(StackNode));

    get_user_input(infix);
    to_postfix(infix, postfix, stack);

    return 0;
}