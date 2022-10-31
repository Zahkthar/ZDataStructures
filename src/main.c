#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "ZSinglyLinkedList.h"

// Renvoie true si A > B -> tri par ordre croissant
bool compareIntegersSort(void *valueA, void *valueB) {
    return *(int32_t*)valueA > *(int32_t*)valueB;
}

// Renvoie true si A = B
bool compareIntegersSearch(void *valueA, void *valueB) {
    return *(int32_t*)valueA == *(int32_t*)valueB;
}

int main(void) {
    ZSinglyLinkedList *list = ZSinglyLinkedList_create();

    for(int32_t i = 10; i > 0; --i) {
        int32_t *a = malloc(sizeof(int32_t));
        *a = i; ZSinglyLinkedList_insertBack(list, a);
    }

    int32_t b = 8;

    printf("Is value b in list ? %d\n", ZSinglyLinkedList_linearSearch(list, &b, &compareIntegersSearch));

    printf("Before :\n");
    ZSinglyLinkedList_dumpMemoryFormat(list, 20, "d");

    ZSinglyLinkedList_BubbleSort(list, &compareIntegersSort);
    
    printf("After :\n");
    ZSinglyLinkedList_dumpMemoryFormat(list, 20, "d");

    ZSinglyLinkedList_free(list);
    return 0;
}