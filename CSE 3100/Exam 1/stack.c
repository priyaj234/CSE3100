
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

//TODO:
void push(stack *s, node *new_node)
{
    *new_node = *s -> top; //the new node becomes the top of the stack
}

//TODO:
node* pop(stack *s)
{
    *s -> top = top -> next; //the top becomes whatever node is after it.
}

//TODO:
int empty(stack *s)
{
    if(*s -> next == NULL)
}

//TODO:
void clear_stack(stack *s)
{
    stack *n = pop(s);
    while(*s != NULL){
        free(n);
    }
}