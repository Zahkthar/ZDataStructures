#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "ZSinglyLinkedList.h"

void freeFunction(void* value)
{
    free(value);
}

int main(void)
{
    ZSinglyLinkedList *list = ZSinglyLinkedList_create();

    for(int i = 0; i < 10; ++i) {
        int32_t *a = malloc(sizeof(int32_t));
        *a = i; ZSinglyLinkedList_insertBack(list, a);
    }

    // ----------------------------------------------------

    ZSinglyLinkedList_dumpMemoryFormat(list, 10, "d");
    printf("%d\n", *(int32_t*)ZSinglyLinkedList_getData(list, 1));

    ZSinglyLinkedList_free(list, &freeFunction);
    return 0;
}