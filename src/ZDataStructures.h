#ifndef Z_DATA_STRUCTURES_H_INCLUDED
#define Z_DATA_STRUCTURES_H_INCLUDED

#include <stdio.h> // printf
#include <stdlib.h> // calloc
#include <stdint.h> // int32_t, INT32_MAX
#include <stdbool.h> // bool, true, false

/*
 * Singly Linked List
 */
typedef struct ZSinglyLinkedList {
    void *data;
    struct ZSinglyLinkedList *next;
} ZSinglyLinkedList;

// Allocation and free
void ZSinglyLinkedList_init(ZSinglyLinkedList **head);
void ZSinglyLinkedList_free(ZSinglyLinkedList **head);

// Generic singly linked list functions
void ZSinglyLinkedList_insert(ZSinglyLinkedList **head, void* data);
void ZSinglyLinkedList_delete(ZSinglyLinkedList **head, int32_t position);

// Debug singly linked list functions
void ZSinglyLinkedList_dumpMemory(ZSinglyLinkedList *head, int32_t dataPerLine);

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
static const int32_t ZSTACK_MAX_SIZE = (1024 * 1024);

typedef enum ZStackStatus {
    NO_ERROR,
    FULL_ERROR,
    EMPTY_ERROR,
    STACK_SIZE_TOO_HIGH_ERROR
} ZStackStatus;

typedef struct ZStack {
    size_t stackSize;
    size_t currentPosition;
    void **data;
    ZStackStatus stackStatus;
} ZStack;

// Allocation and free
void ZStack_initEmptyStack(ZStack *p_stack, size_t stackSize);
void ZStack_freeStack(ZStack *p_stack);

// Generic stack functions
void ZStack_push(ZStack *p_stack, void *data);
void ZStack_pop(ZStack *p_stack, void **buffer);
void *ZStack_peek(ZStack *p_stack);

// Checking functions
bool ZStack_isEmpty(ZStack *p_stack);
bool ZStack_isFull(ZStack *p_stack);

// Debug stack functions
void ZStack_dumpMemory(ZStack *p_stack, int32_t dataPerLine);

/*
 * Queue
 */

#endif // Z_DATA_STRUCTURES_H_INCLUDED