#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ZDataStructures.h"

int main(void) {
    ZSinglyLinkedList *linkedList;
    ZSinglyLinkedList_init(&linkedList);

    int *a = malloc(sizeof(int)); *a = 12;
    ZSinglyLinkedList_insert(&linkedList, a);

    a = malloc(sizeof(int)); *a = 14;
    ZSinglyLinkedList_insert(&linkedList, a);

    ZSinglyLinkedList_dumpMemory(linkedList, 10);

    ZSinglyLinkedList_free(&linkedList);
    return 0;
}