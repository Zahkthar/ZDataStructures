#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include <criterion/criterion.h>

#include "ZDynamicArray.h"

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

Test(ZDynamicArray, create) {
    ZDynamicArray *dynArr = ZDynamicArray_create(&cloneFunction, &freeFunction);

    cr_expect(dynArr != NULL, "array must not be NULL");
    cr_expect(dynArr->capacity == 16, "dynArr->capacity must be 16");
    cr_expect(dynArr->nbElements == 0, "dynArr->nbElements must be 0");
    cr_expect(dynArr->cloneFunction != NULL, "dynArr->cloneFunction must not be NULL");
    cr_expect(dynArr->freeFunction != NULL, "dynArr->freeFunction must not be NULL");

    ZDynamicArray_free(dynArr);
}

Test(ZDynamicArray, insert)
{
    ZDynamicArray *dynArr = ZDynamicArray_create(&cloneFunction, &freeFunction);    
    int32_t *newValue;

    for(int32_t i = 3; i >= 0; --i)
    {
        newValue = malloc(sizeof(int32_t)); *newValue = i;
        ZDynamicArray_insertFront(dynArr, newValue);

        cr_expect(*(int32_t*)dynArr->data[0] == i, "The value is not correct");
        cr_expect(dynArr->capacity == 16, "The capacity doesn't change at this point");
    }

    for(int32_t i = 10; i < 16; ++i)
    {
        newValue = malloc(sizeof(int32_t)); *newValue = i;
        ZDynamicArray_insertBack(dynArr, newValue);

        cr_expect(*(int32_t*)dynArr->data[dynArr->nbElements - 1] == i, "The value is not correct");
        cr_expect(dynArr->capacity == 16, "The capacity doesn't change at this point");
    }

    for(int32_t i = 9; i > 3; --i)
    {
        newValue = malloc(sizeof(int32_t)); *newValue = i;
        ZDynamicArray_insert(dynArr, 4, newValue);

        cr_expect(*(int32_t*)dynArr->data[4] == i, "The value is not correct");
        cr_expect(dynArr->capacity == 16, "The capacity doesn't change at this point");
    }

    ZDynamicArray_free(dynArr);
}

Test(ZDynamicArray, delete)
{
    ZDynamicArray *dynArr = ZDynamicArray_create(&cloneFunction, &freeFunction);
    int32_t *newValue;

    for(int32_t i = 0; i < 16; ++i)
    {
        newValue = malloc(sizeof(int32_t)); *newValue = i;
        ZDynamicArray_insertBack(dynArr, newValue);
    }

    ZDynamicArray_deleteFront(dynArr);
    cr_expect(*(int32_t*)dynArr->data[0] == 1, "The first value is not correct");
    cr_expect(dynArr->nbElements == 15, "The number of element is not correct");

    ZDynamicArray_deleteBack(dynArr);
    cr_expect(*(int32_t*)dynArr->data[dynArr->nbElements - 1] == 14, "The last value is not correct");
    cr_expect(dynArr->nbElements == 14, "The number of element is not correct");

    ZDynamicArray_delete(dynArr, 1);
    cr_expect(*(int32_t*)dynArr->data[1] == 3, "The value at position 1 is not correct");
    cr_expect(dynArr->nbElements == 13, "The number of element is not correct");

    ZDynamicArray_free(dynArr);
}

Test(ZDynamicArray, clear)
{
    ZDynamicArray *dynArr = ZDynamicArray_create(&cloneFunction, &freeFunction);
    int32_t *newValue;

    for(int32_t i = 0; i < 32; ++i)
    {
        newValue = malloc(sizeof(int32_t)); *newValue = i;
        ZDynamicArray_insertBack(dynArr, newValue);
    }

    ZDynamicArray_clear(dynArr);

    cr_expect(dynArr->capacity == 16, "The capacity is not correct");
    cr_expect(dynArr->nbElements == 0, "Element number is not 0 after a clear");

    ZDynamicArray_free(dynArr);
}

Test(ZDynamicArray, resize)
{
    ZDynamicArray *dynArr = ZDynamicArray_create(&cloneFunction, &freeFunction);
    int32_t *newValue;

    cr_expect(dynArr->capacity == 16, "The initial capacity is not 16");

    for(int32_t i = 0; i < 17; ++i)
    {
        newValue = malloc(sizeof(int32_t)); *newValue = i;
        ZDynamicArray_insertBack(dynArr, newValue);
    }

    cr_expect(dynArr->capacity == 32, "The capacity should be 32");

    for(int32_t i = 17; i < 33; ++i)
    {
        newValue = malloc(sizeof(int32_t)); *newValue = i;
        ZDynamicArray_insertBack(dynArr, newValue);
    }
    
    cr_expect(dynArr->capacity == 64, "The capacity should be 64");

    ZDynamicArray_clear(dynArr);

    cr_expect(dynArr->capacity == 16, "The capacity should be 16");

    ZDynamicArray_free(dynArr);
}

Test(ZDynamicArray, getData)
{
    ZDynamicArray *dynArr = ZDynamicArray_create(&cloneFunction, &freeFunction);
    int32_t *newValue;

    for(int32_t i = 0; i < 32; ++i)
    {
        newValue = malloc(sizeof(int32_t)); *newValue = i;
        ZDynamicArray_insertBack(dynArr, newValue);
    }

    cr_expect(*(int32_t*)ZDynamicArray_getDataFront(dynArr) == 0, "getDataFront doesn't return the right data");

    for(int32_t i = 0; i < 32; ++i)
    {
        cr_expect(*(int32_t*)ZDynamicArray_getData(dynArr, i) == i, "getData doesn't return the right data");
    }

    cr_expect(*(int32_t*)ZDynamicArray_getDataBack(dynArr) == 31, "getDataBack doesn't return the right data");

    ZDynamicArray_free(dynArr);
}

Test(ZDynamicArray, setData)
{
    ZDynamicArray *dynArr = ZDynamicArray_create(&cloneFunction, &freeFunction);
    int32_t *newValue;

    for(int32_t i = 0; i < 32; ++i)
    {
        newValue = malloc(sizeof(int32_t)); *newValue = i;
        ZDynamicArray_insertBack(dynArr, newValue);
    }

    newValue = malloc(sizeof(int32_t)); *newValue = 32;
    ZDynamicArray_setDataFront(dynArr, newValue);
    cr_expect(*(int32_t*)dynArr->data[0] == 32, "setDataFront doesn't set the data correctly");

    for(int32_t i = 33; i < 63; ++i)
    {
        newValue = malloc(sizeof(int32_t)); *newValue = i;
        ZDynamicArray_setData(dynArr, i - 32, newValue);
        cr_expect(*(int32_t*)dynArr->data[i - 32] == i, "setData doesn't set the data correctly");
    }
    
    newValue = malloc(sizeof(int32_t)); *newValue = 63;
    ZDynamicArray_setDataBack(dynArr, newValue);
    cr_expect(*(int32_t*)dynArr->data[dynArr->nbElements - 1] == 63, "setDataBack doesn't set the data correctly");

    ZDynamicArray_free(dynArr);
}

Test(ZDynamicArray, swapData)
{
    ZDynamicArray *dynArr = ZDynamicArray_create(&cloneFunction, &freeFunction);
    int32_t *newValue;

    for(int32_t i = 0; i < 16; ++i)
    {
        newValue = malloc(sizeof(int32_t)); *newValue = i;
        ZDynamicArray_insertBack(dynArr, newValue);
    }

    ZDynamicArray_swapData(dynArr, 0, 1);
    cr_expect(*(int32_t*)dynArr->data[0] == 1, "Values are not swapped");
    cr_expect(*(int32_t*)dynArr->data[1] == 0, "Values are not swapped");
    
    ZDynamicArray_swapData(dynArr, 10, 12);
    cr_expect(*(int32_t*)dynArr->data[10] == 12, "Values are not swapped");
    cr_expect(*(int32_t*)dynArr->data[12] == 10, "Values are not swapped");
    
    ZDynamicArray_swapData(dynArr, 7, 14);
    cr_expect(*(int32_t*)dynArr->data[7] == 14, "Values are not swapped");
    cr_expect(*(int32_t*)dynArr->data[14] == 7, "Values are not swapped");
    
    ZDynamicArray_swapData(dynArr, 8, 2);
    cr_expect(*(int32_t*)dynArr->data[8] == 2, "Values are not swapped");
    cr_expect(*(int32_t*)dynArr->data[2] == 8, "Values are not swapped");

    ZDynamicArray_free(dynArr);
}

Test(ZDynamicArray, appendTwoArrays)
{
    ZDynamicArray *dynArr1 = ZDynamicArray_create(&cloneFunction, &freeFunction);
    ZDynamicArray *dynArr2 = ZDynamicArray_create(&cloneFunction, &freeFunction);
    
    int32_t *newValue1;
    for(int32_t i = 0; i < 64; ++i)
    {
        newValue1 = malloc(sizeof(int32_t)); *newValue1 = i;
        ZDynamicArray_insertBack(dynArr1, newValue1);
    }

    int32_t *newValue2;
    for(int32_t i = 0; i < 32; ++i)
    {
        newValue2 = malloc(sizeof(int32_t)); *newValue2 = i;
        ZDynamicArray_insertBack(dynArr2, newValue2);
    }

    cr_expect(dynArr1->nbElements == 64, "Elements number is not correct");
    cr_expect(dynArr2->nbElements == 32, "Elements number is not correct");
    cr_expect(dynArr1->capacity == 64, "Capacity is not correct");
    cr_expect(dynArr2->capacity == 32, "Capacity is not correct");

    ZDynamicArray_appendTwoArrays(dynArr1, dynArr2, false);

    cr_expect(dynArr1->nbElements == 96, "Elements number is not correct");
    cr_expect(dynArr2->nbElements == 0, "Elements number is not correct");
    cr_expect(dynArr1->capacity == 128, "Capacity is not correct");
    cr_expect(dynArr2->capacity == 16, "Capacity is not correct");

    ZDynamicArray_free(dynArr1);
    ZDynamicArray_free(dynArr2);
}

Test(ZDynamicArray, reverseArray)
{
    ZDynamicArray *dynArr = ZDynamicArray_create(&cloneFunction, &freeFunction);

    int32_t normalArray[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    int32_t reversedArray[] = { 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

    int32_t *newValue;
    for(int32_t i = 0; i < 16; ++i)
    {
        newValue = malloc(sizeof(int32_t)); *newValue = i;
        ZDynamicArray_insertBack(dynArr, newValue);
    }

    for(int32_t i = 0; i < 16; ++i)
    {
        cr_expect(*(int32_t*)dynArr->data[i] == normalArray[i], "Array is not correct");
    }

    ZDynamicArray_reverseArray(dynArr);

    for(int32_t i = 0; i < 16; ++i)
    {
        cr_expect(*(int32_t*)dynArr->data[i] == reversedArray[i], "Array is not reversed");
    }

    ZDynamicArray_free(dynArr);
}

static bool equalsFunction(void *valueA, void *valueB)
{
    return *(int32_t*)valueA == *(int32_t*)valueB;
}

Test(ZDynamicArray, searchFirstOccurence)
{
    ZDynamicArray *dynArr = ZDynamicArray_create(&cloneFunction, &freeFunction);
    int32_t *newValue;

    for(int32_t i = 0; i < 16; ++i)
    {
        newValue = malloc(sizeof(int32_t)); *newValue = i;
        ZDynamicArray_insertBack(dynArr, newValue);
    }

    int32_t *compareValue;
    for(int32_t i = 0; i < 16; ++i)
    {
        compareValue = malloc(sizeof(int32_t)); *compareValue = i;
        cr_expect((int32_t)ZDynamicArray_searchFirstOccurence(dynArr, compareValue, &equalsFunction) == i, "First occurence is not at the good place");
        free(compareValue);
    }

    ZDynamicArray_free(dynArr);
}

Test(ZDynamicArray, searchPositions)
{
    ZDynamicArray *dynArr = ZDynamicArray_create(&cloneFunction, &freeFunction);
    int32_t *newValue;

    for(int32_t i = 0; i < 16; ++i)
    {
        newValue = malloc(sizeof(int32_t)); *newValue = i;
        ZDynamicArray_insertBack(dynArr, newValue);
    }

    *(int32_t*)ZDynamicArray_getData(dynArr, 8) = 7;

    int32_t *compareValue = malloc(sizeof(int32_t)); *compareValue = 7;
    ZDynamicArray *resultArray = ZDynamicArray_searchPositions(dynArr, compareValue, &equalsFunction);
    cr_expect(*(int32_t*)resultArray->data[0] == 7, "Position is not correct");
    cr_expect(*(int32_t*)resultArray->data[1] == 8, "Position is not correct");

    free(compareValue);
    ZDynamicArray_free(dynArr);
}

Test(ZDynamicArray, countOccurrences)
{
    ZDynamicArray *dynArr = ZDynamicArray_create(&cloneFunction, &freeFunction);
    int32_t *newValue;

    for(int32_t i = 0; i < 16; ++i)
    {
        newValue = malloc(sizeof(int32_t)); *newValue = i;
        ZDynamicArray_insertBack(dynArr, newValue);
    }

    *(int32_t*)ZDynamicArray_getData(dynArr, 8) = 7;

    int32_t *compareValue = malloc(sizeof(int32_t)); *compareValue = 7;
    cr_expect(ZDynamicArray_countOccurrences(dynArr, compareValue, &equalsFunction) == 2, "Occurence count is not correct");
    *compareValue = 2;
    cr_expect(ZDynamicArray_countOccurrences(dynArr, compareValue, &equalsFunction) == 1, "Occurence count is not correct");

    free(compareValue);
    ZDynamicArray_free(dynArr);
}

static bool testFunctionFilter(void *valueA)
{
    return *(int32_t*)valueA < 5;
}

Test(ZDynamicArray, filter)
{
    ZDynamicArray *dynArr = ZDynamicArray_create(&cloneFunction, &freeFunction);
    int32_t *newValue;

    for(int32_t i = 0; i < 16; ++i)
    {
        newValue = malloc(sizeof(int32_t)); *newValue = i;
        ZDynamicArray_insertBack(dynArr, newValue);
    }

    int32_t compareArray[] = { 0, 1, 2, 3, 4 };

    ZDynamicArray *filteredArray = ZDynamicArray_filter(dynArr, &testFunctionFilter);

    for(size_t i = 0; i < filteredArray->nbElements; ++i)
    {
        cr_expect(*(int32_t*)filteredArray->data[i] == compareArray[i], "filter value is not correct");
    }

    ZDynamicArray_free(dynArr);
}

static bool sortFunctionArray(void *valueA, void* valueB)
{
    return *(int32_t*)valueA > *(int32_t*)valueB;
}

static int sortFunctionQSort(const void *valueA, const void* valueB)
{
    return (*(int32_t*)valueA - *(int32_t*)valueB);
}

Test(ZDynamicArray, BubbleSort)
{
    ZDynamicArray *dynArr = ZDynamicArray_create(&cloneFunction, &freeFunction);
    
    int32_t array[18] = { 4, 9, 2, 3, 4, 5, 1, 7, 2, 5, 6, 8, 9, 1, 0, 21, 4, 5 };

    int32_t *newValue;
    for(size_t i = 0; i < 18; ++i)
    {
        newValue = malloc(sizeof(int32_t)); *newValue = array[i];
        ZDynamicArray_insertBack(dynArr, newValue);
    }

    qsort(array, 18, sizeof(int32_t), &sortFunctionQSort);
    ZDynamicArray_BubbleSort(dynArr, &sortFunctionArray);

    for(size_t i = 0; i < 18; ++i)
    {
        cr_expect(*(int32_t*)dynArr->data[i] == array[i], "Array is not sorted correctly");
    }

    ZDynamicArray_free(dynArr);
}

Test(ZDynamicArray, isEmpty)
{
    ZDynamicArray *dynArr = ZDynamicArray_create(&cloneFunction, &freeFunction);
    int32_t *newValue;

    cr_expect(ZDynamicArray_isEmpty(dynArr) == true, "Array is empty");

    newValue = malloc(sizeof(int32_t)); *newValue = 12;
    ZDynamicArray_insertBack(dynArr, newValue);

    cr_expect(ZDynamicArray_isEmpty(dynArr) == false, "Array is not empty");

    ZDynamicArray_deleteBack(dynArr);

    cr_expect(ZDynamicArray_isEmpty(dynArr) == true, "Array is empty");

    ZDynamicArray_free(dynArr);
}

Test(ZDynamicArray, isFull)
{
    ZDynamicArray *dynArr = ZDynamicArray_create(&cloneFunction, &freeFunction);
    int32_t *newValue;

    cr_expect(ZDynamicArray_isFull(dynArr) == false, "Array is not full");

    for(int32_t i = 0; i < 16; ++i)
    {
        newValue = malloc(sizeof(int32_t)); *newValue = i;
        ZDynamicArray_insertBack(dynArr, newValue);
    }

    cr_expect(ZDynamicArray_isFull(dynArr) == true, "Array is full");

    ZDynamicArray_deleteBack(dynArr);

    cr_expect(ZDynamicArray_isFull(dynArr) == false, "Array is not full");

    ZDynamicArray_free(dynArr);
}

Test(ZDynamicArray, getLength)
{
    ZDynamicArray *dynArr = ZDynamicArray_create(&cloneFunction, &freeFunction);
    int32_t *newValue;

    for(int32_t i = 0; i < 16; ++i)
    {
        newValue = malloc(sizeof(int32_t)); *newValue = i;
        ZDynamicArray_insertBack(dynArr, newValue);
        cr_expect((int32_t)ZDynamicArray_getLength(dynArr) == i + 1, "The length must be i + 1");
        cr_expect(ZDynamicArray_getLength(dynArr) == dynArr->nbElements, "The length must be equals to dynArr->nbElements");
    }

    ZDynamicArray_free(dynArr);
}

Test(ZDynamicArray, getCapacity)
{
    ZDynamicArray *dynArr = ZDynamicArray_create(&cloneFunction, &freeFunction);
    int32_t *newValue;

    cr_expect(ZDynamicArray_getCapacity(dynArr) == 16, "The getCapacity function doen't return the right value");

    for(int32_t i = 0; i < 17; ++i)
    {
        newValue = malloc(sizeof(int32_t)); *newValue = i;
        ZDynamicArray_insertBack(dynArr, newValue);
    }

    cr_expect(ZDynamicArray_getCapacity(dynArr) == 32, "The getCapacity function doen't return the right value");

    ZDynamicArray_free(dynArr);
}