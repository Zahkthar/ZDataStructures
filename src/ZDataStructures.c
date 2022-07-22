#include "ZDataStructures.h"

/*
 * Singly Linked List
 */

/*
 * Circular Linked List
 */

/*
 * Doubly Linked List
 */

/*
 * Circular Doubly Linked List
 */

/*
 * Stack
 */
void ZStack_initEmptyStack(ZStack *p_stack, size_t stackSize) {
    if(stackSize >= ZSTACK_MAX_SIZE) {
        p_stack->stackStatus = (ZStackStatus) STACK_SIZE_TOO_HIGH_ERROR;
        p_stack->stackSize = 0; p_stack->data = NULL; p_stack->currentPosition = -1;
        return;
    }
    
    p_stack->stackSize = stackSize;
    p_stack->data = calloc(p_stack->stackSize, sizeof(p_stack->data[0]));
    p_stack->currentPosition = -1;
    p_stack->stackStatus = (ZStackStatus) NO_ERROR;
}

void ZStack_freeStack(ZStack *p_stack) {
    free(p_stack->data);
    p_stack->stackStatus = (ZStackStatus) NO_ERROR;
}

void ZStack_push(ZStack *p_stack, int32_t data) {
    if(ZStack_isFull(p_stack) == false) {
        p_stack->currentPosition++;
        p_stack->data[p_stack->currentPosition] = data;
        p_stack->stackStatus = (ZStackStatus) NO_ERROR;
    } else {
        p_stack->stackStatus = (ZStackStatus) FULL_ERROR;
    }
}

void ZStack_pop(ZStack *p_stack, int32_t *buffer) {
    if(ZStack_isEmpty(p_stack) == false) {
        if(buffer != NULL) { *buffer = p_stack->data[p_stack->currentPosition]; }
        p_stack->currentPosition--;
        p_stack->stackStatus = (ZStackStatus) NO_ERROR;
    } else {
        *buffer = INT32_MAX;
        p_stack->stackStatus = (ZStackStatus) EMPTY_ERROR;
    }
}

int32_t ZStack_peek(ZStack *p_stack) {
    if(ZStack_isEmpty(p_stack) == false) {
        p_stack->stackStatus = (ZStackStatus) NO_ERROR;
        return p_stack->data[p_stack->currentPosition];
    } else {
        p_stack->stackStatus = (ZStackStatus) EMPTY_ERROR;
        return INT32_MAX;
    }
}

bool ZStack_isEmpty(ZStack *p_stack) {
    return (p_stack->currentPosition == -1);
}

bool ZStack_isFull(ZStack *p_stack) {
    return (p_stack->currentPosition == p_stack->stackSize - 1);
}

void ZStack_dumpMemory(ZStack *p_stack, int32_t dataPerLine) {
    if(p_stack->stackStatus != (ZStackStatus) STACK_SIZE_TOO_HIGH_ERROR) {
        for(int i = 0; i < p_stack->stackSize; ++i) {
            printf("%d ", p_stack->data[i]);
            if((i + 1) % dataPerLine == 0 && i != 0) { printf("\n"); }
        }
    }
}

/*
 * Queue
 */