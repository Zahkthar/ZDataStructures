#ifndef ZDS_DYNAMIC_ARRAY_H_INCLUDED
#define ZDS_DYNAMIC_ARRAY_H_INCLUDED

/**
 * \file      ZDynamicArray.h
 * \author    Zahkthar
 * \brief     Déclare les structures et les fonctions du module ZDynamicArray.
 */

#include <stdlib.h> // size_t

/*
 * Dynamic Array
 */
typedef struct ZDynamicArray {
    // Attributs
    void **data;
    size_t capacity;
    size_t nbElements;

    // Functions
    void *(*cloneFunction)(void *data);
    void (*freeFunction)(void *data);
} ZDynamicArray;

/*
 * Allocation, free and clear
 */

/**
 * \brief     Initialise le tableau
 * \details   Crée un tableau d'une capacité de 16 éléments
 * 
 * \param cloneFunction  Un pointeur vers la fonction de clonage d'un élément
 * \param freeFunction   Un pointeur vers la fonction de libération d'un élément
 * 
 * \return    Un pointeur vers un tableau dynamique de type \e ZDynamicArray
 */
ZDynamicArray *ZDynamicArray_create(void* (*cloneFunction)(void *data), void (*freeFunction)(void *data));

/**
 * \brief     Libère toute la mémoire allouée par le tableau
 * 
 * \param dynArr  Le pointeur vers le tableau à libérer
 */
void ZDynamicArray_free(ZDynamicArray *dynArr);

/**
 * \brief     Vide le tableau et libère ses éléments
 * 
 * \param dynArr  Le pointeur vers le tableau à vider
 */
void ZDynamicArray_clear(ZDynamicArray *dynArr);

/**
 * \brief     Modifie la quantité de mémoire allouée pour le tableau
 * 
 * \param dynArr  Le pointeur vers le tableau à redimentionner
 */
void ZDynamicArray_resize(ZDynamicArray *dynArr, size_t newSize);

/*
 * Generic ZSinglyLinkedList functions
 */


/*
 * Processing functions
 */


/*
 * Search functions
 */


/*
 * Sort functions
 */


/*
 * Debug DynamicArray functions
 */


#endif // ZDS_DYNAMIC_ARRAY_H_INCLUDED