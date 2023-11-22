#include <stdint.h>
#include <stdbool.h>

#include <criterion/criterion.h>

#include "ZStack.h"

void *cloneFunction(void *value)
{
    int32_t *clone = malloc(sizeof(int32_t));
    *clone = *(int32_t *)value;
    return clone;
}

void freeFunction(void *value)
{
    free(value);
}

bool equalsFunction(void *valueA, void *valueB)
{
    return *(int32_t *)valueA == *(int32_t *)valueB;
}

Test(ZStack, create)
{
    ZStack *stack = ZStack_create(&cloneFunction, &freeFunction);

    cr_expect(stack != NULL, "array must not be NULL");
    cr_expect(stack->nbElements == 0, "stack->nbElements must be 0");
    cr_expect(stack->cloneFunction != NULL, "stack->cloneFunction must not be NULL");
    cr_expect(stack->freeFunction != NULL, "stack->freeFunction must not be NULL");

    // Libération
    ZStack_free(stack);
}

Test(ZStack, clear)
{
    ZStack *stack = ZStack_create(&cloneFunction, &freeFunction);

    // Insertion
    for (int32_t i = 0; i < 10; ++i)
    {
        int32_t *newValue = malloc(sizeof(int32_t));
        *newValue = i;
        ZStack_push(stack, newValue);
    }

    ZStack_clear(stack);

    cr_expect(ZStack_getSize(stack) == 0, "Element number is not 0 after a clear");

    // Libération
    ZStack_free(stack);
}

Test(ZStack, push)
{
    ZStack *stack = ZStack_create(&cloneFunction, &freeFunction);

    // Insertion
    for (int32_t i = 0; i < 10; ++i)
    {
        int32_t *newValue = malloc(sizeof(int32_t));
        *newValue = i;
        ZStack_push(stack, newValue);
    }

    for (int32_t i = 0; i < 10; ++i)
    {
        int32_t *newValue = malloc(sizeof(int32_t));
        *newValue = i;
        cr_expect(equalsFunction(ZStack_peekPosition(stack, i), newValue) == true, "The values are not correctly pushed");
        free(newValue);
    }

    // Libération
    ZStack_free(stack);
}

Test(ZStack, pop)
{
    ZStack *stack = ZStack_create(&cloneFunction, &freeFunction);

    // Insertion
    for (int32_t i = 0; i < 10; ++i)
    {
        int32_t *newValue = malloc(sizeof(int32_t));
        *newValue = i;
        ZStack_push(stack, newValue);
    }

    for (int32_t i = 9; i >= 0; --i)
    {
        int32_t *newValue = malloc(sizeof(int32_t));
        *newValue = i;
        int32_t *popped = ZStack_pop(stack);

        cr_expect(equalsFunction(popped, newValue) == true, "The values are not correctly popped");
        free(newValue);
    }

    // Libération
    ZStack_free(stack);
}

Test(ZStack, peek)
{
    ZStack *stack = ZStack_create(&cloneFunction, &freeFunction);

    // Insertion
    for (int32_t i = 0; i < 10; ++i)
    {
        int32_t *newValue = malloc(sizeof(int32_t));
        *newValue = i;
        ZStack_push(stack, newValue);
        cr_expect(ZStack_peek(stack) == newValue, "The peeked value is not the right one");
    }

    // Libération
    ZStack_free(stack);
}

Test(ZStack, peekPosition)
{
    ZStack *stack = ZStack_create(&cloneFunction, &freeFunction);

    // Insertion
    for (int32_t i = 0; i < 10; ++i)
    {
        int32_t *newValue = malloc(sizeof(int32_t));
        *newValue = i;
        ZStack_push(stack, newValue);
    }

    for (int32_t i = 0; i < 10; ++i)
    {
        int32_t *newValue = malloc(sizeof(int32_t));
        *newValue = i;
        int32_t *peeked = ZStack_peekPosition(stack, i);

        cr_expect(equalsFunction(peeked, newValue), "The peeked value is not the right one");
        free(newValue);
    }

    // Libération
    ZStack_free(stack);
}

Test(ZStack, cloneStack)
{
    ZStack *firstStack = ZStack_create(&cloneFunction, &freeFunction);

    // Insertion
    for (int32_t i = 0; i < 10; ++i)
    {
        int32_t *newValue = malloc(sizeof(int32_t));
        *newValue = i;
        ZStack_push(firstStack, newValue);
    }

    ZStack *secondStack = ZStack_cloneStack(firstStack);

    for (int32_t i = 0; i < 10; ++i)
    {
        cr_expect(equalsFunction(ZStack_peekPosition(firstStack, i), ZStack_peekPosition(secondStack, i)), "The peeked value is not the right one");
    }

    // Libération
    ZStack_free(firstStack);
}

Test(ZStack, pushStack)
{
    ZStack *stackA = ZStack_create(&cloneFunction, &freeFunction);

    // Insertion
    for (int32_t i = 0; i < 10; ++i)
    {
        int32_t *newValue = malloc(sizeof(int32_t));
        *newValue = i;
        ZStack_push(stackA, newValue);
    }

    ZStack *stackB = ZStack_create(&cloneFunction, &freeFunction);

    for (int32_t i = 10; i < 20; ++i)
    {
        int32_t *newValue = malloc(sizeof(int32_t));
        *newValue = i;
        ZStack_push(stackB, newValue);
    }

    ZStack_pushStack(stackA, stackB, false);

    for (int32_t i = 0; i < 20; ++i)
    {
        int32_t *newValue = malloc(sizeof(int32_t));
        *newValue = i;
        cr_expect(equalsFunction(ZStack_peekPosition(stackA, i), newValue), "The peeked value is not the right one");
        free(newValue);
    }

    cr_expect(ZStack_getSize(stackB) == 0, "The size is not 0 after clear");

    // Libération
    ZStack_free(stackA);
    ZStack_free(stackB);
}

Test(ZStack, reverseStack)
{
    ZStack *stack = ZStack_create(&cloneFunction, &freeFunction);

    // Insertion
    for (int32_t i = 0; i < 10; ++i)
    {
        int32_t *newValue = malloc(sizeof(int32_t));
        *newValue = i;
        ZStack_push(stack, newValue);
    }

    ZStack_reverseStack(stack);

    for (int32_t i = 9; i >= 0; --i)
    {
        int32_t *newValue = malloc(sizeof(int32_t));
        *newValue = i;
        cr_expect(equalsFunction(ZStack_peekPosition(stack, 9 - i), newValue) == true, "The peeked value is not the right one");
        free(newValue);
    }

    // Libération
    ZStack_free(stack);
}

Test(ZStack, searchFirstOccurence)
{
    ZStack *stack = ZStack_create(&cloneFunction, &freeFunction);

    // Insertion
    for (int32_t i = 0; i < 10; ++i)
    {
        int32_t *newValue = malloc(sizeof(int32_t));
        *newValue = i;
        ZStack_push(stack, newValue);
    }

    for (int32_t i = 0; i < 10; ++i)
    {
        int32_t *newValue = malloc(sizeof(int32_t));
        *newValue = i;
        cr_expect(ZStack_searchFirstOccurence(stack, newValue, &equalsFunction) == (size_t)i, "The position is not right");
        free(newValue);
    }

    // Libération
    ZStack_free(stack);
}

Test(ZStack, searchPositions)
{
    ZStack *stack = ZStack_create(&cloneFunction, &freeFunction);

    // Insertion
    for (int32_t i = 0; i < 10; ++i)
    {
        int32_t *newValue = malloc(sizeof(int32_t));
        *newValue = i;
        ZStack_push(stack, newValue);
    }

    int32_t *data = malloc(sizeof(int32_t));
    *data = 4;
    ZDynamicArray *dynArr = ZStack_searchPositions(stack, data, equalsFunction);
    free(data);

    cr_expect(*(int32_t *)ZDynamicArray_getDataFront(dynArr) == 4, "The searched data is not at the right place");

    // Libération
    ZStack_free(stack);
}

Test(ZStack, countOccurrences)
{
    ZStack *stack = ZStack_create(&cloneFunction, &freeFunction);

    // Insertion
    for (int32_t i = 0; i < 10; ++i)
    {
        int32_t *newValue = malloc(sizeof(int32_t));
        *newValue = 42;
        ZStack_push(stack, newValue);
    }

    int32_t *data = malloc(sizeof(int32_t));
    *data = 42;
    size_t countOf42 = ZStack_countOccurrences(stack, data, equalsFunction);
    free(data);

    cr_expect(countOf42 == 10, "The count is not right");

    // Libération
    ZStack_free(stack);
}

bool testFunctionFilter(void *value)
{
    return *(int32_t *)value == 42;
}

Test(ZStack, filter)
{
    ZStack *stack = ZStack_create(&cloneFunction, &freeFunction);

    // Insertion
    for (int32_t i = 0; i < 10; ++i)
    {
        int32_t *newValue = malloc(sizeof(int32_t));
        *newValue = 42;
        ZStack_push(stack, newValue);
    }

    for (int32_t i = 0; i < 10; ++i)
    {
        int32_t *newValue = malloc(sizeof(int32_t));
        *newValue = 12;
        ZStack_push(stack, newValue);
    }

    cr_expect(ZStack_getSize(stack) == 20, "The size of the original stack is incorrect");

    ZStack *filteredStack = ZStack_filter(stack, &testFunctionFilter);

    cr_expect(ZStack_getSize(filteredStack) == 10, "The size of the filtered stack is incorrect");

    // Libération
    ZStack_free(filteredStack);
    ZStack_free(stack);
}

Test(ZStack, isEmpty)
{
    ZStack *stack = ZStack_create(&cloneFunction, &freeFunction);

    cr_expect(ZStack_isEmpty(stack) == true, "The stack is empty");

    // Insertion
    for (int32_t i = 0; i < 10; ++i)
    {
        int32_t *newValue = malloc(sizeof(int32_t));
        *newValue = i;
        ZStack_push(stack, newValue);
    }

    cr_expect(ZStack_isEmpty(stack) == false, "The stack is not empty");

    ZStack_clear(stack);

    cr_expect(ZStack_isEmpty(stack) == true, "The stack is empty");

    // Libération
    ZStack_free(stack);
}

Test(ZStack, getSize)
{
    ZStack *stack = ZStack_create(&cloneFunction, &freeFunction);

    cr_expect(ZStack_getSize(stack) == 0, "The stack size is wrong");

    // Insertion
    for (int32_t i = 0; i < 10; ++i)
    {
        int32_t *newValue = malloc(sizeof(int32_t));
        *newValue = i;
        ZStack_push(stack, newValue);
    }

    cr_expect(ZStack_getSize(stack) == 10, "The stack size is wrong");

    // Libération
    ZStack_free(stack);
}