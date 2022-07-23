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

    int *b = ZSinglyLinkedList_peek(linkedList);
    int realValue = *(int32_t*)b;
    printf("%d\n", realValue);

    ZSinglyLinkedList_pop(&linkedList);

    b = ZSinglyLinkedList_peek(linkedList);
    realValue = *(int32_t*)b;
    printf("%d\n", realValue);

    ZSinglyLinkedList_free(&linkedList);
    return 0;
}