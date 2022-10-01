#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ZDataStructures.h"

int main(void) {
    ZSinglyLinkedList *list = ZSinglyLinkedList_create();

    int32_t *a = malloc(sizeof(int32_t)); *a = 12;
    ZSinglyLinkedList_pushFront(list, a);
    
    a = malloc(sizeof(int32_t)); *a = 14;
    ZSinglyLinkedList_pushBack(list, a);

    printf("%d\n", *(int32_t*)ZSinglyLinkedList_showValue(list, 0));

    ZSinglyLinkedList_free(list);
    return 0;
}