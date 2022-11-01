#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "ZSinglyLinkedList.h"

// Renvoie true si A > B
bool compareIntegersSort(void *valueA, void *valueB) {
    return *(int32_t*)valueA > *(int32_t*)valueB;
}

void printInteger(void *value) {
    printf("%d ", *(int32_t*)value);
}

int main(void) {
    ZSinglyLinkedList *list = ZSinglyLinkedList_create();

    for(int32_t i = 10; i > 0; --i) {
        int32_t *a = malloc(sizeof(int32_t));
        *a = i; ZSinglyLinkedList_insertBack(list, a);
    }

    ZSinglyLinkedList_BubbleSort(list, &compareIntegersSort);

    ZSinglyLinkedList_dumpMemoryCallback(list, 20, &printInteger);

    ZSinglyLinkedList_free(list);
    return 0;
}