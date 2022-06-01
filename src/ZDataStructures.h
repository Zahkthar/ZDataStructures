#ifndef Z_DATA_STRUCTURES_H_INCLUDED
#define Z_DATA_STRUCTURES_H_INCLUDED

#include <stdio.h> //fprintf, stderr
#include <stdlib.h> // malloc, free
#include <stdint.h> // int32_t, INT32_MAX

/*
 * STACK
 */
typedef struct ZStack {
    struct ZStack *prev;
    struct ZStack *next;
    int32_t data;
} ZStack;

// Allocation and free
ZStack* ZStack_createEmptyStack();
void ZStack_freeStack(ZStack **pp_stack);

// Generic stack functions
void ZStack_push(ZStack **pp_stack, int32_t data);
int32_t ZStack_pop(ZStack **pp_stack);
int32_t ZStack_peek(ZStack **pp_stack);
int ZStack_isEmpty(ZStack **pp_stack);

// Queue
// Linked List

#endif // Z_DATA_STRUCTURES_H_INCLUDED