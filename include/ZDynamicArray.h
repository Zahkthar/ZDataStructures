#ifndef ZDS_DYNAMIC_ARRAY_H_INCLUDED
#define ZDS_DYNAMIC_ARRAY_H_INCLUDED

/**
 * \file      ZDynamicArray.h
 * \author    Zahkthar
 * \brief     Déclare les structures et les fonctions du module ZDynamicArray.
 */

#include <stdlib.h> // size_t
#include <stdint.h> // int32_t
#include <stdbool.h> // bool

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
 * Generic ZDynamicArray functions
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

/**
 * \brief     Renvoie true si le tableau est vide, false sinon
 * 
 * \param     dynArr   Un pointeur vers le tableau
 * 
 * \return    Un \e bool valant true si le tableau est vide.
 */
bool ZDynamicArray_isEmpty(ZDynamicArray *dynArr);

/**
 * \brief     Renvoie le nombre d'éléments du tableau
 * 
 * \param     dynArr   Un pointeur vers le tableau
 * 
 * \return    Un \e size_t étant le nombre d'éléments du tableau.
 */
size_t ZDynamicArray_getLength(ZDynamicArray *dynArr);

/**
 * \brief     Affiche les données du tableau selon une forme définie par un format
 * \details   Permet d'afficher un nombre de données par ligne ddu tableau dans un certain format
 * 
 * \param     dynArr        Un pointeur vers le tableau
 * \param     dataPerLine   Le nombre de données à afficher par ligne, mettre 0 si l'on ne veut pas de mise à la ligne automatique
 * \param     format        Le format pour afficher correctement les données : \n
 *                          - "p" -> pointeur \n
 *                          - "d" -> int32_t \n
 *                          - "u" -> uint32_t \n
 *                          - "o" -> octal \n
 *                          - "x" -> hexadécimal \n
 *                          - "c" -> char \n
 *                          - "s" -> char* \n
 *                          - "f" -> float \n
 *                          - "lf" -> double \n
 */
void ZDynamicArray_dumpMemoryFormat(ZDynamicArray *dynArr, int32_t dataPerLine, char *format);

/**
 * \brief     Affiche les données du tableau selon une forme définie par une fonction passée en paramètre
 * 
 * \param     dynArr          Un pointeur vers le tableau
 * \param     dataPerLine     Le nombre de données à afficher par ligne, mettre 0 si l'on ne veut pas de mise à la ligne automatique
 */
void ZDynamicArray_dumpMemoryCallback(ZDynamicArray *dynArr, int32_t dataPerLine, void (*printFunction)(void *value));

#endif // ZDS_DYNAMIC_ARRAY_H_INCLUDED