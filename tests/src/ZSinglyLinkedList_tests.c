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

Test(ZSinglyLinkedList, cloneArray)
{
    ZSinglyLinkedList *firstList = ZSinglyLinkedList_create(&cloneFunction, &freeFunction);
    
    for(size_t i = 0; i < 10; ++i)
    {
        int32_t *newValue = malloc(sizeof(int32_t)); *newValue = i;
        ZSinglyLinkedList_insertBack(firstList, newValue);
    }

    ZSinglyLinkedList *secondList = ZSinglyLinkedList_cloneList(firstList);

    ZSinglyLinkedListNode *firstListCurrentNode = firstList->head;
    ZSinglyLinkedListNode *secondListCurrentNode = secondList->head;

    size_t length = ZSinglyLinkedList_getLength(firstList);

    for(size_t i = 0; i < length; ++i)
    {
        cr_expect(*(int32_t*)firstListCurrentNode->data == *(int32_t*)secondListCurrentNode->data, "The values are not equal");
        cr_expect(firstListCurrentNode->data != secondListCurrentNode->data, "The pointer are equals, the data is not cloned");

        firstListCurrentNode = firstListCurrentNode->next;
        secondListCurrentNode = secondListCurrentNode->next;
    }

    ZSinglyLinkedList_free(firstList);
    ZSinglyLinkedList_free(secondList);
}

Test(ZSinglyLinkedList, swapData)
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

    // Test
    ZSinglyLinkedList_swapData(list, 1, 2);
    void *tmp = compareArray[1]; compareArray[1] = compareArray[2]; compareArray[2] = tmp;
    cr_expect(ZSinglyLinkedList_compareWithArray(list, compareArray, arraySize, &equalsFunction) == true, "The values are not swapped");

    ZSinglyLinkedList_swapData(list, 4, 7);
    tmp = compareArray[4]; compareArray[4] = compareArray[7]; compareArray[7] = tmp;
    cr_expect(ZSinglyLinkedList_compareWithArray(list, compareArray, arraySize, &equalsFunction) == true, "The values are not swapped");

    for(size_t i = 0; i < arraySize; ++i) { free(compareArray[i]); }
    ZSinglyLinkedList_free(list);
}

Test(ZSinglyLinkedList, appendTwoLists)
{
    ZSinglyLinkedList *list1 = ZSinglyLinkedList_create(&cloneFunction, &freeFunction);
    ZSinglyLinkedList *list2 = ZSinglyLinkedList_create(&cloneFunction, &freeFunction);
    void *compareArray[10]; size_t arraySize = 10;

    // Insertion
    int32_t *newValueList = NULL;
    int32_t *newValueArray = NULL;

    for(size_t i = 0; i < 10; ++i)
    {
        newValueList = malloc(sizeof(int32_t)); *newValueList = i;
        newValueArray = malloc(sizeof(int32_t)); *newValueArray = i;

        if(i < 5) { ZSinglyLinkedList_insertBack(list1, newValueList); }
        else { ZSinglyLinkedList_insertBack(list2, newValueList); }

        compareArray[i] = newValueArray;
    }

    // Test
    ZSinglyLinkedList_appendTwoLists(list1, list2);
    cr_expect(ZSinglyLinkedList_compareWithArray(list1, compareArray, arraySize, &equalsFunction) == true, "The list is not append");

    for(size_t i = 0; i < arraySize; ++i) { free(compareArray[i]); }
    ZSinglyLinkedList_free(list1);
    ZSinglyLinkedList_free(list2);
}

Test(ZSinglyLinkedList, reverseList)
{
    ZSinglyLinkedList *list = ZSinglyLinkedList_create(&cloneFunction, &freeFunction);
    void *compareArray[10]; size_t arraySize = 10;

    // Insertion
    int32_t *newValueList = NULL;
    int32_t *newValueArray = NULL;

    for(size_t i = 0; i < 10; ++i)
    {
        newValueList = malloc(sizeof(int32_t)); *newValueList = i;
        newValueArray = malloc(sizeof(int32_t)); *newValueArray = 9 - i;
        ZSinglyLinkedList_insertBack(list, newValueList);
        compareArray[i] = newValueArray;
    }

    // Test
    ZSinglyLinkedList_reverseList(list);
    cr_expect(ZSinglyLinkedList_compareWithArray(list, compareArray, arraySize, &equalsFunction) == true, "the list is not reversed");

    for(size_t i = 0; i < arraySize; ++i) { free(compareArray[i]); }
    ZSinglyLinkedList_free(list);
}

Test(ZSinglyLinkedList, searchFirstOccurence)
{
    ZSinglyLinkedList *list = ZSinglyLinkedList_create(&cloneFunction, &freeFunction);

    // Insertion
    int32_t *newValue = NULL;
    for(size_t i = 0; i < 10; ++i)
    {
        newValue = malloc(sizeof(int32_t)); *newValue = i;
        ZSinglyLinkedList_insertBack(list, newValue);
    }

    int32_t *data = malloc(sizeof(int32_t));
    *data = 0; cr_expect(ZSinglyLinkedList_searchFirstOccurence(list, data, &equalsFunction) == 0, "The data is not at the good position");
    *data = 1; cr_expect(ZSinglyLinkedList_searchFirstOccurence(list, data, &equalsFunction) == 1, "The data is not at the good position");
    *data = 2; cr_expect(ZSinglyLinkedList_searchFirstOccurence(list, data, &equalsFunction) == 2, "The data is not at the good position");
    *data = 3; cr_expect(ZSinglyLinkedList_searchFirstOccurence(list, data, &equalsFunction) == 3, "The data is not at the good position");
    *data = 4; cr_expect(ZSinglyLinkedList_searchFirstOccurence(list, data, &equalsFunction) == 4, "The data is not at the good position");
    *data = 5; cr_expect(ZSinglyLinkedList_searchFirstOccurence(list, data, &equalsFunction) == 5, "The data is not at the good position");
    *data = 6; cr_expect(ZSinglyLinkedList_searchFirstOccurence(list, data, &equalsFunction) == 6, "The data is not at the good position");
    *data = 7; cr_expect(ZSinglyLinkedList_searchFirstOccurence(list, data, &equalsFunction) == 7, "The data is not at the good position");
    *data = 8; cr_expect(ZSinglyLinkedList_searchFirstOccurence(list, data, &equalsFunction) == 8, "The data is not at the good position");
    *data = 9; cr_expect(ZSinglyLinkedList_searchFirstOccurence(list, data, &equalsFunction) == 9, "The data is not at the good position");

    ZSinglyLinkedList_free(list);
}

Test(ZSinglyLinkedList, searchPositions)
{
    ZSinglyLinkedList *list = ZSinglyLinkedList_create(&cloneFunction, &freeFunction);
    void *compareArray[10]; size_t arraySize = 0;

    // Insertion
    int32_t *newValueList = NULL;
    int32_t *newValueArray = NULL;

    for(size_t i = 0; i < 10; ++i) {
        newValueList = malloc(sizeof(int32_t)); *newValueList = i % 2;
        ZSinglyLinkedList_insertBack(list, newValueList);

        if(i % 2 == 1) { newValueArray = malloc(sizeof(int32_t)); *newValueArray = i; compareArray[arraySize] = newValueArray; arraySize++; }
    }

    int32_t* data = malloc(sizeof(int32_t)); *data = 1;
    ZSinglyLinkedList *occurenceList = ZSinglyLinkedList_searchPositions(list, data, &equalsFunction);
    
    cr_expect(ZSinglyLinkedList_compareWithArray(occurenceList, compareArray, arraySize, &equalsFunction) == true, "Les positions ne sont pas correctes");

    // Libération
    for(size_t i = 0; i < arraySize; ++i) { free(compareArray[i]); }
    ZSinglyLinkedList_free(occurenceList);
    ZSinglyLinkedList_free(list);
}

Test(ZSinglyLinkedList, countOccurrences)
{
    ZSinglyLinkedList *list = ZSinglyLinkedList_create(&cloneFunction, &freeFunction);

    // Insertion
    int32_t *newValue = NULL;
    for(size_t i = 0; i < 10; ++i)
    {
        newValue = malloc(sizeof(int32_t)); *newValue = 4;
        ZSinglyLinkedList_insertBack(list, newValue);
    }

    int32_t *data = malloc(sizeof(int32_t)); *data = 4;
    cr_expect(ZSinglyLinkedList_countOccurrences(list, data, &equalsFunction) == 10, "The occurence count is not correct");

    ZSinglyLinkedList_free(list);
}

static bool compareFunctionFilter(void *valueA)
{
    return *(int32_t*)valueA >= 5;
}

Test(ZSinglyLinkedList, filter)
{
    ZSinglyLinkedList *list = ZSinglyLinkedList_create(&cloneFunction, &freeFunction);
    void *compareArray[10]; size_t arraySize = 0;

    // Insertion
    int32_t *newValueList = NULL;
    int32_t *newValueArray = NULL;

    for(size_t i = 0; i < 10; ++i) {
        newValueList = malloc(sizeof(int32_t)); *newValueList = i;
        ZSinglyLinkedList_insertBack(list, newValueList);

        if(i >= 5)
        {
            newValueArray = malloc(sizeof(int32_t)); *newValueArray = i;
            compareArray[arraySize] = newValueArray; arraySize++;
        }
    }

    ZSinglyLinkedList *filteredList = ZSinglyLinkedList_filter(list, &compareFunctionFilter);

    cr_expect(ZSinglyLinkedList_compareWithArray(filteredList, compareArray, arraySize, &equalsFunction) == true);

    // Libération
    for(size_t i = 0; i < arraySize; ++i) { free(compareArray[i]); }
    ZSinglyLinkedList_free(list);
}

static bool compareFunctionSort(void *valueA, void *valueB)
{
    return *(int32_t*)valueA > *(int32_t*)valueB;
}

Test(ZSinglyLinkedList, BubbleSort)
{
    ZSinglyLinkedList *list = ZSinglyLinkedList_create(&cloneFunction, &freeFunction);
    void *compareArray[10]; size_t arraySize = 10;

    // Insertion
    int32_t *newValueList = NULL;
    int32_t *newValueArray = NULL;

    for(size_t i = 0; i < 10; ++i)
    {
        newValueList = malloc(sizeof(int32_t)); *newValueList = 9 - i;
        newValueArray = malloc(sizeof(int32_t)); *newValueArray = i;
        ZSinglyLinkedList_insertBack(list, newValueList);
        compareArray[i] = newValueArray;
    }

    ZSinglyLinkedList_BubbleSort(list, &compareFunctionSort);

    cr_expect(ZSinglyLinkedList_compareWithArray(list, compareArray, arraySize, &equalsFunction));

    // Libération
    for(size_t i = 0; i < arraySize; ++i) { free(compareArray[i]); }
    ZSinglyLinkedList_free(list);
}

Test(ZSinglyLinkedList, isCircular)
{
    ZSinglyLinkedList *list = ZSinglyLinkedList_create(&cloneFunction, &freeFunction);

    // Insertion
    int32_t *newValue = NULL;
    for(size_t i = 0; i < 10; ++i)
    {
        newValue = malloc(sizeof(int32_t)); *newValue = i;
        ZSinglyLinkedList_insertBack(list, newValue);
    }
    cr_expect(ZSinglyLinkedList_isCircular(list) == false, "La liste n'est pas circulaire");
    
    list->tail->next = list->head; // insertBack insèrerais la liste en tant que data et non en tant que noeud
    
    cr_expect(ZSinglyLinkedList_isCircular(list) == true, "La liste est circulaire");

    ZSinglyLinkedList_free(list);
}

Test(ZSinglyLinkedList, isEmpty)
{
    ZSinglyLinkedList *list = ZSinglyLinkedList_create(&cloneFunction, &freeFunction);

    cr_expect(ZSinglyLinkedList_isEmpty(list) == true, "La liste est vide");

    int32_t *newValue = malloc(sizeof(int32_t)); *newValue = 10;
    ZSinglyLinkedList_insertBack(list, newValue);

    cr_expect(ZSinglyLinkedList_isEmpty(list) == false, "La liste n'est pas vide");

    ZSinglyLinkedList_free(list);
}

Test(ZSinglyLinkedList, getLength)
{
    ZSinglyLinkedList *list = ZSinglyLinkedList_create(&cloneFunction, &freeFunction);

    // Insertion
    int32_t *newValue = NULL;
    for(size_t i = 0; i < 10; ++i)
    {
        newValue = malloc(sizeof(int32_t)); *newValue = i;
        ZSinglyLinkedList_insertBack(list, newValue);

        cr_expect(ZSinglyLinkedList_getLength(list) == i + 1, "The size is wrong");
    }

    ZSinglyLinkedList_free(list);
}