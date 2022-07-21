#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ZDataStructures.h"

int main(void) {
    ZStack stack;
    ZStack_initEmptyStack(&stack, 5);

    

    ZStack_freeStack(&stack);
    return 0;
}