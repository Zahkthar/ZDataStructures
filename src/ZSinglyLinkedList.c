#include "ZSinglyLinkedList.h"

/*
 * Singly Linked List
 */

// Allocation and free
ZSinglyLinkedList *ZSinglyLinkedList_create() {
    ZSinglyLinkedList *newList = malloc(sizeof(ZSinglyLinkedList));
    newList->head = NULL;
    newList->length = 0;
    return newList;
}

void ZSinglyLinkedList_free(ZSinglyLinkedList *list) {
    for (size_t i = 0; i < list->length; ++i) {
        ZSinglyLinkedList_deleteFront(list);
    }
    free(list);
}

// Generic ZSinglyLinkedList functions
void ZSinglyLinkedList_insert(ZSinglyLinkedList *list, size_t position, void *data) {
    // Gestion des cas spéciaux
    if(position > list->length) { return; }

    // Insertion en début de liste
    if(position == 0) {
        ZSinglyLinkedListNode *newNode = malloc(sizeof(ZSinglyLinkedListNode));
        newNode->next = list->head;
        newNode->data = data;
        list->head = newNode;

    // Insertion en fin de liste
    } else if(position == list->length) {
        ZSinglyLinkedListNode *tmpHead = list->head;

        while (tmpHead->next != NULL) {
            tmpHead = tmpHead->next;
        }

        ZSinglyLinkedListNode *newNode = malloc(sizeof(ZSinglyLinkedListNode));
        tmpHead->next = newNode;
        newNode->data = data;
        newNode->next = NULL;

    // Insertion dans la liste
    } else {
        ZSinglyLinkedListNode *tmpHead = list->head;
        for(size_t i = 0; i < position - 1; ++i) {
            tmpHead = tmpHead->next;
        }

        ZSinglyLinkedListNode *newNode = malloc(sizeof(ZSinglyLinkedListNode));
        newNode->data = data;
        newNode->next = tmpHead->next;
        tmpHead->next = newNode;
    }

    list->length += 1;
}

void ZSinglyLinkedList_insertFront(ZSinglyLinkedList *list, void *data) {
    ZSinglyLinkedList_insert(list, 0, data);
}

void ZSinglyLinkedList_insertBack(ZSinglyLinkedList *list, void *data) {
    ZSinglyLinkedList_insert(list, list->length, data);
}

void ZSinglyLinkedList_delete(ZSinglyLinkedList *list, size_t position) {
    ZSinglyLinkedListNode *tmpHead = list->head;

    // Gestion des cas spéciaux
    if(position >= list->length) { return; }
    
    // Le premier élément de la liste
    if(position == 0) {
        if(list->head != NULL) {
            list->head = list->head->next;
            free(tmpHead->data);
            free(tmpHead);
        }

    // Le dernier élément de la liste
    } else if(position == list->length - 1) {
        ZSinglyLinkedListNode *tmpHead = list->head;

        while(tmpHead->next->next != NULL) {
            tmpHead = tmpHead->next;
        }

        free(tmpHead->next->data);
        free(tmpHead->next);
        tmpHead->next = NULL;

    // Dans la liste
    } else {
        for(size_t i = 0; i < position - 1; ++i) {
            tmpHead = tmpHead->next;
        }

        ZSinglyLinkedListNode *del = tmpHead->next;
        tmpHead->next = tmpHead->next->next;
        free(del->data);
        free(del);
    }
    
    list->length -= 1;
}

void ZSinglyLinkedList_deleteFront(ZSinglyLinkedList *list) {
    ZSinglyLinkedList_delete(list, 0);
}

void ZSinglyLinkedList_deleteBack(ZSinglyLinkedList *list) {
    ZSinglyLinkedList_delete(list, list->length - 1);
}

void *ZSinglyLinkedList_showValue(ZSinglyLinkedList *list, size_t position) {
    ZSinglyLinkedListNode *tmpHead = list->head;

    // Gestion des cas spéciaux
    if(position == 0 && tmpHead != NULL) { return tmpHead->data; }
    if(position >= list->length) { return NULL; }

    for(size_t i = 0; i < position; ++i) {
        tmpHead = tmpHead->next;
    }

    return tmpHead->data;
}

void *ZSinglyLinkedList_showValueFront(ZSinglyLinkedList *list) {
    return list->head->data;
}

void *ZSinglyLinkedList_showValueBack(ZSinglyLinkedList *list) {
    return ZSinglyLinkedList_showValue(list, list->length - 1);
}

// Search functions
void ZSinglyLinkedList_linearSearch(ZSinglyLinkedList *list, void *data, char *format) {
    (void)list;
    (void)data;
    (void)format;
    // Not implemented yet
}

// Sort functions
void ZSinglyLinkedList_BubbleSort(ZSinglyLinkedList *list) {
    (void)list;
    // Not implemented yet
}

// Debug singly linked list functions
bool ZSinglyLinkedList_isEmpty(ZSinglyLinkedList *list) {
    return (list->length == 0);
}

size_t ZSinglyLinkedList_getLength(ZSinglyLinkedList *list) {
    return list->length;
}

void ZSinglyLinkedList_dumpMemoryPtr(ZSinglyLinkedList *list, int32_t dataPerLine) {
    ZSinglyLinkedList_dumpMemoryFormat(list, dataPerLine, "p");
}

void ZSinglyLinkedList_dumpMemoryFormat(ZSinglyLinkedList *list, int32_t dataPerLine, char *format) {
    ZSinglyLinkedListNode *tmpNode = list->head;
    
    for(size_t i = 0; i < list->length; ++i) {
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

        if((i + 1) % dataPerLine == 0 || tmpNode == NULL) { printf("\n"); }
        tmpNode = tmpNode->next;
    }
}