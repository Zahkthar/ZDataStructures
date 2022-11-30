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

bool equalsFunction(void *valueA, void *valueB)
{
    return *(int32_t*)valueA == *(int32_t*)valueB;
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

Test(ZSinglyLinkedList, compareWithArray)
{
    ZSinglyLinkedList *list = ZSinglyLinkedList_create(&cloneFunction, &freeFunction);
    void *equalArray[10];
    void *differentArray[10];

    // Insertion dans la liste et dans le tableau
    int32_t *newValueList = NULL;
    
    int32_t *newValueEqualsArray = NULL;
    int32_t *newValueDifferentArray = NULL;
    
    for(size_t i = 0; i < 10; ++i)
    {
        newValueList = malloc(sizeof(int32_t)); *newValueList = i;
        newValueEqualsArray = malloc(sizeof(int32_t)); *newValueEqualsArray = i;
        newValueDifferentArray = malloc(sizeof(int32_t)); *newValueDifferentArray = i + 1;

        ZSinglyLinkedList_insertBack(list, newValueList);
        equalArray[i] = newValueEqualsArray;
        differentArray[i] = newValueDifferentArray;
    }

    // Comparaison
    cr_assert(ZSinglyLinkedList_compareWithArray(list, equalArray, 10, &equalsFunction) == true);
    cr_assert(ZSinglyLinkedList_compareWithArray(list, differentArray, 10, &equalsFunction) == false);

    // Libération
    for(size_t i = 0; i < 10; ++i) { free(equalArray[i]); free(differentArray[i]); }

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
    cr_assert(list->head == list->tail);

    // insertFront
    newValue = malloc(sizeof(int32_t)); *newValue = 2;
    ZSinglyLinkedList_insertFront(list, newValue);

    cr_assert(*(int32_t*)(list->head->data) == *newValue);
    cr_assert(*(int32_t*)(list->head->next->data) == 1);
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
    void *compareArray[10]; size_t arraySize = 10;

    // Insertion
    int32_t *newValueList = NULL;
    int32_t *newValueArray = NULL;

    for(size_t i = 0; i < 10; ++i)
    {
        newValueList = malloc(sizeof(int32_t)); *newValueList = i;
        newValueArray = malloc(sizeof(int32_t)); *newValueArray = i;

        ZSinglyLinkedList_insertBack(list, newValueList);
        compareArray[i] = newValueArray;
    }

    cr_assert(ZSinglyLinkedList_compareWithArray(list, compareArray, arraySize, &equalsFunction) == true);

    // deleteFront
    ZSinglyLinkedList_deleteFront(list);
    free(compareArray[0]); memmove(compareArray, compareArray + 1, (arraySize - 1) * sizeof(void*)); arraySize--;
    cr_assert(ZSinglyLinkedList_compareWithArray(list, compareArray, arraySize, &equalsFunction) == true);
    cr_assert(list->length == 9);

    // deleteBack
    ZSinglyLinkedList_deleteBack(list);
    free(compareArray[arraySize - 1]); arraySize--;
    cr_assert(ZSinglyLinkedList_compareWithArray(list, compareArray, arraySize, &equalsFunction) == true);
    cr_assert(list->length == 8);
    
    // delete
    ZSinglyLinkedList_delete(list, 2);
    free(compareArray[2]); memmove(compareArray + 2, compareArray + 3, (arraySize - 1) * sizeof(void*)); arraySize--;
    cr_assert(ZSinglyLinkedList_compareWithArray(list, compareArray, arraySize, &equalsFunction) == true);
    cr_assert(list->length == 7);

    ZSinglyLinkedList_delete(list, 3);
    free(compareArray[3]); memmove(compareArray + 3, compareArray + 4, (arraySize - 1) * sizeof(void*)); arraySize--;
    cr_assert(ZSinglyLinkedList_compareWithArray(list, compareArray, arraySize, &equalsFunction) == true);
    cr_assert(list->length == 6);

    ZSinglyLinkedList_delete(list, 1);
    free(compareArray[1]); memmove(compareArray + 1, compareArray + 2, (arraySize - 1) * sizeof(void*)); arraySize--;
    cr_assert(ZSinglyLinkedList_compareWithArray(list, compareArray, arraySize, &equalsFunction) == true);
    cr_assert(list->length == 5);

    // Libération
    for(size_t i = 0; i < arraySize; ++i) { free(compareArray[i]); }

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