#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "ZSinglyLinkedList.h"

void printFunction(void *value)
{
    printf("%d ", *(int32_t*)value);
}

void *cloneFunction(void *data)
{
    int32_t *newData = malloc(sizeof(int32_t));
    *newData = *(int32_t*)data;
    return newData;
}

void freeFunction(void *value)
{
    free(value);
}

bool testFunction(void *value)
{
    return *(int32_t*)value >= 5;
}

int main(void)
{
    ZSinglyLinkedList *list = ZSinglyLinkedList_create();

    ZSinglyLinkedList_setCallbackFunctions(list, &cloneFunction, &freeFunction);

    for(int i = 0; i < 10; ++i) {
        int32_t *a = malloc(sizeof(int32_t));
        *a = i; ZSinglyLinkedList_insertBack(list, a);
    }

    // ----------------------------------------------------

    int32_t *b = malloc(sizeof(int32_t)); *b = 8;
    
    ZSinglyLinkedList *filteredList = ZSinglyLinkedList_filter(list, &testFunction);
    ZSinglyLinkedList_dumpMemoryCallback(filteredList, 10, &printFunction);

    ZSinglyLinkedList_dumpMemoryCallback(list, 10, &printFunction);

    ZSinglyLinkedList_free(filteredList);
    ZSinglyLinkedList_free(list);
    return 0;
}