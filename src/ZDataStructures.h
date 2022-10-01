#ifndef Z_DATA_STRUCTURES_H_INCLUDED
#define Z_DATA_STRUCTURES_H_INCLUDED

#include <stdio.h> // printf
#include <stdlib.h> // malloc, free
#include <stdint.h> // int32_t
#include <string.h> // strnlen

/*
 * Singly Linked List
 */
typedef struct ZSinglyLinkedList {
    struct ZSinglyLinkedListNode *head;
} ZSinglyLinkedList;

typedef struct ZSinglyLinkedListNode {
    void *data;
    struct ZSinglyLinkedListNode *next;
} ZSinglyLinkedListNode;

// Allocation and free
ZSinglyLinkedList *ZSinglyLinkedList_create();
void ZSinglyLinkedList_free(ZSinglyLinkedList *list);

// Generic ZSinglyLinkedList functions
void ZSinglyLinkedList_pushFront(ZSinglyLinkedList *list, void* data);
void ZSinglyLinkedList_pushBack(ZSinglyLinkedList *list, void* data);

void ZSinglyLinkedList_delete(ZSinglyLinkedList *list, size_t position);
void ZSinglyLinkedList_deleteFront(ZSinglyLinkedList *list);
void ZSinglyLinkedList_deleteBack(ZSinglyLinkedList *list);

void *ZSinglyLinkedList_showValue(ZSinglyLinkedList *list, size_t position);
void *ZSinglyLinkedList_showValueFront(ZSinglyLinkedList *list);
void *ZSinglyLinkedList_showValueBack(ZSinglyLinkedList *list);

// Search functions
void ZSinglyLinkedList_linearSearch(ZSinglyLinkedList *list, void* data, char *format);

// Sort functions
void ZSinglyLinkedList_BubbleSort(ZSinglyLinkedList *list);

// Debug singly linked list functions
void ZSinglyLinkedList_dumpMemoryPtr(ZSinglyLinkedList *list, int32_t dataPerLine);
void ZSinglyLinkedList_dumpMemoryFormat(ZSinglyLinkedList *list, int32_t dataPerLine, char *format);

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

/*
 * Queue
 */

#endif // Z_DATA_STRUCTURES_H_INCLUDED