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

void freeFunction(void* value)
{
    free(value);
}

int main(void)
{
    ZSinglyLinkedList *list = ZSinglyLinkedList_create();

    ZSinglyLinkedList_setCallbackFunctions(list, &printFunction, &cloneFunction, &freeFunction);

    for(int i = 0; i < 10; ++i) {
        int32_t *a = malloc(sizeof(int32_t));
        *a = i; ZSinglyLinkedList_insertBack(list, a);
    }

    // ----------------------------------------------------

    ZSinglyLinkedList_dumpMemoryFormat(list, 10, "d");
    printf("%d\n", *(int32_t*)ZSinglyLinkedList_getData(list, 1));

    ZSinglyLinkedList_free(list);
    return 0;
}