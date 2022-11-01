#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "ZSinglyLinkedList.h"

void printInteger(void *value) {
    printf("%d ", *(int32_t*)value);
}

int main(void) {
    ZSinglyLinkedList *list = ZSinglyLinkedList_create();
    for(int32_t i = 0; i < 10; ++i) {
        int32_t *a = malloc(sizeof(int32_t));
        *a = i; ZSinglyLinkedList_insertBack(list, a);
    }

    printf("Before :\n");
    ZSinglyLinkedList_dumpMemoryCallback(list, 20, &printInteger);
    
    ZSinglyLinkedList_reverseList(list);

    printf("After :\n");
    ZSinglyLinkedList_dumpMemoryCallback(list, 20, &printInteger);

    ZSinglyLinkedList_free(list);
    return 0;
}