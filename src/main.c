#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ZSinglyLinkedList.h"

int main(void) {
    ZSinglyLinkedList *list = ZSinglyLinkedList_create();

    int32_t *a = malloc(sizeof(int32_t)); *a = 12;
    ZSinglyLinkedList_pushFront(list, a);
    
    a = malloc(sizeof(int32_t)); *a = 14;
    ZSinglyLinkedList_pushBack(list, a);

    ZSinglyLinkedList_dumpMemoryFormat(list, 10, "d");

    ZSinglyLinkedList_free(list);
    return 0;
}