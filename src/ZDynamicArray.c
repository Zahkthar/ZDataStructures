#include "ZDynamicArray.h"

/*
 * Allocation, free and clear
 */
ZDynamicArray *ZDynamicArray_create(void* (*cloneFunction)(void *data), void (*freeFunction)(void *data))
{
    if(cloneFunction == NULL || freeFunction == NULL)
    {
        return NULL;
    }

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

/*
 * Generic ZDynamicArray functions
 */
void ZDynamicArray_insert(ZDynamicArray *dynArr, size_t position, void *data)
{
    // Cas d'erreurs
    if(position > dynArr->nbElements)
    {
        return;
    }

    // Si la liste est pleine, augmenter sa taille
    if(ZDynamicArray_isFull(dynArr) == true)
    {
        ZDynamicArray_resize(dynArr, dynArr->capacity * 2);
    }

    if(position == dynArr->nbElements)
    {
        dynArr->data[position] = data;
    }
    else
    {
        memmove(dynArr->data + position + 1, dynArr->data + position, dynArr->nbElements - position - 1);
        dynArr->data[position] = data;
    }
}

void ZDynamicArray_insertFront(ZDynamicArray *dynArr, void *data)
{
    ZDynamicArray_insert(dynArr, 0, data);
}

void ZDynamicArray_insertBack(ZDynamicArray *dynArr, void *data)
{
    ZDynamicArray_insert(dynArr, dynArr->nbElements, data);
}

void ZDynamicArray_delete(ZDynamicArray *dynArr, size_t position)
{
    if(ZDynamicArray_isEmpty(dynArr) == true || position >= dynArr->nbElements)
    {
        return;
    }

    dynArr->freeFunction(dynArr->data[position]);

    if(position != dynArr->nbElements)
    {
        memmove(dynArr->data + position, dynArr->data + position + 1, dynArr->nbElements - position - 1);
    }

    dynArr->nbElements--;

    if(dynArr->capacity >= 16)
    {
        float ratio = dynArr->nbElements / dynArr->capacity;
        if(ratio <= 0.25)
        {
            ZDynamicArray_resize(dynArr, dynArr->capacity / 2);
        }
    }
}

void ZDynamicArray_deleteFront(ZDynamicArray *dynArr)
{
    ZDynamicArray_delete(dynArr, 0);
}

void ZDynamicArray_deleteBack(ZDynamicArray *dynArr)
{
    ZDynamicArray_delete(dynArr, dynArr->nbElements - 1);
}

void *ZDynamicArray_getData(ZDynamicArray *dynArr, size_t position)
{
    // Cas d'erreur
    if(position >= dynArr->nbElements)
    {
        return NULL;
    }

    return dynArr->data[position];
}

void *ZDynamicArray_getDataFront(ZDynamicArray *dynArr)
{
    return ZDynamicArray_getData(dynArr, 0);
}

void *ZDynamicArray_getDataBack(ZDynamicArray *dynArr)
{
    return ZDynamicArray_getData(dynArr, dynArr->nbElements - 1);
}

void ZDynamicArray_setData(ZDynamicArray *dynArr, size_t position, void* data)
{
    // Cas d'erreur
    if(position >= dynArr->nbElements)
    {
        return;
    }

    dynArr->freeFunction(dynArr->data[position]);
    dynArr->data[position] = data;
}

void ZDynamicArray_setDataFront(ZDynamicArray *dynArr, void* data)
{
    ZDynamicArray_setData(dynArr, 0, data);
}

void ZDynamicArray_setDataBack(ZDynamicArray *dynArr, void* data)
{
    ZDynamicArray_setData(dynArr, dynArr->nbElements - 1, data);
}

/*
 * Processing functions
 */
void ZDynamicArray_swapData(ZDynamicArray *dynArr, size_t positionA, size_t positionB)
{
    // Cas d'erreur
    if(positionA >= dynArr->nbElements || positionB >= dynArr->nbElements)
    {
        return;
    }

    void *tmp = dynArr->data[positionA];
    dynArr->data[positionA] = dynArr->data[positionB];
    dynArr->data[positionB] = tmp;
}

void ZDynamicArray_appendTwoArrays(ZDynamicArray *dynArrA, ZDynamicArray *dynArrB)
{
    // Cas d'erreur
    if(ZDynamicArray_isEmpty(dynArrA) == true || ZDynamicArray_isEmpty(dynArrB) == true)
    {
        return;
    }

    dynArrA->capacity += dynArrB->capacity;
    ZDynamicArray_resize(dynArrA, dynArrA->capacity);

    for(size_t i = 0; i < dynArrB->nbElements; ++i)
    {
        ZDynamicArray_setDataBack(dynArrA, dynArrB->data[i]);
    }

    dynArrB->capacity = 16;
    dynArrB->nbElements = 0;
    ZDynamicArray_resize(dynArrB, dynArrB->capacity);
}

void ZDynamicArray_reverseArrays(ZDynamicArray *dynArr)
{
    // Cas d'erreur
    if(ZDynamicArray_isEmpty(dynArr) == true)
    {
        return;
    }

    size_t length = ZDynamicArray_getLength(dynArr);
    for(size_t i = 0; i < length / 2; ++i)
    {
        ZDynamicArray_swapData(dynArr, i, length - i - 1);
    }
}

/*
 * Search functions
 */
size_t ZDynamicArray_searchFirstOccurence(ZDynamicArray *dynArr, void *data, bool (*testFunction)(void *valueA, void *valueB))
{
    size_t length = ZDynamicArray_getLength(dynArr);
    for(size_t i = 0; i < length; ++i)
    {
        if(testFunction(data, dynArr->data[i]) == true)
        {
            return i;
        }
    }

    return UINT64_MAX;
}

ZDynamicArray *ZDynamicArray_searchPositions(ZDynamicArray *dynArr, void *data, bool (*testFunction)(void *valueA, void *valueB))
{
    ZDynamicArray *positions = ZDynamicArray_create(dynArr->cloneFunction, dynArr->freeFunction);

    if(positions == NULL)
    {
        return NULL;
    }

    size_t length = ZDynamicArray_getLength(dynArr);
    for(size_t i = 0; i < length; ++i)
    {
        if(testFunction(data, dynArr->data[i]) == true)
        {
            size_t *currentPosition = malloc(sizeof(size_t));
            *currentPosition = i;
            ZDynamicArray_insertBack(positions, currentPosition);
        }
    }

    return positions;
}

size_t ZDynamicArray_countOccurrences(ZDynamicArray *dynArr, void *data, bool (*testFunction)(void *valueA, void *valueB))
{
    size_t occurences = 0;

    size_t length = ZDynamicArray_getLength(dynArr);
    for(size_t i = 0; i < length; ++i)
    {
        if(testFunction(data, dynArr->data[i]) == true)
        {
            occurences++;
        }
    }

    return occurences;
}

ZDynamicArray *ZDynamicArray_filter(ZDynamicArray *dynArr, bool (*testFunction)(void *value))
{
    ZDynamicArray *returnList = ZDynamicArray_create(dynArr->cloneFunction, dynArr->freeFunction);

    if(returnList == NULL)
    {
        return NULL;
    }

    size_t length = ZDynamicArray_getLength(dynArr);
    for(size_t i = 0; i < length; ++i)
    {
        if(testFunction(dynArr->data[i]) == true)
        {
            void *copyData = dynArr->cloneFunction(dynArr->data[i]);
            ZDynamicArray_insertBack(returnList, copyData);
        }
    }

    return returnList;
}

/*
 * Sort functions
 */
void ZDynamicArray_BubbleSort(ZDynamicArray *dynArr, bool (*compareFunction)(void *valueA, void *valueB))
{
    // Cas d'erreur
    if(ZDynamicArray_isEmpty(dynArr) == true)
    {
        return;
    }
    
    // Commencement du tri
    bool isArraySorted = true;

    size_t length = ZDynamicArray_getLength(dynArr);
    for(size_t i = length - 1; i > 0; --i)
    {
        isArraySorted = true;
        for(size_t j = 0; j < i; ++j)
        {
            if(compareFunction(dynArr->data[j], dynArr->data[j + 1]) == true)
            {
                ZDynamicArray_swapData(dynArr, j + 1, j);
                isArraySorted = false;
            }
        }

        if(isArraySorted == true)
        {
            break;
        }
    }
}

/*
 * Debug DynamicArray functions
 */
bool ZDynamicArray_isEmpty(ZDynamicArray *dynArr)
{
    return dynArr->nbElements == 0;
}

bool ZDynamicArray_isFull(ZDynamicArray *dynArr)
{
    return dynArr->nbElements == dynArr->capacity;
}

size_t ZDynamicArray_getLength(ZDynamicArray *dynArr)
{
    return dynArr->nbElements;
}

size_t ZDynamicArray_getCapacity(ZDynamicArray *dynArr)
{
    return dynArr->capacity;
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