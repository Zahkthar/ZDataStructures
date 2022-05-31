#include "ZDataStructures.h"

// Stack
ZStack* ZStack_createEmptyStack(int stackSize) {
    ZStack* stack = malloc(sizeof(ZStack));
    stack->size = stackSize;
    stack->items = malloc(stack->size);

    stack->topPosition = -1;

    return stack;
}

ZStack* ZStack_createStackFilledWithZero(int stackSize) {
    ZStack* stack = malloc(sizeof(ZStack));
    stack->size = stackSize;
    stack->items = calloc(stack->size, sizeof(int));

    stack->topPosition = -1;

    return stack;
}

void ZStack_freeStack(ZStack **stack) {
    free((*stack)->items);
    (*stack)->items = NULL;
    free(*stack);
    *stack = NULL;
}

int ZStack_push(ZStack *stack, int newValue) {
    if(ZStack_isFull(stack)) {
        return -1;
    } else {
        ++stack->topPosition;
        stack->items[stack->topPosition] = newValue;
        return 0;
    }
}

int ZStack_pop(ZStack *stack, int *buffer) {
    if(ZStack_isEmpty(stack)) {
        return -1;
    } else {
        if(buffer != NULL) { *buffer = stack->items[stack->topPosition]; }
        --stack->topPosition;
        return 0;
    }
}

int ZStack_peek(ZStack *stack) {
    if(ZStack_isEmpty(stack)) {
        return -1;
    } else {
        return stack->items[stack->topPosition];
    }
}

int ZStack_isEmpty(ZStack *stack) {
    return (stack->topPosition == (size_t)-1);
}

int ZStack_isFull(ZStack *stack) {
    return (stack->topPosition == stack->size - 1);
}

// Queue
// Linked List