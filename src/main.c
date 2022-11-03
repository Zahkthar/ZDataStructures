#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "ZSinglyLinkedList.h"

int main(void) {
    ZSinglyLinkedList *list = ZSinglyLinkedList_create();
    for(int i = 0; i < 10; ++i) {
        int32_t *a = malloc(sizeof(int32_t));
        *a = i; ZSinglyLinkedList_insertBack(list, a);
    }

    ZSinglyLinkedList_swapData(list, 0, 9);

    ZSinglyLinkedList_dumpMemoryFormat(list, 10, "d");

    ZSinglyLinkedList_free(list);
    return 0;
}