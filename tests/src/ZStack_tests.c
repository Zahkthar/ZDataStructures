#include <stdint.h>
#include <stdbool.h>

#include <criterion/criterion.h>

#include "ZStack.h"

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

Test(ZStack, create)
{
    // TODO
    cr_expect(1 == 2, "Tests Stack not done yet");
}