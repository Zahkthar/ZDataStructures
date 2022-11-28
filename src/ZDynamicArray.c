#include "ZDynamicArray.h"

/*
 * Allocation, free and clear
 */
ZDynamicArray *ZDynamicArray_create(void* (*cloneFunction)(void *data), void (*freeFunction)(void *data))
{
    ZDynamicArray *newArray = malloc(sizeof(ZDynamicArray));

    newArray->capacity = 16;
    newArray->nbElements = 0;
    newArray->data = malloc(newArray->capacity * sizeof(void*));

    newArray->cloneFunction = cloneFunction;
    newArray->freeFunction = freeFunction;

    return newArray;
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

    if(dynArr->capacity != 16)
    {
        ZDynamicArray_resize(dynArr, 16);
    }
}

void ZDynamicArray_resize(ZDynamicArray *dynArr, size_t newSize)
{
    dynArr->capacity = newSize;
    dynArr->data = realloc(dynArr->data, dynArr->capacity * sizeof(void*));
}

bool ZDynamicArray_isEmpty(ZDynamicArray *dynArr)
{
    return dynArr->nbElements == 0;
}

size_t ZDynamicArray_getLength(ZDynamicArray *dynArr)
{
    return dynArr->nbElements;
}

void ZDynamicArray_dumpMemoryFormat(ZDynamicArray *dynArr, int32_t dataPerLine, char *format)
{
    size_t length = ZDynamicArray_getLength(dynArr);
    for(size_t i = 0; i < length; ++i)
    {
        switch (format[0])
        {
            case 'p':
                printf("%p ", dynArr->data[i]);
                break;
            case 'd':
                printf("%d ", *(int32_t*)dynArr->data[i]);
                break;
            case 'u':
                printf("%u ", *(uint32_t*)dynArr->data[i]);
                break;
            case 'o':
                printf("%o ", *(int32_t*)dynArr->data[i]);
                break;
            case 'x':
                printf("%x ", *(int32_t*)dynArr->data[i]);
                break;
            case 'c':
                printf("%c ", *(char*)dynArr->data[i]);
                break;
            case 's':
                printf("%s ", *(char**)dynArr->data[i]);
                break;
            case 'f':
                printf("%f ", *(float*)dynArr->data[i]);
                break;
            case 'l':
                if(format[1] == 'f' && strnlen(format, 3) == 2)
                {
                    printf("%lf ", *(double*)dynArr->data[i]);
                }
                break;

            default:
                return;
        }

        if(dataPerLine != 0)
        {
            if((i + 1) % dataPerLine == 0 || i == length - 1)
            {
                printf("\n");
            }
        }
    }
}

void ZDynamicArray_dumpMemoryCallback(ZDynamicArray *dynArr, int32_t dataPerLine, void (*printFunction)(void *value))
{
    size_t length = ZDynamicArray_getLength(dynArr);
    for(size_t i = 0; i < length; ++i)
    {
        printFunction(dynArr->data[i]);

        if(dataPerLine != 0)
        {
            if((i + 1) % dataPerLine == 0 || i == length - 1)
            {
                printf("\n");
            }
        }
    }
}