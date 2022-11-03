#include "ZSinglyLinkedList.h"

/*
 * Singly Linked List
 */

// Allocation and free
ZSinglyLinkedList *ZSinglyLinkedList_create() {
    ZSinglyLinkedList *newList = malloc(sizeof(ZSinglyLinkedList));
    newList->head = NULL;
    newList->length = 0;
    return newList;
}

void ZSinglyLinkedList_free(ZSinglyLinkedList *list) {
    for (size_t i = 0; i < list->length; ++i) {
        ZSinglyLinkedList_deleteFront(list);
    }
    free(list);
}

// Generic ZSinglyLinkedList functions
void ZSinglyLinkedList_insert(ZSinglyLinkedList *list, size_t position, void *data) {
    // Gestion des cas spéciaux
    if(position > list->length) { return; }

    // Insertion en début de liste
    if(position == 0) {
        ZSinglyLinkedListNode *newNode = malloc(sizeof(ZSinglyLinkedListNode));
        newNode->next = list->head;
        newNode->data = data;
        list->head = newNode;

    // Insertion en fin de liste
    } else if(position == list->length) {
        ZSinglyLinkedListNode *currentNode = list->head;

        while (currentNode->next != NULL) {
            currentNode = currentNode->next;
        }

        ZSinglyLinkedListNode *newNode = malloc(sizeof(ZSinglyLinkedListNode));
        currentNode->next = newNode;
        newNode->data = data;
        newNode->next = NULL;

    // Insertion dans la liste
    } else {
        ZSinglyLinkedListNode *currentNode = list->head;

        for(size_t i = 0; i < position - 1; ++i) {
            currentNode = currentNode->next;
        }

        ZSinglyLinkedListNode *newNode = malloc(sizeof(ZSinglyLinkedListNode));
        newNode->data = data;
        newNode->next = currentNode->next;
        currentNode->next = newNode;
    }

    list->length += 1;
}

void ZSinglyLinkedList_insertFront(ZSinglyLinkedList *list, void *data) {
    ZSinglyLinkedList_insert(list, 0, data);
}

void ZSinglyLinkedList_insertBack(ZSinglyLinkedList *list, void *data) {
    ZSinglyLinkedList_insert(list, list->length, data);
}

void ZSinglyLinkedList_delete(ZSinglyLinkedList *list, size_t position) {
    ZSinglyLinkedListNode *currentNode = list->head;

    // Gestion des cas spéciaux
    if(position >= list->length) { return; }
    
    // Le premier élément de la liste
    if(position == 0) {
        if(list->head != NULL) {
            list->head = list->head->next;
            free(currentNode->data);
            free(currentNode);
        }

    // Le dernier élément de la liste
    } else if(position == list->length - 1) {
        while(currentNode->next->next != NULL) {
            currentNode = currentNode->next;
        }

        free(currentNode->next->data);
        free(currentNode->next);
        currentNode->next = NULL;

    // Dans la liste
    } else {
        for(size_t i = 0; i < position - 1; ++i) {
            currentNode = currentNode->next;
        }

        ZSinglyLinkedListNode *del = currentNode->next;
        currentNode->next = currentNode->next->next;
        free(del->data);
        free(del);
    }
    
    list->length -= 1;
}

void ZSinglyLinkedList_deleteFront(ZSinglyLinkedList *list) {
    ZSinglyLinkedList_delete(list, 0);
}

void ZSinglyLinkedList_deleteBack(ZSinglyLinkedList *list) {
    ZSinglyLinkedList_delete(list, list->length - 1);
}

void *ZSinglyLinkedList_getData(ZSinglyLinkedList *list, size_t position) {
    ZSinglyLinkedListNode *currentNode = list->head;

    // Gestion des cas spéciaux
    if(position == 0) { return currentNode->data; }
    if(position >= list->length) { return NULL; }

    for(size_t i = 0; i < position; ++i) {
        currentNode = currentNode->next;
    }

    return currentNode->data;
}

void *ZSinglyLinkedList_getDataFront(ZSinglyLinkedList *list) {
    return ZSinglyLinkedList_getData(list, 0);
}

void *ZSinglyLinkedList_getDataBack(ZSinglyLinkedList *list) {
    return ZSinglyLinkedList_getData(list, list->length - 1);
}

ZSinglyLinkedListNode *ZSinglyLinkedList_getNode(ZSinglyLinkedList *list, size_t position) {
    // Gestion des cas spéciaux
    if(position == 0) { return list->head; }
    if(position >= list->length) { return NULL; }

    ZSinglyLinkedListNode *currentNode = list->head;
    for(size_t i = 0; i < position; ++i) {
        currentNode = currentNode->next;
    }
    return currentNode;
}

ZSinglyLinkedListNode *ZSinglyLinkedList_getNodeFront(ZSinglyLinkedList *list) {
    return ZSinglyLinkedList_getNode(list, 0);
}

ZSinglyLinkedListNode *ZSinglyLinkedList_getNodeBack(ZSinglyLinkedList *list) {
    return ZSinglyLinkedList_getNode(list, list->length);
}

void ZSinglyLinkedList_swapData(ZSinglyLinkedList *list, size_t positionA, size_t positionB) {
    // Gestion des cas spéciaux
    if(positionA >= list->length || positionB >= list->length) { return; }
    if(positionA == positionB) { return; }

    size_t nearestPosition = (positionA < positionB) ? positionA : positionB;
    size_t delta = (nearestPosition == positionA) ? (positionB - positionA) : (positionA - positionB);

    ZSinglyLinkedListNode *currentNode = list->head;

    for(size_t i = 0; i < nearestPosition; ++i) {
        currentNode = currentNode->next;
    }

    ZSinglyLinkedListNode *nearestNode = currentNode;

    for(size_t i = 0; i < delta; ++i) {
        currentNode = currentNode->next;
    }

    void *tmpData = nearestNode->data;
    nearestNode->data = currentNode->data;
    currentNode->data = tmpData;
}

void ZSinglyLinkedList_appendTwoLists(ZSinglyLinkedList *listA, ZSinglyLinkedList *listB) {
    ZSinglyLinkedListNode *currentNode = listA->head;

    while (currentNode->next != NULL) {
        currentNode = currentNode->next;
    }

    currentNode->next = listB->head;
    listA->length += listB->length;

    listB->head = NULL;
    listB->length = 0;
}

void ZSinglyLinkedList_reverseList(ZSinglyLinkedList *list) {
    // Gestion des cas spéciaux
    if(list->length == 0) { return; }

    ZSinglyLinkedListNode *previousNode = NULL;
    ZSinglyLinkedListNode *currentNode = list->head;
    ZSinglyLinkedListNode *nextNode;
 
    while (currentNode != NULL) {
        nextNode = currentNode->next;
        currentNode->next = previousNode;
        previousNode = currentNode;
        currentNode = nextNode;
    }

    list->head = previousNode;
}

// Search functions
size_t ZSinglyLinkedList_linearSearchFirstOccurence(ZSinglyLinkedList *list, void *data, bool (*compareFunction)(void *valueA, void *valueB)) {
    ZSinglyLinkedListNode *currentNode = list->head;

    for(size_t i = 0; i < list->length; ++i) {
        if(compareFunction(data, currentNode->data)) { return i; }
        currentNode = currentNode->next;
    }

    return -1;
}

ZSinglyLinkedList *ZSinglyLinkedList_linearSearchPositions(ZSinglyLinkedList *list, void *data, bool (*compareFunction)(void *valueA, void *valueB)) {
    ZSinglyLinkedListNode *currentNode = list->head;

    ZSinglyLinkedList *positions = ZSinglyLinkedList_create();

    for(size_t i = 0; i < list->length; ++i) {
        if(compareFunction(data, currentNode->data)) {
            size_t *currentPosition = malloc(sizeof(size_t)); *currentPosition = i;
            ZSinglyLinkedList_insertBack(positions, currentPosition);
        }
        currentNode = currentNode->next;
    }

    return positions;
}

size_t ZSinglyLinkedList_countOccurrences(ZSinglyLinkedList *list, void *data, bool (*compareFunction)(void *valueA, void *valueB)) {
    ZSinglyLinkedListNode *currentNode = list->head;

    size_t occurences = 0;

    for(size_t i = 0; i < list->length; ++i) {
        if(compareFunction(data, currentNode->data)) { occurences++; }
        currentNode = currentNode->next;
    }

    return occurences;
}

// Sort functions
void ZSinglyLinkedList_BubbleSort(ZSinglyLinkedList *list, bool (*compareFunction)(void *valueA, void *valueB)) {
    ZSinglyLinkedListNode *lastNodeToCheck = NULL;

    // Si la liste est vide, on s'arrête
    if(list->length == 0) { return; }
    
    // Commencement du tri
    while(true) {
        bool isSorted = true;
        ZSinglyLinkedListNode *currentNode = list->head;
        
        // On parcours la liste du début à la fin
        while(currentNode->next != lastNodeToCheck) {
            // Si currentData > nextData
            if(compareFunction(currentNode->data, currentNode->next->data)) {
                // On swap les data
                void *tmpData = currentNode->data;
                currentNode->data = currentNode->next->data;
                currentNode->next->data = tmpData;
                
                isSorted = false; // La liste n'est pas trié
            }
            currentNode = currentNode->next;
        }

        // La valeur la plus grande a forcément été poussée tout à la fin de la liste, ce qui réduit la liste à parcourir
        lastNodeToCheck = currentNode;
        // Si la liste est déjà triée, ne pas faire toutes les passes restantes
        if(isSorted == true) {
            break;
        }
    }
}

// Debug singly linked list functions
bool ZSinglyLinkedList_isEmpty(ZSinglyLinkedList *list) {
    return (list->length == 0);
}

size_t ZSinglyLinkedList_getLength(ZSinglyLinkedList *list) {
    return list->length;
}

void ZSinglyLinkedList_dumpMemoryFormat(ZSinglyLinkedList *list, int32_t dataPerLine, char *format) {
    ZSinglyLinkedListNode *currentNode = list->head;
    size_t currentPosition = 0;

    while(currentNode != NULL) {
        switch (format[0]) {
            case 'p': printf("%p ", currentNode->data); break;
            case 'd': printf("%d ", *(int32_t*)currentNode->data); break;
            case 'u': printf("%u ", *(uint32_t*)currentNode->data); break;
            case 'o': printf("%o ", *(int32_t*)currentNode->data); break;
            case 'x': printf("%x ", *(int32_t*)currentNode->data); break;
            case 'c': printf("%c ", *(char*)currentNode->data); break;
            case 's': printf("%s ", *(char**)currentNode->data); break;
            case 'f': printf("%f ", *(float*)currentNode->data); break;
            case 'l': if(format[1] == 'f' && strnlen(format, 3) == 2) { printf("%lf ", *(double*)currentNode->data); } break;

            default: return;
        }

        if((currentPosition + 1) % dataPerLine == 0 || currentNode->next == NULL) { printf("\n"); }
        
        currentPosition++;
        currentNode = currentNode->next;
    }
}

void ZSinglyLinkedList_dumpMemoryCallback(ZSinglyLinkedList *list, int32_t dataPerLine, void (*printFunction)(void *value)) {
    ZSinglyLinkedListNode *currentNode = list->head;
    size_t currentPosition = 0;
    
    while(currentNode != NULL) {
        printFunction(currentNode->data);

        if((currentPosition + 1) % dataPerLine == 0 || currentNode->next == NULL) { printf("\n"); }
        
        currentPosition++;
        currentNode = currentNode->next;
    }
}