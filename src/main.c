#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "ZSinglyLinkedList.h"

int main(void) {
    ZSinglyLinkedList *list = ZSinglyLinkedList_create();

    for(int32_t i = 0; i < 10; ++i) {
        int32_t *a = malloc(sizeof(int32_t));
        *a = i; ZSinglyLinkedList_insertBack(list, a);
    }
    
    int32_t b = 5;

    printf("Is the value of b in the list ? %d\n", ZSinglyLinkedList_linearSearch(list, &b, "d"));

    printf("===========================================\n");

    ZSinglyLinkedList_dumpMemoryFormat(list, 20, "d");

    ZSinglyLinkedList_free(list);
    return 0;
}