#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "ZSinglyLinkedList.h"

int main(void) {
    ZSinglyLinkedList *list = ZSinglyLinkedList_create();

    for(int i = 0; i < 10; ++i) {
        int32_t *a = malloc(sizeof(int32_t));
        *a = i; ZSinglyLinkedList_insertBack(list, a);
    } 
    
    int32_t *b = malloc(sizeof(int32_t)); *b = 14;
    ZSinglyLinkedList_insert(list, 2, b);

    printf("Is list empty -> %I64d", ZSinglyLinkedList_getLength(list));

    ZSinglyLinkedList_free(list);
    return 0;
}