#include <stdio.h> // printf
#include <stdlib.h> // malloc
#include <stdint.h> // int32_t
#include "ZDataStructures.h"

int main(void) {
    ZStack stack;
    ZStack_initEmptyStack(&stack, 5);

    int *a = malloc(sizeof(int)); *a = 5;
    ZStack_push(&stack, a);

    a = malloc(sizeof(int)); *a = 12;
    ZStack_push(&stack, a);

    ZStack_dumpMemory(&stack, 10);

    printf("%d\n", *((int32_t*)(ZStack_peek(&stack))));

    ZStack_freeStack(&stack);
    return 0;
}