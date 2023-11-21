#ifndef ZDS_DYNAMIC_ARRAY_H_INCLUDED
#define ZDS_DYNAMIC_ARRAY_H_INCLUDED

/**
 * \file      ZDynamicArray.h
 * \author    Zahkthar
 * \brief     Déclare les structures et les fonctions du module ZDynamicArray.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

/*
 * Dynamic Array
 */

/**
 * \brief     La structure qui contient le tableau dynamique
 * \details   Contient le tableau, le nombre d'éléments actuels du tableau, sa capacité actuelle ainsi que des callbacks
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

/**
 * \brief     Ajoute un élement dans le tableau à la position souhaitée
 * 
 * \param     dynArr     Un pointeur vers le tableau
 * \param     position   La position à laquelle insérer l'élement
 * \param     data       Le pointeur à ajouter au tableau
 */
void ZDynamicArray_insert(ZDynamicArray *dynArr, size_t position, void *data);

/**
 * \brief     Ajoute un élement au début de tableau
 * \details   Décale les anciennes cases
 * 
 * \param     dynArr   Un pointeur vers le tableau
 * \param     data     Le pointeur à ajouter au tableau
 */
void ZDynamicArray_insertFront(ZDynamicArray *dynArr, void *data);

/**
 * \brief     Ajoute un élement en fin de tableau
 * 
 * \param     dynArr   Un pointeur vers le tableau
 * \param     data     Le pointeur à ajouter au tableau
 */
void ZDynamicArray_insertBack(ZDynamicArray *dynArr, void *data);

/**
 * \brief     Supprime un élement du tableau à une position passée en paramètre
 * 
 * \param     dynArr         Un pointeur vers le tableau
 * \param     position       La position de l'élement à supprimer
 */
void ZDynamicArray_delete(ZDynamicArray *dynArr, size_t position);

/**
 * \brief     Supprime le premier élement du tableau
 * 
 * \param     dynArr       Un pointeur vers le tableau
 */
void ZDynamicArray_deleteFront(ZDynamicArray *dynArr);

/**
 * \brief     Supprime le dernier élement du tableau
 * 
 * \param     dynArr       Un pointeur vers le tableau
 */
void ZDynamicArray_deleteBack(ZDynamicArray *dynArr);

/**
 * \brief     Renvoie un élement du tableau à une position passée en paramètre
 * 
 * \param     dynArr       Un pointeur vers le tableau
 * \param     position     La position de l'élement à retourner
 * 
 * \return    Un \e void* étant la donnée à la position \e position du tableau.
 */
void *ZDynamicArray_getData(ZDynamicArray *dynArr, size_t position);

/**
 * \brief     Renvoie le premier élement du tableau
 * 
 * \param     dynArr       Un pointeur vers le tableau
 * 
 * \return    Un \e void* étant la donnée au début de tableau.
 */
void *ZDynamicArray_getDataFront(ZDynamicArray *dynArr);

/**
 * \brief     Renvoie le dernier élement du tableau
 * 
 * \param     dynArr       Un pointeur vers le tableau
 * 
 * \return    Un \e void* étant la donnée à la fin du tableau.
 */
void *ZDynamicArray_getDataBack(ZDynamicArray *dynArr);

/**
 * \brief     Modifie la donnée du tableau à la position passée en paramètre
 * 
 * \param     dynArr         Un pointeur vers le tableau
 * \param     position       La position à laquelle modifier la donnée
 * \param     data           La nouvelle donnée
 */
void ZDynamicArray_setData(ZDynamicArray *dynArr, size_t position, void* data);

/**
 * \brief     Modifie la donnée du premier élement du tableau
 * 
 * \param     dynArr       Un pointeur vers le tableau
 * \param     data         La nouvelle donnée
 */
void ZDynamicArray_setDataFront(ZDynamicArray *dynArr, void* data);

/**
 * \brief     Modifie la donnée du dernier élement du tableau
 * 
 * \param     dynArr       Un pointeur vers le tableau
 * \param     data         La nouvelle donnée
 */
void ZDynamicArray_setDataBack(ZDynamicArray *dynArr, void* data);

/*
 * Processing functions
 */

/**
 * \brief     Clone le tableau et ses données
 * 
 * \param     dynArr       Un pointeur vers le tableau
 * 
 * \return    Un \e ZDynamicArray* étant le nouveau tableau contenant les données du premier ou NULL si la fonction échoue.
 */
ZDynamicArray *ZDynamicArray_cloneArray(ZDynamicArray *dynArr);

/**
 * \brief     Swap les data deux cases aux positions données en paramètres
 * 
 * \param     dynArr       Un pointeur vers le tableau
 * \param     positionA    La position de la première donnée
 * \param     positionB    La position de la deuxième donnée
 */
void ZDynamicArray_swapData(ZDynamicArray *dynArr, size_t positionA, size_t positionB);

/**
 * \brief     Ajoute le tableau B derrière le tableau A.
 * \details   Rend le tableau B vide.
 * 
 * \param     dynArrA      Un pointeur vers le tableau A
 * \param     dynArrB      Un pointeur vers le tableau B
 * \param     freeArrayB   true pour libérer automatiquement la liste B, false sinon
 */
void ZDynamicArray_appendTwoArrays(ZDynamicArray *dynArrA, ZDynamicArray *dynArrB, bool freeArrayB);

/**
 * \brief     Renverse le tableau passé en paramètre
 * 
 * \param     dynArr       Un pointeur vers le tableau
 */
void ZDynamicArray_reverseArray(ZDynamicArray *dynArr);


/*
 * Search functions
 */

/**
 * \brief     Recherche une donnée dans le tableau selon une fonction de comparaison donnée en paramètre
 * 
 * \param     dynArr         Un pointeur vers le tableau
 * \param     data           Un pointeur contenant la donnée à chercher
 * \param     testFunction   Un pointeur vers la fonction de comparaison
 * 
 * \return    La position de la première occurence dans le tableau pour laquelle la fonction \e testFunction renvoie true. Renvoie UINT64_MAX si aucune valeur ne renvoie true.
 */
size_t ZDynamicArray_searchFirstOccurence(ZDynamicArray *dynArr, void *data, bool (*testFunction)(void *valueA, void *valueB));

/**
 * \brief     Recherche une donnée dans le tableau selon une fonction de comparaison donnée en paramètre et renvoie un tableau de positions
 * 
 * \param     dynArr         Un pointeur vers le tableau
 * \param     data           Un pointeur contenant la donnée à chercher
 * \param     testFunction   Un pointeur vers la fonction de comparaison
 * 
 * \return    Un tableau de size_t contenant les positions auquelles la fonction \e testFunction a renvoyée true (ne pas oublier de la libérer après utilisation). Renvoie NULL si l'allocation a échouée.
 */
ZDynamicArray *ZDynamicArray_searchPositions(ZDynamicArray *dynArr, void *data, bool (*testFunction)(void *valueA, void *valueB));

/**
 * \brief     Renvoie le nombre d'occurence d'une donnée dans un tableau
 * 
 * \param     dynArr         Un pointeur vers le tableau
 * \param     data           Un pointeur contenant la donnée à chercher
 * \param     testFunction   Un pointeur vers la fonction de comparaison
 * 
 * \return    Le nombre d'élément du tableau pour lesquels la fonction \e testFunction a renvoyée true.
 */
size_t ZDynamicArray_countOccurrences(ZDynamicArray *dynArr, void *data, bool (*testFunction)(void *valueA, void *valueB));

/**
 * \brief     Renvoie un tableau d'élement du tableau donnée en paramètre pour lesquels la fonction de test a renvoyée true
 * 
 * \param     dynArr           Un pointeur vers la liste
 * \param     testFunction     Un pointeur vers la fonction de test

 * \return    Le tableau d'élements du tableau d'origine pour lesquels testFunction() a renvoyé true (ne pas oublier de la libérer après utilisation). Renvoie NULL si l'allocation a échouée.
 */
ZDynamicArray *ZDynamicArray_filter(ZDynamicArray *dynArr, bool (*testFunction)(void *value));


/*
 * Sort functions
 */

/**
 * \brief     Trie le tableau à l'aide d'un tri à bulle 
 * 
 * \param     list              Un pointeur vers le tableau
 * \param     compareFunction   Un pointeur vers la fonction de comparaison
 * 
 */
void ZDynamicArray_BubbleSort(ZDynamicArray *dynArr, bool (*compareFunction)(void *valueA, void *valueB));

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
 * \brief     Renvoie true si le tableau est plein, false sinon
 * 
 * \param     dynArr   Un pointeur vers le tableau
 * 
 * \return    Un \e bool valant true si le tableau est plein.
 */
bool ZDynamicArray_isFull(ZDynamicArray *dynArr);

/**
 * \brief     Renvoie le nombre d'éléments du tableau
 * 
 * \param     dynArr   Un pointeur vers le tableau
 * 
 * \return    Un \e size_t étant le nombre d'éléments du tableau.
 */
size_t ZDynamicArray_getLength(ZDynamicArray *dynArr);

/**
 * \brief     Renvoie la capacité du tableau
 * 
 * \param     dynArr   Un pointeur vers le tableau
 * 
 * \return    Un \e size_t étant le nombre d'éléments que peut stocker le tableau.
 */
size_t ZDynamicArray_getCapacity(ZDynamicArray *dynArr);

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
 * \param     printFunction   L'adresse de la fonction d'affichage
 */
void ZDynamicArray_dumpMemoryCallback(ZDynamicArray *dynArr, int32_t dataPerLine, void (*printFunction)(void *value));

#endif // ZDS_DYNAMIC_ARRAY_H_INCLUDED