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
    cr_expect(ZSinglyLinkedList_compareWithArray(list, equalArray, 10, &equalsFunction) == true);
    cr_expect(ZSinglyLinkedList_compareWithArray(list, differentArray, 10, &equalsFunction) == false);

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

    cr_expect(*(int32_t*)(list->head->data) == *newValue);
    cr_expect(list->head->next == NULL);
    cr_expect(list->head == list->tail);

    // insertFront
    newValue = malloc(sizeof(int32_t)); *newValue = 2;
    ZSinglyLinkedList_insertFront(list, newValue);

    cr_expect(*(int32_t*)(list->head->data) == *newValue);
    cr_expect(*(int32_t*)(list->head->next->data) == 1);
    cr_expect(list->head->next == list->tail);

    // insertBack
    newValue = malloc(sizeof(int32_t)); *newValue = 3;
    ZSinglyLinkedList_insertBack(list, newValue);
    
    cr_expect(*(int32_t*)(list->tail->data) == *newValue);
    cr_expect(list->head->next->next == list->tail);
    
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

    cr_expect(ZSinglyLinkedList_compareWithArray(list, compareArray, arraySize, &equalsFunction) == true);

    // deleteFront
    ZSinglyLinkedList_deleteFront(list);
    free(compareArray[0]); memmove(compareArray, compareArray + 1, (arraySize - 1) * sizeof(void*)); arraySize--;
    cr_expect(ZSinglyLinkedList_compareWithArray(list, compareArray, arraySize, &equalsFunction) == true);
    cr_expect(list->length == 9);

    // deleteBack
    ZSinglyLinkedList_deleteBack(list);
    free(compareArray[arraySize - 1]); arraySize--;
    cr_expect(ZSinglyLinkedList_compareWithArray(list, compareArray, arraySize, &equalsFunction) == true);
    cr_expect(list->length == 8);
    
    // delete
    ZSinglyLinkedList_delete(list, 2);
    free(compareArray[2]); memmove(compareArray + 2, compareArray + 3, (arraySize - 1) * sizeof(void*)); arraySize--;
    cr_expect(ZSinglyLinkedList_compareWithArray(list, compareArray, arraySize, &equalsFunction) == true);
    cr_expect(list->length == 7);

    ZSinglyLinkedList_delete(list, 3);
    free(compareArray[3]); memmove(compareArray + 3, compareArray + 4, (arraySize - 1) * sizeof(void*)); arraySize--;
    cr_expect(ZSinglyLinkedList_compareWithArray(list, compareArray, arraySize, &equalsFunction) == true);
    cr_expect(list->length == 6);

    ZSinglyLinkedList_delete(list, 1);
    free(compareArray[1]); memmove(compareArray + 1, compareArray + 2, (arraySize - 1) * sizeof(void*)); arraySize--;
    cr_expect(ZSinglyLinkedList_compareWithArray(list, compareArray, arraySize, &equalsFunction) == true);
    cr_expect(list->length == 5);

    // Libération
    for(size_t i = 0; i < arraySize; ++i) { free(compareArray[i]); }

    ZSinglyLinkedList_free(list);
}

Test(ZSinglyLinkedList, clear)
{
    ZSinglyLinkedList *list = ZSinglyLinkedList_create(&cloneFunction, &freeFunction);

    // Insertion
    int32_t *newValue = NULL;
    for(size_t i = 0; i < 10; ++i)
    {
        newValue = malloc(sizeof(int32_t)); *newValue = i;
        ZSinglyLinkedList_insertBack(list, newValue);
    }

    // Clear
    ZSinglyLinkedList_clear(list);
    cr_expect(list->head == NULL);
    cr_expect(list->tail == NULL);
    cr_expect(list->length == 0);

    ZSinglyLinkedList_free(list);
}

Test(ZSinglyLinkedList, getNode)
{
    ZSinglyLinkedList *list = ZSinglyLinkedList_create(&cloneFunction, &freeFunction);

    // Insertion
    int32_t *newValue = NULL;
    for(size_t i = 0; i < 10; ++i)
    {
        newValue = malloc(sizeof(int32_t)); *newValue = i;
        ZSinglyLinkedList_insertBack(list, newValue);
    }

    cr_expect(ZSinglyLinkedList_getNodeFront(list) == list->head, "The node (getNodeFront) is not the right node");
    cr_expect(ZSinglyLinkedList_getNode(list, 1) == list->head->next, "The node (getNode) is not the right node");   
    cr_expect(ZSinglyLinkedList_getNode(list, 2) == list->head->next->next, "The node (getNode) is not the right node");   
    cr_expect(ZSinglyLinkedList_getNode(list, 3) == list->head->next->next->next, "The node (getNode) is not the right node");   
    cr_expect(ZSinglyLinkedList_getNode(list, 4) == list->head->next->next->next->next, "The node (getNode) is not the right node");    
    cr_expect(ZSinglyLinkedList_getNodeBack(list) == list->tail, "The node (getNodeBack) is not the right node");
    
    ZSinglyLinkedList_free(list);
}

Test(ZSinglyLinkedList, getData)
{
    ZSinglyLinkedList *list = ZSinglyLinkedList_create(&cloneFunction, &freeFunction);
    
    // Insertion
    int32_t *newValue = NULL;
    for(size_t i = 0; i < 10; ++i)
    {
        newValue = malloc(sizeof(int32_t)); *newValue = i;
        ZSinglyLinkedList_insertBack(list, newValue);
    }

    cr_expect(ZSinglyLinkedList_getDataFront(list) == list->head->data, "The data (getDataFront) is not the right data");
    cr_expect(ZSinglyLinkedList_getData(list, 1) == list->head->next->data, "The data (getData) is not the right data");
    cr_expect(ZSinglyLinkedList_getData(list, 2) == list->head->next->next->data, "The data (getData) is not the right data");
    cr_expect(ZSinglyLinkedList_getData(list, 3) == list->head->next->next->next->data, "The data (getData) is not the right data");
    cr_expect(ZSinglyLinkedList_getData(list, 4) == list->head->next->next->next->next->data, "The data (getData) is not the right data");
    cr_expect(ZSinglyLinkedList_getDataBack(list) == list->tail->data, "The data (getDataBack) is not the right data");

    ZSinglyLinkedList_free(list);
}

Test(ZSinglyLinkedList, setData)
{
    ZSinglyLinkedList *list = ZSinglyLinkedList_create(&cloneFunction, &freeFunction);

    // Insertion
    int32_t *newValue = NULL;
    for(size_t i = 0; i < 10; ++i)
    {
        newValue = malloc(sizeof(int32_t)); *newValue = i;
        ZSinglyLinkedList_insertBack(list, newValue);
    }


    cr_expect(list->head->data != NULL, "The data at the head must not be NULL");
    ZSinglyLinkedList_setDataFront(list, NULL);
    cr_expect(list->head->data == NULL, "The data at the head must be NULL");

    cr_expect(list->head->next->data != NULL, "The data at the position 1 must not be NULL");
    ZSinglyLinkedList_setData(list, 1, NULL);
    cr_expect(list->head->next->data == NULL, "The data at the position 1 must be NULL");

    cr_expect(list->head->next->next->data != NULL, "The data at the position 2 must not be NULL");
    ZSinglyLinkedList_setData(list, 2, NULL);
    cr_expect(list->head->next->next->data == NULL, "The data at the position 2 must be NULL");

    cr_expect(list->tail->data != NULL, "The data at the tail must not be NULL");
    ZSinglyLinkedList_setDataBack(list, NULL);
    cr_expect(list->tail->data == NULL, "The data at the tail must not be NULL");

    ZSinglyLinkedList_free(list);
}