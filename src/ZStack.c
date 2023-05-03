#include "ZStack.h"


/*
 * Allocation, free and clear
 */
ZStack *ZStack_create(void* (*cloneFunction)(void *data), void (*freeFunction)(void *data))
{
    // TODO
    return NULL;
}

void ZStack_free(ZStack *stack)
{
    // TODO
}

void ZStack_clear(ZStack *stack)
{
    // TODO
}

/*
 * Generic ZStack functions
 */
void ZStack_push(ZStack *stack, void *data)
{
    // TODO
}

void *ZStack_pop(ZStack *stack)
{
    // TODO
    return NULL;
}

void *ZStack_peek(ZStack *stack)
{
    // TODO
    return NULL;
}

void *ZStack_peekPosition(ZStack *stack, size_t position)
{
    // TODO
    return NULL;
}

/*
 * Processing functions
 */
void ZStack_pushStack(ZStack *stackA, ZStack *stackB, bool freeArrayB)
{
    // TODO
}

ZStack *ZStack_reverseStack(ZStack *stack)
{
    // TODO
    return NULL;
}

/*
 * Search functions
 */
size_t ZStack_searchFirstOccurence(ZStack *stack, void *data, bool (*testFunction)(void *valueA, void *valueB))
{
    // TODO
    return 0;
}

ZDynamicArray *ZStack_searchPositions(ZStack *stack, void *data, bool (*testFunction)(void *valueA, void *valueB))
{
    // TODO
    return NULL;
}

size_t ZStack_countOccurrences(ZStack *stack, void *data, bool (*testFunction)(void *valueA, void *valueB))
{
    // TODO
    return 0;
}

ZDynamicArray *ZStack_filter(ZStack *stack, bool (*testFunction)(void *value))
{
    // TODO
    return NULL;
}

/*
 * Debug DynamicArray functions
 */
bool ZStack_isEmpty(ZStack *stack)
{
    // TODO
    return false;
}

size_t ZStack_getSize(ZStack *stack)
{
    // TODO
    return 0;
}

void ZStack_dumpMemoryFormat(ZStack *stack, int32_t dataPerLine, char *format)
{
    // TODO
}

void ZStack_dumpMemoryCallback(ZStack *stack, int32_t dataPerLine, void (*printFunction)(void *value))
{
    // TODO
}
