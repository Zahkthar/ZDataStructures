#include <stdint.h>
#include <stdbool.h>

#include <criterion/criterion.h>

#include "ZSinglyLinkedList.h"

void *cloneFunction(void *value)
{
    int32_t *clone = malloc(sizeof(int32_t));
    *clone = *(int32_t*)value;
    return clone;
}

void freeFunction(void *value)
{
    free(value);
}

Test(ZSinglyLinkedList, create)
{
    ZSinglyLinkedList *list = ZSinglyLinkedList_create(&cloneFunction, &freeFunction);

    cr_assert(list != NULL, "list must not be NULL");
    cr_expect(list->head == NULL, "list->head must be NULL");
    cr_expect(list->tail == NULL, "list->tail must be NULL");
    cr_expect(list->length == 0, "list->length must be 0");
    cr_expect(list->cloneFunction != NULL, "list->cloneFunction must not be NULL");
    cr_expect(list->freeFunction != NULL, "list->freeFunction must not be NULL");

    ZSinglyLinkedList_free(list);
}

Test(ZSinglyLinkedList, insert)
{
    ZSinglyLinkedList *list = ZSinglyLinkedList_create(&cloneFunction, &freeFunction);
    
    // Insertion dans une liste vide
    int32_t *newValue = malloc(sizeof(int32_t)); *newValue = 1;
    ZSinglyLinkedList_insert(list, 0, newValue);

    cr_assert(*(int32_t*)(list->head->data) == *newValue);
    cr_assert(list->head->next == NULL);

    // insertFront
    newValue = malloc(sizeof(int32_t)); *newValue = 2;
    ZSinglyLinkedList_insertFront(list, newValue);

    cr_assert(*(int32_t*)(list->head->data) == *newValue);
    cr_assert(list->head->next == list->tail);

    // insertBack
    newValue = malloc(sizeof(int32_t)); *newValue = 3;
    ZSinglyLinkedList_insertBack(list, newValue);
    
    cr_assert(*(int32_t*)(list->tail->data) == *newValue);
    cr_assert(list->head->next->next == list->tail);
    
    ZSinglyLinkedList_free(list);
}

Test(ZSinglyLinkedList, delete)
{
    ZSinglyLinkedList *list = ZSinglyLinkedList_create(&cloneFunction, &freeFunction);
    
    ZSinglyLinkedList_free(list);
}

Test(ZSinglyLinkedList, clear)
{
    ZSinglyLinkedList *list = ZSinglyLinkedList_create(&cloneFunction, &freeFunction);
    
    ZSinglyLinkedList_free(list);
}

Test(ZSinglyLinkedList, getNode)
{
    ZSinglyLinkedList *list = ZSinglyLinkedList_create(&cloneFunction, &freeFunction);
    
    ZSinglyLinkedList_free(list);
}

Test(ZSinglyLinkedList, getData)
{
    ZSinglyLinkedList *list = ZSinglyLinkedList_create(&cloneFunction, &freeFunction);
    
    ZSinglyLinkedList_free(list);
}

Test(ZSinglyLinkedList, setData)
{
    ZSinglyLinkedList *list = ZSinglyLinkedList_create(&cloneFunction, &freeFunction);

    ZSinglyLinkedList_free(list);
}