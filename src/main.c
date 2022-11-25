#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "ZDataStructures.h"

int main(void)
{
    ZDynamicArray *array = ZDynamicArray_create();

    
    ZDynamicArray_free(array);
    return 0;
}