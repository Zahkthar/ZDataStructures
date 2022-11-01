#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "ZSinglyLinkedList.h"

// Renvoie true si A > B
bool compareIntegersSearch(void *valueA, void *valueB) {
    return *(int32_t*)valueA > *(int32_t*)valueB;
}

void printInteger(void *value) {
    printf("%d ", *(int32_t*)value);
}

int main(void) {
    ZSinglyLinkedList *list = ZSinglyLinkedList_create();

    for(int32_t i = 0; i < 10; ++i) {
        int32_t *a = malloc(sizeof(int32_t));
        *a = i; ZSinglyLinkedList_insertBack(list, a);
    }

    int32_t b = 8;

    ZSinglyLinkedList *positions = ZSinglyLinkedList_linearSearchPositions(list, &b, &compareIntegersSearch);

    ZSinglyLinkedList_dumpMemoryCallback(positions, 20, &printInteger);
    ZSinglyLinkedList_dumpMemoryCallback(list, 20, &printInteger);

    ZSinglyLinkedList_free(positions);
    ZSinglyLinkedList_free(list);
    return 0;
}