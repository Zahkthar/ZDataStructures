#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ZDataStructures.h"

int main(void) {
    ZSinglyLinkedList *linkedList;
    ZSinglyLinkedList_init(&linkedList);

    int32_t *a = malloc(sizeof(int32_t)); *a = 12;
    ZSinglyLinkedList_insert(&linkedList, a);

    a = malloc(sizeof(int32_t)); *a = 14;
    ZSinglyLinkedList_insert(&linkedList, a);

    //================================================

    ZSinglyLinkedList_dumpMemory(linkedList, 10);
    
    //================================================

    int *b = ZSinglyLinkedList_peek(linkedList, 0);
    printf("%d\n", *(int32_t*)b);

    ZSinglyLinkedList_delete(&linkedList, 0);

    b = ZSinglyLinkedList_peek(linkedList, 0);
    printf("%d\n", *(int32_t*)b);

    ZSinglyLinkedList_free(&linkedList);
    return 0;
}