#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "ZSinglyLinkedList.h"

// TODO :
// - Ajouter la fonction setData dans ZSinglyLinkedList

void *assignFunction(void *data)
{
    int32_t *container = malloc(sizeof(int32_t));
    *(int32_t*)container = *(int32_t*)data;
    return container;
}

bool testFunction(void *value)
{
    return *(int32_t*)value < 5;
}

int main(void)
{
    ZSinglyLinkedList *list = ZSinglyLinkedList_create();

    for(int i = 0; i < 10; ++i) {
        int32_t *a = malloc(sizeof(int32_t));
        *a = i; ZSinglyLinkedList_insertBack(list, a);
    }

    // ----------------------------------------------------

    ZSinglyLinkedList *filteredList = ZSinglyLinkedList_filter(list, &testFunction, &assignFunction);

    *(int32_t*)ZSinglyLinkedList_getNode(list, 4)->data = 12;

    ZSinglyLinkedList_dumpMemoryFormat(list, 10, "d");
    ZSinglyLinkedList_dumpMemoryFormat(filteredList, 10, "d");

    ZSinglyLinkedList_free(list);
    return 0;
}