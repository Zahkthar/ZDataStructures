#include "ZDataStructures.h"

/*
 * STACK
 */
ZStack* ZStack_createEmptyStack() {
    return NULL;
}

void ZStack_freeStack(ZStack **pp_stack) {
    if(pp_stack != NULL &&  *pp_stack != NULL) {
        while (*pp_stack != NULL) {
            ZStack_pop(pp_stack);
        }
    }
}

void ZStack_push(ZStack **pp_stack, int32_t data) {
    if(pp_stack != NULL) {
        ZStack *p_currentElement = *pp_stack;
        ZStack *p_nextElement = NULL;

        p_nextElement = malloc(sizeof(*p_nextElement));
        if(p_nextElement != NULL) {
            p_nextElement->data = data;
            p_nextElement->next = NULL;
            p_nextElement->prev = p_currentElement;
            
            if(p_currentElement != NULL) {
                p_currentElement->next = p_nextElement;
            }

            *pp_stack = p_nextElement;
        } else {
            fprintf(stderr, "Insufficient memory");
            exit(EXIT_FAILURE);
        }
    }
}

int32_t ZStack_pop(ZStack **pp_stack) {
    int32_t ret = INT32_MAX;

    if(pp_stack != NULL && *pp_stack != NULL) {
        ZStack *p_currentElement = *pp_stack;
        ZStack *p_previousElement = p_currentElement->prev;

        if(p_previousElement != NULL) { p_previousElement->next = NULL; }
        ret = p_currentElement->data;

        free(p_currentElement);
        p_currentElement = NULL;

        *pp_stack = p_previousElement;
    }

    return ret;
}

int32_t ZStack_peek(ZStack **pp_stack) {
    if(pp_stack != NULL && *pp_stack != NULL) { return (*pp_stack)->data; } else { return INT32_MAX; }
}

int ZStack_isEmpty(ZStack **pp_stack) {
    return (pp_stack != NULL && *pp_stack == NULL);
}

// Queue
// Linked List