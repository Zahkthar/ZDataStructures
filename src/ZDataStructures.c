#include "ZDataStructures.h"

/*
 * Singly Linked List
 */
void ZSinglyLinkedList_init(ZSinglyLinkedList **head) {
    *head = NULL;
}

void ZSinglyLinkedList_free(ZSinglyLinkedList **head) {
    while (*head != NULL) {
        ZSinglyLinkedList_delete(head, 0);
    }
}

void ZSinglyLinkedList_insert(ZSinglyLinkedList **head, void* data) {
    ZSinglyLinkedList *newNode = malloc(sizeof(ZSinglyLinkedList));
    newNode->data = data;
    newNode->next = *head;
    *head = newNode;
}

void ZSinglyLinkedList_delete(ZSinglyLinkedList **head, int32_t position) {
    ZSinglyLinkedList *tmpHead = *head;

    if(position == 0) {
        free((*head)->data);
        *head = (*head)->next;
        free(tmpHead);
    } else {
        for(int32_t i = 0; i < position - 1; ++i) {
            tmpHead = tmpHead->next;
        }
        ZSinglyLinkedList *del = tmpHead->next;
        tmpHead->next = tmpHead->next->next;
        free(del->data);
        free(del);
    }
}

void ZSinglyLinkedList_pop(ZSinglyLinkedList **head) {
    ZSinglyLinkedList_delete(head, 0);
}

void *ZSinglyLinkedList_showValue(ZSinglyLinkedList *head, int32_t position) {
    ZSinglyLinkedList *tmpHead = head;
    for(int32_t i = 0; i < position; ++i) {
        tmpHead = tmpHead->next;
    }
    return tmpHead->data;
}

void *ZSinglyLinkedList_peek(ZSinglyLinkedList *head) {
    return ZSinglyLinkedList_showValue(head, 0);
}

void ZSinglyLinkedList_dumpMemory(ZSinglyLinkedList *node, int32_t dataPerLine) {
    int position = 0;
    while (node != NULL) {
        printf("%p ", node->data);
        node = node->next;
        ++position;
        if(((position + 1) % dataPerLine == 0) || (node == NULL)) { printf("\n"); } 
    }
}

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
    for(size_t i = 0; i < p_stack->stackSize; ++i) {
        free(p_stack->data[i]);
    }
    free(p_stack->data);
    p_stack->stackStatus = (ZStackStatus) NO_ERROR;
}

void ZStack_push(ZStack *p_stack, void *data) {
    if(ZStack_isFull(p_stack) == false) {
        p_stack->currentPosition++;
        p_stack->data[p_stack->currentPosition] = data;
        p_stack->stackStatus = (ZStackStatus) NO_ERROR;
    } else {
        p_stack->stackStatus = (ZStackStatus) FULL_ERROR;
    }
}

void ZStack_pop(ZStack *p_stack, void **buffer) {
    if(ZStack_isEmpty(p_stack) == false) {
        if(buffer != NULL) { *buffer = p_stack->data[p_stack->currentPosition]; }
        p_stack->currentPosition--;
        p_stack->stackStatus = (ZStackStatus) NO_ERROR;
    } else {
        *buffer = NULL;
        p_stack->stackStatus = (ZStackStatus) EMPTY_ERROR;
    }
}

void *ZStack_peek(ZStack *p_stack) {
    if(ZStack_isEmpty(p_stack) == false) {
        p_stack->stackStatus = (ZStackStatus) NO_ERROR;
        return p_stack->data[p_stack->currentPosition];
    } else {
        p_stack->stackStatus = (ZStackStatus) EMPTY_ERROR;
        return NULL;
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
            printf("%p ", p_stack->data[i]);
            if(((i + 1) % dataPerLine == 0 && i != 0) || (i == p_stack->stackSize - 1)) { printf("\n"); }
        }
    }
}

/*
 * Queue
 */