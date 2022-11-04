#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "ZSinglyLinkedList.h"

bool testFunction(void* value) {
    return *(int32_t*)value > 5;
}

int main(void) {
    ZSinglyLinkedList *list = ZSinglyLinkedList_create();
    for(int i = 0; i < 10; ++i) {
        int32_t *a = malloc(sizeof(int32_t));
        *a = i; ZSinglyLinkedList_insertBack(list, a);
    }

    ZSinglyLinkedList *filteredList = ZSinglyLinkedList_filter(list, &testFunction);

    printf("Liste originale :\n");
    ZSinglyLinkedList_dumpMemoryFormat(list, 10, "d");
    
    printf("Liste filtree :\n");
    ZSinglyLinkedList_dumpMemoryFormat(filteredList, 10, "d");

    ZSinglyLinkedList_free(filteredList);
    ZSinglyLinkedList_free(list);
    return 0;
}