#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "ZSinglyLinkedList.h"

void printInteger(void *value) {
    printf("%d ", *(int32_t*)value);
}

int main(void) {
    ZSinglyLinkedList *list1 = ZSinglyLinkedList_create();
    for(int32_t i = 0; i < 10; ++i) {
        int32_t *a = malloc(sizeof(int32_t));
        *a = i; ZSinglyLinkedList_insertBack(list1, a);
    }

    ZSinglyLinkedList *list2 = ZSinglyLinkedList_create();
    for(int32_t i = 10; i < 20; ++i) {
        int32_t *a = malloc(sizeof(int32_t));
        *a = i; ZSinglyLinkedList_insertBack(list2, a);
    }

    printf("list1 :\n");
    ZSinglyLinkedList_dumpMemoryCallback(list1, 20, &printInteger);
    
    printf("list2 :\n");
    ZSinglyLinkedList_dumpMemoryCallback(list2, 20, &printInteger);

    ZSinglyLinkedList_appendTwoLists(list1, list2);
    
    printf("list1 + list2 :\n");
    ZSinglyLinkedList_dumpMemoryCallback(list1, 20, &printInteger);

    printf("list2 :\n");
    ZSinglyLinkedList_dumpMemoryCallback(list2, 20, &printInteger);

    ZSinglyLinkedList_free(list1);
    return 0;
}