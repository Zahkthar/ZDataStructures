#include "ZSinglyLinkedList.h"

/*
 * Singly Linked List
 */

/*
 * Allocation, free and clear
 */
ZSinglyLinkedList *ZSinglyLinkedList_create(void* (*cloneFunction)(void *data), void (*freeFunction)(void *data))
{
    if(cloneFunction == NULL || freeFunction == NULL)
    {
        return NULL;
    }

    ZSinglyLinkedList *newList = malloc(sizeof(ZSinglyLinkedList));

    if(newList == NULL)
    {
        return NULL;
    }

    newList->head = NULL;
    newList->tail = NULL;

    newList->length = 0;

    newList->cloneFunction = cloneFunction;
    newList->freeFunction = freeFunction;

    return newList;
}

void ZSinglyLinkedList_free(ZSinglyLinkedList *list)
{
    ZSinglyLinkedList_clear(list);
    free(list);
}

void ZSinglyLinkedList_clear(ZSinglyLinkedList *list) {
    if(ZSinglyLinkedList_isCircular(list) == false)
    {
        while(list->head != NULL)
        {
            ZSinglyLinkedList_deleteFront(list);
        }
    }
    else
    {
        ZSinglyLinkedListNode *tmp;
        ZSinglyLinkedListNode *current = list->head->next;
        
        // Destruction du 2ème jusqu'au premier en parcourant la liste
        while(current != list->head)
        {
            tmp = current->next;
            list->freeFunction(current->data);
            free(current);
            current = tmp;
        }

        // Suppression de la tête
        list->freeFunction(list->head->data);
        free(list->head);
        list->head = NULL;
    }
}

/*
 * Generic ZSinglyLinkedList functions
 */
void ZSinglyLinkedList_insert(ZSinglyLinkedList *list, size_t position, void *data)
{
    // Gestion des cas spéciaux
    if(position > list->length)
    {
        return;
    }

    ZSinglyLinkedListNode *newNode = malloc(sizeof(ZSinglyLinkedListNode));
    newNode->data = data;

    if(list->length == 0) // Si la liste est vide
    {
        list->head = newNode;
        list->tail = newNode;
        newNode->next = NULL;
    }
    else
    {
        if(position == 0) // Insertion en début de liste
        {
            newNode->next = list->head;
            list->head = newNode;
        }
        else if(position == list->length) // Insertion en fin de liste
        {
            list->tail->next = newNode;
            list->tail = newNode;
            newNode->next = NULL;
        }
        else // Insertion dans la liste
        {
            ZSinglyLinkedListNode *currentNode = list->head;

            for(size_t i = 0; i < position - 1; ++i)
            {
                currentNode = currentNode->next;
            }

            newNode->next = currentNode->next;
            currentNode->next = newNode;
        }
    }

    list->length += 1;
}

void ZSinglyLinkedList_insertFront(ZSinglyLinkedList *list, void *data)
{
    ZSinglyLinkedList_insert(list, 0, data);
}

void ZSinglyLinkedList_insertBack(ZSinglyLinkedList *list, void *data)
{
    ZSinglyLinkedList_insert(list, list->length, data);
}

void ZSinglyLinkedList_delete(ZSinglyLinkedList *list, size_t position)
{
    // Gestion des cas spéciaux
    if(list->length == 0 || position >= list->length)
    {
        return;
    }

    ZSinglyLinkedListNode *currentNode = list->head;
    
    if(position == 0) // Le premier élément de la liste
    {
        if(list->head != NULL)
        {
            list->head = list->head->next;
            list->freeFunction(currentNode->data);
            free(currentNode);

            if(list->length == 1)
            {
                list->tail = NULL;
            }
        }
    }
    else // Dans la liste
    {
        for(size_t i = 0; i < position - 1; ++i)
        {
            currentNode = currentNode->next;
        }

        ZSinglyLinkedListNode *del = currentNode->next;
        currentNode->next = currentNode->next->next;
        list->freeFunction(del->data);
        free(del);

        if(position == list->length - 1)
        {
            list->tail = currentNode;
        }
    }
    
    list->length -= 1;
}

void ZSinglyLinkedList_deleteFront(ZSinglyLinkedList *list)
{
    ZSinglyLinkedList_delete(list, 0);
}

void ZSinglyLinkedList_deleteBack(ZSinglyLinkedList *list)
{
    ZSinglyLinkedList_delete(list, list->length - 1);
}

void *ZSinglyLinkedList_getData(ZSinglyLinkedList *list, size_t position)
{
    // Gestion des cas spéciaux
    if(position >= list->length)
    {
        return NULL;
    }

    if(position == list->length - 1)
    {
        return list->tail->data;
    }

    ZSinglyLinkedListNode *currentNode = list->head;
    
    for(size_t i = 0; i < position; ++i)
    {
        currentNode = currentNode->next;
    }
    
    if(currentNode != NULL)
    {
        return currentNode->data;
    }
    else // Liste vide ou position invalide
    {
        return NULL;
    }
}

void *ZSinglyLinkedList_getDataFront(ZSinglyLinkedList *list)
{
    return ZSinglyLinkedList_getData(list, 0);
}

void *ZSinglyLinkedList_getDataBack(ZSinglyLinkedList *list)
{
    return ZSinglyLinkedList_getData(list, list->length - 1);
}

void ZSinglyLinkedList_setData(ZSinglyLinkedList *list, size_t position, void* data)
{
    // Gestion des cas spéciaux
    if(position >= list->length)
    {
        return;
    }

    ZSinglyLinkedListNode *node = list->head;

    if(position == list->length - 1)
    {
        node = list->tail;
    }
    else
    {
        for(size_t i = 0; i < position; ++i)
        {
            node = node->next;
        }
    }
    
    if(node == NULL) // Liste vide ou position invalide
    {
        return;
    }

    list->freeFunction(node->data);
    node->data = data;
}

void ZSinglyLinkedList_setDataFront(ZSinglyLinkedList *list, void* data)
{
    ZSinglyLinkedList_setData(list, 0, data);
}

void ZSinglyLinkedList_setDataBack(ZSinglyLinkedList *list, void* data)
{
    ZSinglyLinkedList_setData(list, list->length - 1, data);
}

/*
 * Processing functions
 */
ZSinglyLinkedList *ZSinglyLinkedList_cloneList(ZSinglyLinkedList *list)
{
    ZSinglyLinkedList *newList = ZSinglyLinkedList_create(list->cloneFunction, list->freeFunction);

    ZSinglyLinkedListNode *currentNode = list->head;
    size_t length = ZSinglyLinkedList_getLength(list);

    for(size_t i = 0; i < length; ++i)
    {
        ZSinglyLinkedList_insertBack(newList, list->cloneFunction(currentNode->data));

        currentNode = currentNode->next;
    }

    return newList;
}

void ZSinglyLinkedList_swapData(ZSinglyLinkedList *list, size_t positionA, size_t positionB) {
    // Gestion des cas spéciaux
    if(positionA >= list->length || positionB >= list->length || positionA == positionB)
    {
        return;
    }

    size_t nearestPosition = (positionA < positionB) ? positionA : positionB;
    size_t delta = (nearestPosition == positionA) ? (positionB - positionA) : (positionA - positionB);

    ZSinglyLinkedListNode *currentNode = list->head;

    for(size_t i = 0; i < nearestPosition; ++i)
    {
        currentNode = currentNode->next;
    }

    ZSinglyLinkedListNode *nearestNode = currentNode;

    for(size_t i = 0; i < delta; ++i)
    {
        currentNode = currentNode->next;
    }

    // Swap
    void *tmpData = nearestNode->data;
    nearestNode->data = currentNode->data;
    currentNode->data = tmpData;
}

void ZSinglyLinkedList_appendTwoLists(ZSinglyLinkedList *listA, ZSinglyLinkedList *listB)
{
    listA->tail->next = listB->head;
    listA->length += listB->length;

    listB->head = NULL;
    listB->length = 0;
}

void ZSinglyLinkedList_reverseList(ZSinglyLinkedList *list)
{
    // Gestion des cas spéciaux
    if(list->length == 0)
    {
        return;
    }

    list->tail = list->head;

    ZSinglyLinkedListNode *previousNode = NULL;
    ZSinglyLinkedListNode *currentNode = list->head;
    ZSinglyLinkedListNode *nextNode;
 
    while (currentNode != NULL)
    {
        nextNode = currentNode->next;
        currentNode->next = previousNode;
        previousNode = currentNode;
        currentNode = nextNode;
    }

    list->head = previousNode;
}

/*
 * Search functions
 */
size_t ZSinglyLinkedList_searchFirstOccurence(ZSinglyLinkedList *list, void *data, bool (*testFunction)(void *valueA, void *valueB))
{
    ZSinglyLinkedListNode *currentNode = list->head;

    for(size_t i = 0; i < list->length; ++i)
    {
        if(testFunction(data, currentNode->data) == true)
        {
            return i;
        }
        
        currentNode = currentNode->next;
    }

    return UINT64_MAX;
}

ZSinglyLinkedList *ZSinglyLinkedList_searchPositions(ZSinglyLinkedList *list, void *data, bool (*testFunction)(void *valueA, void *valueB))
{
    ZSinglyLinkedList *positions = ZSinglyLinkedList_create(list->cloneFunction, list->freeFunction);

    if(positions == NULL)
    {
        return NULL;
    }

    ZSinglyLinkedListNode *currentNode = list->head;

    for(size_t i = 0; i < list->length; ++i)
    {
        if(testFunction(data, currentNode->data) == true)
        {
            size_t *currentPosition = malloc(sizeof(size_t));
            *currentPosition = i;
            ZSinglyLinkedList_insertBack(positions, currentPosition);
        }

        currentNode = currentNode->next;
    }

    return positions;
}

size_t ZSinglyLinkedList_countOccurrences(ZSinglyLinkedList *list, void *data, bool (*testFunction)(void *valueA, void *valueB))
{
    ZSinglyLinkedListNode *currentNode = list->head;

    size_t occurences = 0;

    while(currentNode != NULL)
    {
        if(testFunction(data, currentNode->data) == true)
        {
            occurences++;
        }
        currentNode = currentNode->next;
    }

    return occurences;
}

ZSinglyLinkedList *ZSinglyLinkedList_filter(ZSinglyLinkedList *list, bool (*testFunction)(void *value))
{
    ZSinglyLinkedList *returnList = ZSinglyLinkedList_create(list->cloneFunction, list->freeFunction);

    if(returnList == NULL)
    {
        return NULL;
    }

    ZSinglyLinkedListNode *currentNode = list->head;

    while(currentNode != NULL)
    {
        if(testFunction(currentNode->data) == true)
        {
            void *copyData = list->cloneFunction(currentNode->data);
            ZSinglyLinkedList_insertBack(returnList, copyData);
        }
        currentNode = currentNode->next;
    }

    return returnList;
}

/*
 * Sort functions
 */
void ZSinglyLinkedList_BubbleSort(ZSinglyLinkedList *list, bool (*compareFunction)(void *valueA, void *valueB))
{
    // Si la liste est vide, on s'arrête
    if(list->length == 0)
    {
        return;
    }
    
    ZSinglyLinkedListNode *lastNodeToCheck = NULL;
    
    // Commencement du tri
    while(true)
    {
        bool isSorted = true;
        ZSinglyLinkedListNode *currentNode = list->head;
        
        // On parcours la liste du début à la fin
        while(currentNode->next != lastNodeToCheck)
        {
            // Si currentData > nextData
            if(compareFunction(currentNode->data, currentNode->next->data) == true)
            {
                // On swap les data
                void *tmpData = currentNode->data;
                currentNode->data = currentNode->next->data;
                currentNode->next->data = tmpData;
                
                // La liste n'est pas trié
                isSorted = false;
            }
            currentNode = currentNode->next;
        }

        // La valeur la plus grande a forcément été poussée tout à la fin de la liste, ce qui réduit la liste à parcourir
        lastNodeToCheck = currentNode;
        // Si la liste est déjà triée, ne pas faire toutes les passes restantes
        if(isSorted == true)
        {
            break;
        }
    }
}

/*
 * Debug singly linked list functions
 */
bool ZSinglyLinkedList_isCircular(ZSinglyLinkedList *list)
{
    if(list == NULL || list->head == NULL)
    {
        return false;
    }

    ZSinglyLinkedListNode *slow = list->head;
    ZSinglyLinkedListNode *fast = list->head;

    while(fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;

        if(slow == fast)
        {
            return true;
        }
    }

    return false;
}

bool ZSinglyLinkedList_isEmpty(ZSinglyLinkedList *list)
{
    return (list->length == 0);
}

size_t ZSinglyLinkedList_getLength(ZSinglyLinkedList *list)
{
    return list->length;
}

bool ZSinglyLinkedList_compareWithArray(ZSinglyLinkedList *list, void **array, size_t arraySize, bool (*equalsFunction)(void *valueA, void *valueB))
{
    ZSinglyLinkedListNode *currentNode = list->head;

    for(size_t i = 0; i < arraySize; ++i)
    {
        if(equalsFunction(currentNode->data, array[i]) == false)
        {
            return false;
        }
        currentNode = currentNode->next;
    }

    return true;
}

void ZSinglyLinkedList_dumpMemoryFormat(ZSinglyLinkedList *list, int32_t dataPerLine, char *format)
{
    ZSinglyLinkedListNode *currentNode = list->head;
    size_t currentPosition = 0;

    while(currentNode != NULL)
    {
        switch (format[0])
        {
            case 'p':
                printf("%p ", currentNode->data);
                break;
            case 'd':
                printf("%d ", *(int32_t*)currentNode->data);
                break;
            case 'u':
                printf("%u ", *(uint32_t*)currentNode->data);
                break;
            case 'o':
                printf("%o ", *(int32_t*)currentNode->data);
                break;
            case 'x':
                printf("%x ", *(int32_t*)currentNode->data);
                break;
            case 'c':
                printf("%c ", *(char*)currentNode->data);
                break;
            case 's':
                printf("%s ", *(char**)currentNode->data);
                break;
            case 'f':
                printf("%f ", *(float*)currentNode->data);
                break;
            case 'l':
                if(format[1] == 'f' && strnlen(format, 3) == 2)
                {
                    printf("%lf ", *(double*)currentNode->data);
                }
                break;

            default:
                return;
        }

        if(dataPerLine != 0)
        {
            if((currentPosition + 1) % dataPerLine == 0 || currentNode->next == NULL)
            {
                printf("\n");
            }
        }
        
        currentPosition++;
        currentNode = currentNode->next;
    }
    printf("\n");
}

void ZSinglyLinkedList_dumpMemoryCallback(ZSinglyLinkedList *list, int32_t dataPerLine, void (*printFunction)(void *value))
{
    ZSinglyLinkedListNode *currentNode = list->head;
    size_t currentPosition = 0;
    
    while(currentNode != NULL)
    {
        printFunction(currentNode->data);

        if(dataPerLine != 0)
        {
            if((currentPosition + 1) % dataPerLine == 0 || currentNode->next == NULL)
            {
                printf("\n");
            }
        }
        
        currentPosition++;
        currentNode = currentNode->next;
    }
    printf("\n");
}