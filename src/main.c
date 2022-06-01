#include <stdio.h>
#include <stdlib.h>
#include "ZDataStructures.h"

void debugStack(ZStack *stack) {
    printf("==================================\n");
    if(stack != NULL) {
        printf("Previous pointer = %p\n", stack->prev);
        printf("Current pointer = %p\n", stack);
        printf("Next pointer = %p\n", stack->next);
        printf("Data value = %d\n", stack->data);
    } else {
        printf("Empty stack !");
    }
}

int main(void)
{
    ZStack *stack = ZStack_createEmptyStack();

    ZStack_push(&stack, 12);
    debugStack(stack);

    ZStack_push(&stack, 200);
    debugStack(stack);

    printf("buffer value = %d\n", ZStack_pop(&stack));
    debugStack(stack);

    printf("peek value = %d\n", ZStack_peek(&stack));

    printf("is the stack empty ? %d\n", ZStack_isEmpty(&stack));
    ZStack_pop(&stack);
    printf("is the stack empty ? %d\n", ZStack_isEmpty(&stack));
    
    debugStack(stack);

    ZStack_freeStack(&stack);
    return 0;
}