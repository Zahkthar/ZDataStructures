#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "ZSinglyLinkedList.h"

int main(void) {
    ZSinglyLinkedList *list = ZSinglyLinkedList_create();

    for(int32_t i = 10; i > 0; --i) {
        int32_t *a = malloc(sizeof(int32_t));
        *a = i; ZSinglyLinkedList_insertBack(list, a);
    }

    printf("Before :\n");
    ZSinglyLinkedList_dumpMemoryFormat(list, 20, "d");

    ZSinglyLinkedList_BubbleSort(list, "d");
    
    printf("After :\n");
    ZSinglyLinkedList_dumpMemoryFormat(list, 20, "d");

    ZSinglyLinkedList_free(list);
    return 0;
}