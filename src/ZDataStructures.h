#ifndef Z_DATA_STRUCTURES_H_INCLUDED
#define Z_DATA_STRUCTURES_H_INCLUDED

#include <stdlib.h> // malloc, free
#include <stddef.h> // size_t

// Stack
typedef struct ZStack {
    int *items; // the actual stack implemented as an array
    size_t topPosition; // the current of the position in the stack
    size_t size;
} ZStack;

// Allocation and free functions
ZStack* ZStack_createEmptyStack(int stackSize);
ZStack* ZStack_createStackFilledWithZero(int stackSize);
void ZStack_freeStack(ZStack *stack);

// Generic stack functions
int ZStack_push(ZStack *stack, int newValue);
int ZStack_pop(ZStack *stack, int *buffer);
int ZStack_peek(ZStack *stack);
int ZStack_isEmpty(ZStack *stack);
int ZStack_isFull(ZStack *stack);

// Queue
// Linked List

#endif // Z_DATA_STRUCTURES_H_INCLUDED