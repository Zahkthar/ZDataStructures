#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "ZDataStructures.h"

void *cloneFunction(void *data)
{
    int32_t *newData = malloc(sizeof(int32_t));
    *newData = *(int32_t*)data;
    return newData;
}

void freeFunction(void *data)
{
    free(data);
}

int main(void)
{
    ZDynamicArray *array = ZDynamicArray_create(&cloneFunction, &freeFunction);
    
    

    ZDynamicArray_free(array);
    return 0;
}