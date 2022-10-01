#include "ZDataStructures.h"

/*
 * Singly Linked List
 */

// Allocation and free
ZSinglyLinkedList *ZSinglyLinkedList_create() {
    ZSinglyLinkedList *newList = malloc(sizeof(ZSinglyLinkedList));
    newList->head = NULL;
    return newList; 
}

void ZSinglyLinkedList_free(ZSinglyLinkedList *list) {
    while (list->head != NULL) {
        ZSinglyLinkedList_delete(list, 0);
    }
    free(list);
}

// Generic ZSinglyLinkedList functions
void ZSinglyLinkedList_pushFront(ZSinglyLinkedList *list, void* data) {
    ZSinglyLinkedListNode *newNode = malloc(sizeof(ZSinglyLinkedListNode));
    newNode->next = list->head;
    newNode->data = data;
    list->head = newNode;
}

void ZSinglyLinkedList_pushBack(ZSinglyLinkedList *list, void* data) {
    ZSinglyLinkedListNode *tmpHead = list->head;

    if(tmpHead == NULL) {
        ZSinglyLinkedList_pushFront(list, data);
    } else {
        while (tmpHead->next != NULL) {
            tmpHead = tmpHead->next;
        }
        ZSinglyLinkedListNode *newNode = malloc(sizeof(ZSinglyLinkedListNode));
        tmpHead->next = newNode;
        newNode->data = data;
        newNode->next = NULL;
    }
}


void ZSinglyLinkedList_delete(ZSinglyLinkedList *list, size_t position) {
    ZSinglyLinkedListNode *tmpHead = list->head;

    if(position == 0) {
        list->head = list->head->next;
        free(tmpHead->data);
        free(tmpHead);
    } else {
        for(size_t i = 0; i < position - 1; ++i) {
            tmpHead = tmpHead->next;
        }
        ZSinglyLinkedListNode *del = tmpHead->next;
        tmpHead->next = tmpHead->next->next;
        free(del->data);
        free(del);
    }
}

void ZSinglyLinkedList_deleteFront(ZSinglyLinkedList *list) {
    ZSinglyLinkedList_delete(list, 0);
}

void ZSinglyLinkedList_deleteBack(ZSinglyLinkedList *list) {
    ZSinglyLinkedListNode *tmpHead = list->head;
    if(tmpHead != NULL) {
        if(tmpHead->next == NULL) {
            ZSinglyLinkedList_deleteFront(list);
        } else {
            while (tmpHead->next->next != NULL) {
                tmpHead = tmpHead->next;
            }
            free(tmpHead->next->data);
            free(tmpHead->next);
            tmpHead->next = NULL;
        }
    }
}


void *ZSinglyLinkedList_showValue(ZSinglyLinkedList *list, size_t position) {
    if(position < 0) { return NULL; }

    ZSinglyLinkedListNode *tmpHead = list->head;
    for(size_t i = 0; i < position; ++i) {
        if(tmpHead->next != NULL) {
            tmpHead = tmpHead->next;
        } else {
            return NULL;
        }
    }
    return tmpHead->data;
}

void *ZSinglyLinkedList_showValueFront(ZSinglyLinkedList *list) {
    return list->head->data;
}

void *ZSinglyLinkedList_showValueBack(ZSinglyLinkedList *list) {
    ZSinglyLinkedListNode *tmpHead = list->head;

    if(tmpHead == NULL) { return NULL; }

    if(tmpHead->next == NULL) {
        return ZSinglyLinkedList_showValueFront(list);
    } else {
        while (tmpHead->next != NULL) {
            tmpHead = tmpHead->next;
        }
        return tmpHead->data;
    }
}

// Search functions
void ZSinglyLinkedList_linearSearch(ZSinglyLinkedList *list, void* data, char *format) {
    // Not implemented yet
}

// Sort functions
void ZSinglyLinkedList_BubbleSort(ZSinglyLinkedList *list) {
    // Not implemented yet
}

// Debug singly linked list functions
void ZSinglyLinkedList_dumpMemoryPtr(ZSinglyLinkedList *list, int32_t dataPerLine) {
    ZSinglyLinkedList_dumpMemoryFormat(list, dataPerLine, "p");
}

void ZSinglyLinkedList_dumpMemoryFormat(ZSinglyLinkedList *list, int32_t dataPerLine, char *format) {
    ZSinglyLinkedListNode *tmpNode = list->head;
    int position = 0;
    
    while (tmpNode != NULL) {
        switch (format[0]) {
            case 'p': printf("%p ", tmpNode->data); break;
            case 'd': printf("%d ", *(int32_t*)tmpNode->data); break;
            case 'u': printf("%u ", *(uint32_t*)tmpNode->data); break;
            case 'o': printf("%o ", *(int32_t*)tmpNode->data); break;
            case 'x': printf("%x ", *(int32_t*)tmpNode->data); break;
            case 'c': printf("%c ", *(char*)tmpNode->data); break;
            case 's': printf("%s ", *(char**)tmpNode->data); break;
            case 'f': printf("%f ", *(float*)tmpNode->data); break;
            case 'l': if(format[1] == 'f' && strnlen(format, 2) == 2) { printf("%lf ", *(double*)tmpNode->data); } break;

            default: break;
        }
        tmpNode = tmpNode->next;
        ++position;
        if(position + 1 % dataPerLine == 0 || tmpNode == NULL) { printf("\n"); } 
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

/*
 * Queue
 */