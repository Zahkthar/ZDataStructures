#include <stdbool.h>

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

Test(ZDynamicArray, clear)
{
    ZDynamicArray *dynArr = ZDynamicArray_create(&cloneFunction, &freeFunction);
    
    ZDynamicArray_free(dynArr);
}

Test(ZDynamicArray, resize)
{
    ZDynamicArray *dynArr = ZDynamicArray_create(&cloneFunction, &freeFunction);
    
    ZDynamicArray_free(dynArr);
}

Test(ZDynamicArray, insert)
{
    ZDynamicArray *dynArr = ZDynamicArray_create(&cloneFunction, &freeFunction);
    
    ZDynamicArray_free(dynArr);
}

Test(ZDynamicArray, delete)
{
    ZDynamicArray *dynArr = ZDynamicArray_create(&cloneFunction, &freeFunction);
    
    ZDynamicArray_free(dynArr);
}

Test(ZDynamicArray, getData)
{
    ZDynamicArray *dynArr = ZDynamicArray_create(&cloneFunction, &freeFunction);
    
    ZDynamicArray_free(dynArr);
}

Test(ZDynamicArray, setData)
{
    ZDynamicArray *dynArr = ZDynamicArray_create(&cloneFunction, &freeFunction);
    
    ZDynamicArray_free(dynArr);
}

Test(ZDynamicArray, swapData)
{
    ZDynamicArray *dynArr = ZDynamicArray_create(&cloneFunction, &freeFunction);
    
    ZDynamicArray_free(dynArr);
}

Test(ZDynamicArray, appendTwoArrays)
{
    ZDynamicArray *dynArr = ZDynamicArray_create(&cloneFunction, &freeFunction);
    
    ZDynamicArray_free(dynArr);
}

Test(ZDynamicArray, reverseArray)
{
    ZDynamicArray *dynArr = ZDynamicArray_create(&cloneFunction, &freeFunction);
    
    ZDynamicArray_free(dynArr);
}

Test(ZDynamicArray, searchFirstOccurence)
{
    ZDynamicArray *dynArr = ZDynamicArray_create(&cloneFunction, &freeFunction);
    
    ZDynamicArray_free(dynArr);
}

Test(ZDynamicArray, searchPositions)
{
    ZDynamicArray *dynArr = ZDynamicArray_create(&cloneFunction, &freeFunction);
    
    ZDynamicArray_free(dynArr);
}

Test(ZDynamicArray, countOccurrences)
{
    ZDynamicArray *dynArr = ZDynamicArray_create(&cloneFunction, &freeFunction);
    
    ZDynamicArray_free(dynArr);
}

Test(ZDynamicArray, filter)
{
    ZDynamicArray *dynArr = ZDynamicArray_create(&cloneFunction, &freeFunction);
    
    ZDynamicArray_free(dynArr);
}

Test(ZDynamicArray, BubbleSort)
{
    ZDynamicArray *dynArr = ZDynamicArray_create(&cloneFunction, &freeFunction);
    
    ZDynamicArray_free(dynArr);
}

Test(ZDynamicArray, isEmpty)
{
    ZDynamicArray *dynArr = ZDynamicArray_create(&cloneFunction, &freeFunction);
    
    ZDynamicArray_free(dynArr);
}

Test(ZDynamicArray, isFull)
{
    ZDynamicArray *dynArr = ZDynamicArray_create(&cloneFunction, &freeFunction);
    
    ZDynamicArray_free(dynArr);
}

Test(ZDynamicArray, getLength)
{
    ZDynamicArray *dynArr = ZDynamicArray_create(&cloneFunction, &freeFunction);
    
    ZDynamicArray_free(dynArr);
}

Test(ZDynamicArray, getCapacity)
{
    ZDynamicArray *dynArr = ZDynamicArray_create(&cloneFunction, &freeFunction);
    
    ZDynamicArray_free(dynArr);
}