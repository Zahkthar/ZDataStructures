#include "ZDynamicArray.h"

ZDynamicArray *ZDynamicArray_create()
{
    ZDynamicArray *newArray = malloc(sizeof(ZDynamicArray));

    newArray->capacity = 16;
    newArray->nbElements = 0;
    newArray->data = malloc(newArray->capacity * sizeof(void*));

    newArray->cloneFunction = NULL;
    newArray->freeFunction = NULL;

    return newArray;
}

void ZDynamicArray_setCallbackFunctions(ZDynamicArray *dynArr, void* (*cloneFunction)(void *data), void (*freeFunction)(void *data))
{
    dynArr->cloneFunction = cloneFunction;
    dynArr->freeFunction = freeFunction;
}

void ZDynamicArray_free(ZDynamicArray *dynArr)
{
    ZDynamicArray_clear(dynArr);
    free(dynArr->data);
    free(dynArr);
}

void ZDynamicArray_clear(ZDynamicArray *dynArr)
{
    for(size_t i = 0; i < dynArr->nbElements; ++i)
    {
        dynArr->freeFunction(dynArr->data[i]);
    }

    dynArr->nbElements = 0;

    ZDynamicArray_resize(dynArr, 16);
}

void ZDynamicArray_resize(ZDynamicArray *dynArr, size_t newSize)
{
    dynArr->capacity = newSize;
    dynArr->data = realloc(dynArr->data, dynArr->capacity * sizeof(void*));
}