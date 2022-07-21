#ifndef Z_DATA_STRUCTURES_H_INCLUDED
#define Z_DATA_STRUCTURES_H_INCLUDED

#include <stdio.h> // printf
#include <stdlib.h> // calloc
#include <stdint.h> // int32_t, INT32_MAX
#include <stdbool.h> // bool, true, false

/*
 * STACK
 */
static const int32_t ZSTACK_MAX_SIZE = 100;

typedef enum ZStackStatus {
    NO_ERROR,
    FULL_ERROR,
    EMPTY_ERROR,
    STACK_SIZE_TOO_HIGH_ERROR
} ZStackStatus;

typedef struct ZStack {
    int32_t stackSize;
    int32_t currentPosition;
    int32_t *data;
    ZStackStatus stackStatus;
} ZStack;

// Allocation and free
void ZStack_initEmptyStack(ZStack *p_stack, size_t stackSize);
void ZStack_freeStack(ZStack *p_stack);

// Generic stack functions
void ZStack_push(ZStack *p_stack, int32_t data);
void ZStack_pop(ZStack *p_stack, int32_t *buffer);
int32_t ZStack_peek(ZStack *p_stack);

// Checking functions
bool ZStack_isEmpty(ZStack *p_stack);
bool ZStack_isFull(ZStack *p_stack);

// Debug stack functions
void ZStack_dumpMemory(ZStack *p_stack, int32_t dataPerLine);

// Queue
// Linked List

#endif // Z_DATA_STRUCTURES_H_INCLUDED