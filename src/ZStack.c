#include "ZStack.h"

/*
 * Allocation, free and clear
 */
ZStack *ZStack_create(void* (*cloneFunction)(void *data), void (*freeFunction)(void *data))
{
    return ZDynamicArray_create(cloneFunction, freeFunction);
}

void ZStack_free(ZStack *stack)
{
    ZDynamicArray_free(stack);
}

void ZStack_clear(ZStack *stack)
{
    ZDynamicArray_clear(stack);
}

/*
 * Generic ZStack functions
 */
void ZStack_push(ZStack *stack, void *data)
{
    ZDynamicArray_insertBack(stack, data);
}

void *ZStack_pop(ZStack *stack)
{
    void *value = ZDynamicArray_getDataBack(stack);
    ZDynamicArray_deleteBack(stack);
    return value;
}

void *ZStack_peek(ZStack *stack)
{
    return ZDynamicArray_getDataBack(stack);
}

void *ZStack_peekPosition(ZStack *stack, size_t position)
{
    return ZDynamicArray_getData(stack, position);
}

/*
 * Processing functions
 */
ZStack *ZStack_cloneStack(ZStack *stack)
{
    return ZDynamicArray_cloneArray(stack);
}

void ZStack_pushStack(ZStack *stackA, ZStack *stackB, bool freeStackB)
{
    ZDynamicArray_appendTwoArrays(stackA, stackB, freeStackB);
}

void ZStack_reverseStack(ZStack *stack)
{
    ZDynamicArray_reverseArray(stack);
}

/*
 * Search functions
 */
size_t ZStack_searchFirstOccurence(ZStack *stack, void *data, bool (*testFunction)(void *valueA, void *valueB))
{
    return ZDynamicArray_searchFirstOccurence(stack, data, testFunction);
}

ZDynamicArray *ZStack_searchPositions(ZStack *stack, void *data, bool (*testFunction)(void *valueA, void *valueB))
{
    return ZDynamicArray_searchPositions(stack, data, testFunction);
}

size_t ZStack_countOccurrences(ZStack *stack, void *data, bool (*testFunction)(void *valueA, void *valueB))
{
    return ZDynamicArray_countOccurrences(stack, data, testFunction);
}

ZDynamicArray *ZStack_filter(ZStack *stack, bool (*testFunction)(void *value))
{
    return ZDynamicArray_filter(stack, testFunction);
}

/*
 * Debug DynamicArray functions
 */
bool ZStack_isEmpty(ZStack *stack)
{
    return ZDynamicArray_isEmpty(stack);
}

size_t ZStack_getSize(ZStack *stack)
{
    return ZDynamicArray_getLength(stack);
}

void ZStack_dumpMemoryFormat(ZStack *stack, int32_t dataPerLine, char *format)
{
    ZStack_dumpMemoryFormat(stack, dataPerLine, format);
}

void ZStack_dumpMemoryCallback(ZStack *stack, int32_t dataPerLine, void (*printFunction)(void *value))
{
    ZStack_dumpMemoryCallback(stack, dataPerLine, printFunction);
}
