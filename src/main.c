#include <stdio.h>
#include <stdlib.h>
#include "ZDataStructures.h"

int main(void)
{
    ZStack* stack = ZStack_createEmptyStack(5);

    ZStack_push(stack, 12);
    ZStack_push(stack, 14);
    ZStack_pop(stack, NULL);

    ZStack_freeStack(&stack);

    return 0;
}