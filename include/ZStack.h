#ifndef ZDS_STACK_H_INCLUDED
#define ZDS_STACK_H_INCLUDED

/**
 * \file      ZStack.h
 * \author    Zahkthar
 * \brief     Déclare les structures et les fonctions du module ZStack.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "ZDynamicArray.h"

/*
 * Dynamic Array
 */
typedef ZDynamicArray ZStack;

/*
 * Allocation, free and clear
 */

/**
 * \brief     Initialise la pile
 * \details   Crée une pile et la renvoie
 * 
 * \param cloneFunction  Un pointeur vers la fonction de clonage d'un élément
 * \param freeFunction   Un pointeur vers la fonction de libération d'un élément
 * 
 * \return    Un pointeur vers la pile de type \e ZStack ou NULL si échec
 */
ZStack *ZStack_create(void* (*cloneFunction)(void *data), void (*freeFunction)(void *data));

/**
 * \brief     Libère toute la mémoire allouée par la pile
 * 
 * \param stack  Le pointeur vers la pile à libérer
 */
void ZStack_free(ZStack *stack);

/**
 * \brief     Vide la pile et libère ses éléments
 * 
 * \param stack  Le pointeur vers la pile à vider
 */
void ZStack_clear(ZStack *stack);

/*
 * Generic ZStack functions
 */

/**
 * \brief     Ajoute un élement au dessus de la pile
 * 
 * \param     stack   Un pointeur vers la pile
 * \param     data     Le pointeur à ajouter à la pile
 */
void ZStack_push(ZStack *stack, void *data);

/**
 * \brief     Supprime l'élement au dessus de la pile et le renvoie
 * 
 * \param     stack         Un pointeur vers la pile
 * 
 * \return    Un \e void* étant la donnée supprimée dans la pile.
 */
void *ZStack_pop(ZStack *stack);

/**
 * \brief     Renvoie l'élement au dessus de la pile
 * 
 * \param     stack       Un pointeur vers la pile
 * 
 * \return    Un \e void* étant la donnée au sommet de la pile.
 */
void *ZStack_peek(ZStack *stack);

/**
 * \brief     Renvoie l'élement au dessus de la pile
 * 
 * \param     stack       Un pointeur vers la pile
 * \param     position    La position de l'élement à regarder dans la pile
 * 
 * \return    Un \e void* étant la donnée à cette position, ou NULL si la fonction échoue.
 */
void *ZStack_peekPosition(ZStack *stack, size_t position);

/*
 * Processing functions
 */

/**
 * \brief     Clone la pile et ses données passée en paramètre
 * 
 * \param     stack       Un pointeur vers la pile
 * 
 * \return    Un \e ZStack* étant la nouvelle pile contenant les données de la première ou NULL si la fonction échoue.
 */
ZStack *ZStack_cloneStack(ZStack *stack);

/**
 * \brief     Ajoute la pile B sur la pile A.
 * \details   Rend la pile B vide.
 * 
 * \param     stackA      Un pointeur vers la pile A
 * \param     stackB      Un pointeur vers la pile B
 * \param     freeStackB  true pour libérer automatiquement la liste B, false sinon
 */
void ZStack_pushStack(ZStack *stackA, ZStack *stackB, bool freeStackB);

/**
 * \brief     Renverse la pile passé en paramètre
 * 
 * \param     stack       Un pointeur vers la pile
 */
void ZStack_reverseStack(ZStack *stack);


/*
 * Search functions
 */

/**
 * \brief     Recherche une donnée dans la pile selon une fonction de comparaison donnée en paramètre
 * 
 * \param     stack         Un pointeur vers la pile
 * \param     data          Un pointeur contenant la donnée à chercher
 * \param     testFunction  Un pointeur vers la fonction de comparaison
 * 
 * \return    La position de la première occurence dans la pile pour laquelle la fonction \e testFunction renvoie true. Renvoie UINT64_MAX si aucune valeur ne renvoie true.
 */
size_t ZStack_searchFirstOccurence(ZStack *stack, void *data, bool (*testFunction)(void *valueA, void *valueB));

/**
 * \brief     Recherche une donnée dans la pile selon une fonction de comparaison donnée en paramètre et renvoie un tableau de positions
 * 
 * \param     stack         Un pointeur vers la pile
 * \param     data          Un pointeur contenant la donnée à chercher
 * \param     testFunction  Un pointeur vers la fonction de comparaison
 * 
 * \return    Un tableau de size_t contenant les positions auquelles la fonction \e testFunction a renvoyée true (ne pas oublier de la libérer après utilisation). Renvoie NULL si l'allocation a échouée.
 */
ZDynamicArray *ZStack_searchPositions(ZStack *stack, void *data, bool (*testFunction)(void *valueA, void *valueB));

/**
 * \brief     Renvoie le nombre d'occurence d'une donnée dans une pile
 * 
 * \param     stack         Un pointeur vers la pile
 * \param     data          Un pointeur contenant la donnée à chercher
 * \param     testFunction  Un pointeur vers la fonction de comparaison
 * 
 * \return    Le nombre d'élément de la pile pour lesquels la fonction \e testFunction a renvoyée true.
 */
size_t ZStack_countOccurrences(ZStack *stack, void *data, bool (*testFunction)(void *valueA, void *valueB));

/**
 * \brief     Renvoie un tableau d'élement du tableau donnée en paramètre pour lesquels la fonction de test a renvoyée true
 * 
 * \param     stack           Un pointeur vers la liste
 * \param     testFunction     Un pointeur vers la fonction de test

 * \return    Une nouvelle pile avec les élements de la pile pour lesquels testFunction() a renvoyé true (ne pas oublier de la libérer après utilisation). Renvoie NULL si l'allocation a échouée.
 */
ZStack *ZStack_filter(ZStack *stack, bool (*testFunction)(void *value));


/*
 * Debug DynamicArray functions
 */

/**
 * \brief     Renvoie true si la pile est vide, false sinon
 * 
 * \param     stack   Un pointeur vers la pile
 * 
 * \return    Un \e bool valant true si la pile est vide.
 */
bool ZStack_isEmpty(ZStack *stack);

/**
 * \brief     Renvoie le nombre d'éléments de la pile
 * 
 * \param     stack   Un pointeur vers la pile
 * 
 * \return    Un \e size_t étant le nombre d'éléments de la pile.
 */
size_t ZStack_getSize(ZStack *stack);

/**
 * \brief     Affiche les données de la pile selon une forme définie par un format
 * \details   Permet d'afficher un nombre de données par ligne ddu tableau dans un certain format
 * 
 * \param     stack        Un pointeur vers la pile
 * \param     dataPerLine  Le nombre de données à afficher par ligne, mettre 0 si l'on ne veut pas de mise à la ligne automatique
 * \param     format       Le format pour afficher correctement les données : \n
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
void ZStack_dumpMemoryFormat(ZStack *stack, int32_t dataPerLine, char *format);

/**
 * \brief     Affiche les données de la pile selon une forme définie par une fonction passée en paramètre
 * 
 * \param     stack          Un pointeur vers la pile
 * \param     dataPerLine    Le nombre de données à afficher par ligne, mettre 0 si l'on ne veut pas de mise à la ligne automatique
 * \param     printFunction  L'adresse de la fonction d'affichage
 */
void ZStack_dumpMemoryCallback(ZStack *stack, int32_t dataPerLine, void (*printFunction)(void *value));

#endif // ZDS_STACK_H_INCLUDED