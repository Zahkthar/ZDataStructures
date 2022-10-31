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

void *ZSinglyLinkedList_showValue(ZSinglyLinkedList *list, size_t position) {
    ZSinglyLinkedListNode *currentNode = list->head;

    // Gestion des cas spéciaux
    if(position == 0 && currentNode != NULL) { return currentNode->data; }
    if(position >= list->length) { return NULL; }

    for(size_t i = 0; i < position; ++i) {
        currentNode = currentNode->next;
    }

    return currentNode->data;
}

void *ZSinglyLinkedList_showValueFront(ZSinglyLinkedList *list) {
    return list->head->data;
}

void *ZSinglyLinkedList_showValueBack(ZSinglyLinkedList *list) {
    return ZSinglyLinkedList_showValue(list, list->length - 1);
}

// Search functions
int ZSinglyLinkedList_linearSearch(ZSinglyLinkedList *list, void *data, bool (*compareFunction)(void *valueA, void *valueB)) {
    ZSinglyLinkedListNode *currentNode = list->head;

    for(size_t i = 0; i < list->length; ++i) {
        if(compareFunction(data, currentNode->data)) { return i; }
        currentNode = currentNode->next;
    }

    return -1;
}

// Sort functions
void ZSinglyLinkedList_BubbleSort(ZSinglyLinkedList *list, bool (*compareFunction)(void *valueA, void *valueB)) {
    ZSinglyLinkedListNode *lastCellToCheck = NULL;

    // Si la liste est vide, on s'arrête
    if(list->length == 0) { return; }
    
    // Commencement du tri
    while(true) {
        bool isSorted = true;
        ZSinglyLinkedListNode *currentCell = list->head;
        
        // On parcours la liste du début à la fin
        while(currentCell->next != lastCellToCheck) {
            // Si currentData > nextData
            if(compareFunction(currentCell->data, currentCell->next->data)) {
                // On swap les data
                void *tmpData = currentCell->data;
                currentCell->data = currentCell->next->data;
                currentCell->next->data = tmpData;
                
                isSorted = false; // La liste n'est pas trié
            }
            currentCell = currentCell->next;
        }

        // La valeur la plus grande a forcément été poussée tout à la fin de la liste, ce qui réduit la liste à parcourir
        lastCellToCheck = currentCell;
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
    
    for(size_t i = 0; i < list->length; ++i) {
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

            default: break;
        }

        if((i + 1) % dataPerLine == 0 || currentNode->next == NULL) { printf("\n"); }
        currentNode = currentNode->next;
    }
}

void ZSinglyLinkedList_dumpMemoryCallback(ZSinglyLinkedList *list, int32_t dataPerLine, void (*printFunction)(void *value)) {
    ZSinglyLinkedListNode *currentNode = list->head;
    
    for(size_t i = 0; i < list->length; ++i) {
        printFunction(currentNode->data);

        if((i + 1) % dataPerLine == 0 || currentNode->next == NULL) { printf("\n"); }
        currentNode = currentNode->next;
    }
}