#ifndef ZDS_SINGLY_LINKED_LIST_H_INCLUDED
#define ZDS_SINGLY_LINKED_LIST_H_INCLUDED

/**
 * \file      ZSinglyLinkedList.h
 * \author    Zahkthar
 * \brief     Déclare les structures et les fonctions du module ZSinglyLinkedList.
 */

#include <stdio.h> // printf
#include <stdlib.h> // malloc, free
#include <stdint.h> // int32_t, uint32_t, UINT64_MAX
#include <string.h> // strnlen
#include <stdbool.h> // bool, true, false

/*
 * Singly Linked List
 */

/**
 * \brief     La structure qui contient la liste
 * \details   Contient un pointeur vers la tête de la liste ainsi que des informations simplifiant l'usage des fonctions
 */
typedef struct ZSinglyLinkedList {
    // Attributs
    struct ZSinglyLinkedListNode *head;
    size_t length;

    // Fonctions
    void (*printFunction)(void *value);
    void* (*cloneFunction)(void *data);
    void (*freeFunction)(void *data);
} ZSinglyLinkedList;

/**
 * \brief     La structure qui contient un élement de la liste
 * \details   Contient un pointeur générique vers la donnée, et un pointeur vers l'élement suivant de la liste
 */
typedef struct ZSinglyLinkedListNode {
    void *data;
    struct ZSinglyLinkedListNode *next;
} ZSinglyLinkedListNode;

/*
 * Allocation, free and clear
 */

/**
 * \brief     Initialise la liste
 * \details   Met à NULL le pointeur vers la tête pour avoir une liste vide
 * 
 * \return    Un pointeur vers une liste vide de type \e ZSinglyLinkedList dont la valeur de la tête est à NULL
 */
ZSinglyLinkedList *ZSinglyLinkedList_create();

/**
 * \brief     Libère la mémoire allouée par la liste
 * \details   Libère tous les pointeurs de donnée et les élements de type \e ZSinglyLinkedListNode, puis libère la liste
 * 
 * \param     list            Un pointeur vers la liste
 * \param     printFunction   Un pointeur vers la fonction d'affichage
 * \param     cloneFunction   Un pointeur vers la fonction de clonage
 * \param     freeFunction    Un pointeur vers la fonction de libération
 */
void ZSinglyLinkedList_setCallbackFunctions(ZSinglyLinkedList *list, void (*printFunction)(void *value), void* (*cloneFunction)(void *data), void (*freeFunction)(void *data));

/**
 * \brief     Libère la mémoire allouée par la liste
 * \details   Libère tous les pointeurs de donnée et les élements de type \e ZSinglyLinkedListNode, puis libère la liste
 * 
 * \param     list           Un pointeur vers la liste
 */
void ZSinglyLinkedList_free(ZSinglyLinkedList *list);

/**
 * \brief     Vide la liste sans la supprimer
 * \details   Libère tous les pointeurs de donnée et les élements de type \e ZSinglyLinkedListNode
 * 
 * \param     list           Un pointeur vers la liste
 */
void ZSinglyLinkedList_clear(ZSinglyLinkedList *list);

/*
 * Generic ZSinglyLinkedList functions
 */
/**
 * \brief     Ajoute un élement dans la liste
 * \details   Crée un nouvel élement de type \e ZSinglyLinkedListNode et l'insère à la position \e position dans la liste
 * 
 * \param     list       Un pointeur vers la liste
 * \param     position   La position à laquelle insérer l'élement
 * \param     data       Le pointeur à ajouter à la liste
 */
void ZSinglyLinkedList_insert(ZSinglyLinkedList *list, size_t position, void *data);

/**
 * \brief     Ajoute un élement au début de la liste
 * \details   Crée un nouvel élement de type \e ZSinglyLinkedListNode dont le pointeur next pointera vers l'ancienne tête.
 *            Remplace l'ancienne tête par le nouvel élement
 * 
 * \param     list   Un pointeur vers la liste
 * \param     data   Le pointeur à ajouter à la liste
 */
void ZSinglyLinkedList_insertFront(ZSinglyLinkedList *list, void *data);

/**
 * \brief     Ajoute un élement à la fin de la liste
 * \details   Crée un nouvel élement de type \e ZSinglyLinkedListNode dont le pointeur next pointe vers NULL.
 *            Le dernier élement de la liste pointera vers le nouvel élement.
 * 
 * \param     list   Un pointeur vers la liste
 * \param     data   Le pointeur à ajouter à la liste
 */
void ZSinglyLinkedList_insertBack(ZSinglyLinkedList *list, void *data);

/**
 * \brief     Supprime un élement de la liste à une position passée en paramètre
 * 
 * \param     list           Un pointeur vers la liste
 * \param     position       La position de l'élement à supprimer
 */
void ZSinglyLinkedList_delete(ZSinglyLinkedList *list, size_t position);

/**
 * \brief     Supprime le premier élement de la liste
 * 
 * \param     list           Un pointeur vers la liste
 */
void ZSinglyLinkedList_deleteFront(ZSinglyLinkedList *list);

/**
 * \brief     Supprime le dernier élement de la liste
 * 
 * \param     list           Un pointeur vers la liste
 */
void ZSinglyLinkedList_deleteBack(ZSinglyLinkedList *list);

/**
 * \brief     Renvoie la cellule à la position \e position
 * 
 * \param     list         Un pointeur vers la liste
 * \param     position     La position de la cellule à récupérer
 * 
 * \return    Un \e ZSinglyLinkedListNode* étant la cellule recherchée
 */
ZSinglyLinkedListNode *ZSinglyLinkedList_getNode(ZSinglyLinkedList *list, size_t position);

/**
 * \brief     Renvoie la première cellule de la liste
 * 
 * \param     list         Un pointeur vers la liste
 * 
 * \return    Un \e ZSinglyLinkedListNode* étant la cellule recherchée ou NULL si la liste est vide
 */
ZSinglyLinkedListNode *ZSinglyLinkedList_getNodeFront(ZSinglyLinkedList *list);

/**
 * \brief     Renvoie la dernière cellule de la liste
 * 
 * \param     list         Un pointeur vers la liste
 * 
 * \return    Un \e ZSinglyLinkedListNode* étant la cellule recherchée ou NULL si la liste est vide
 */
ZSinglyLinkedListNode *ZSinglyLinkedList_getNodeBack(ZSinglyLinkedList *list);

/**
 * \brief     Renvoie un élement de la liste à une position passée en paramètre
 * 
 * \param     list         Un pointeur vers la liste
 * \param     position     La position de l'élement à retourner
 * 
 * \return    Un \e void* étant la donnée à la position \e position de la liste.
 */
void *ZSinglyLinkedList_getData(ZSinglyLinkedList *list, size_t position);

/**
 * \brief     Renvoie le premier élement de la liste
 * 
 * \param     list         Un pointeur vers la liste
 * 
 * \return    Un \e void* étant la donnée au début de la liste.
 */
void *ZSinglyLinkedList_getDataFront(ZSinglyLinkedList *list);

/**
 * \brief     Renvoie le dernier élement de la liste
 * 
 * \param     list         Un pointeur vers la liste
 * 
 * \return    Un \e void* étant la donnée à la fin de la liste.
 */
void *ZSinglyLinkedList_getDataBack(ZSinglyLinkedList *list);

/**
 * \brief     Modifie la donnée de la liste à la position passée en paramètre
 * \details   Libère l'ancienne donnée via la fonction de libération passée en paramètre
 * 
 * \param     list           Un pointeur vers la liste
 * \param     position       La position à laquelle modifier la donnée
 * \param     data           La nouvelle donnée
 */
void ZSinglyLinkedList_setData(ZSinglyLinkedList *list, size_t position, void* data);

/**
 * \brief     Modifie la donnée du premier élement de la liste
 * \details   Libère l'ancienne donnée via la fonction de libération passée en paramètre
 * 
 * \param     list           Un pointeur vers la liste
 * \param     data           La nouvelle donnée
 */
void ZSinglyLinkedList_setDataFront(ZSinglyLinkedList *list, void* data);

/**
 * \brief     Modifie la donnée du dernier élement de la liste
 * \details   Libère l'ancienne donnée via la fonction de libération passée en paramètre
 * 
 * \param     list           Un pointeur vers la liste
 * \param     data           La nouvelle donnée
 */
void ZSinglyLinkedList_setDataBack(ZSinglyLinkedList *list, void* data);

/*
 * Processing functions
 */
/**
 * \brief     Swap les data deux cellules aux positions données en paramètres
 * 
 * \param     list         Un pointeur vers la liste
 * \param     positionA    La position de la première donnée
 * \param     positionB    La position de la deuxième donnée
 */
void ZSinglyLinkedList_swapData(ZSinglyLinkedList *list, size_t positionA, size_t positionB);

/**
 * \brief     Ajoute la liste B à la fin de la liste A.
 * \details   Rend la liste B vide.
 * 
 * \param     list         Un pointeur vers la liste
 * 
 * \return    Un \e void* étant la donnée à la fin de la liste.
 */
void ZSinglyLinkedList_appendTwoLists(ZSinglyLinkedList *listA, ZSinglyLinkedList *listB);

/**
 * \brief     Renverse la liste passée en paramètre
 * 
 * \param     list         Un pointeur vers la liste
 */
void ZSinglyLinkedList_reverseList(ZSinglyLinkedList *list);

/*
 * Search functions
 */
/**
 * \brief     Recherche une donnée dans la liste selon une fonction de comparaison donnée en paramètre
 * 
 * \param     list           Un pointeur vers la liste
 * \param     data           Un pointeur contenant la donnée à chercher
 * \param     testFunction   Un pointeur vers la fonction de comparaison
 * 
 * \return    La position de la première occurence dans la liste pour laquelle la fonction \e testFunction renvoie true. Renvoie UINT64_MAX si aucune valeur ne renvoie true.
 */
size_t ZSinglyLinkedList_searchFirstOccurence(ZSinglyLinkedList *list, void *data, bool (*testFunction)(void *valueA, void *valueB));

/**
 * \brief     Recherche une donnée dans la liste selon une fonction de comparaison donnée en paramètre et renvoie un tableau de positions
 * 
 * \param     list           Un pointeur vers la liste
 * \param     data           Un pointeur contenant la donnée à chercher
 * \param     testFunction   Un pointeur vers la fonction de comparaison
 * 
 * \return    Une liste chaînée de size_t contenant les positions auquelles la fonction \e testFunction a renvoyée true (ne pas oublier de la libérer après utilisation). Renvoie NULL si l'allocation a échouée.
 */
ZSinglyLinkedList *ZSinglyLinkedList_searchPositions(ZSinglyLinkedList *list, void *data, bool (*testFunction)(void *valueA, void *valueB));

/**
 * \brief     Renvoie le nombre d'occurence d'une donnée dans la liste
 * 
 * \param     list           Un pointeur vers la liste
 * \param     data           Un pointeur contenant la donnée à chercher
 * \param     testFunction   Un pointeur vers la fonction de comparaison
 * 
 * \return    Le nombre d'élément de la liste pour lesquels la fonction \e testFunction a renvoyée true.
 */
size_t ZSinglyLinkedList_countOccurrences(ZSinglyLinkedList *list, void *data, bool (*testFunction)(void *valueA, void *valueB));

/**
 * \brief     Renvoie la liste d'élement de la liste donnée en paramètre pour lesquels la fonction de test a renvoyée true
 * 
 * \param     list             Un pointeur vers la liste
 * \param     testFunction     Un pointeur vers la fonction de test

 * \return    La liste d'élements de la liste d'origine pour lesquels testFunction() a renvoyé true (ne pas oublier de la libérer après utilisation). Renvoie NULL si l'allocation a échouée.
 */
ZSinglyLinkedList *ZSinglyLinkedList_filter(ZSinglyLinkedList *list, bool (*testFunction)(void *value));

/*
 * Sort functions
 */
/**
 * \brief     Trie la liste à l'aide d'un tri à bulle 
 * 
 * \param     list              Un pointeur vers la liste
 * \param     compareFunction   Un pointeur vers la fonction de comparaison
 * 
 */
void ZSinglyLinkedList_BubbleSort(ZSinglyLinkedList *list, bool (*compareFunction)(void *valueA, void *valueB));

/*
 * Debug singly linked list functions
 */
/**
 * \brief     Renvoie true si la liste est vide, false sinon
 * 
 * \param     list   Un pointeur vers la liste
 * 
 * \return    Un \e bool valant true si la liste est vide.
 */
bool ZSinglyLinkedList_isEmpty(ZSinglyLinkedList *list);

/**
 * \brief     Renvoie le nombre d'éléments de la liste
 * 
 * \param     list   Un pointeur vers la liste
 * 
 * \return    Un \e size_t étant le nombre d'éléments de la liste. 
 */
size_t ZSinglyLinkedList_getLength(ZSinglyLinkedList *list);

/**
 * \brief     Affiche les données de la liste selon une forme définie par un format
 * \details   Permet d'afficher un nombre de données par ligne de la liste dans un certain format
 * 
 * \param     list          Un pointeur vers la liste
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
void ZSinglyLinkedList_dumpMemoryFormat(ZSinglyLinkedList *list, int32_t dataPerLine, char *format);

/**
 * \brief     Affiche les données de la liste selon une forme définie par une fonction passée en paramètre
 * 
 * \param     list            Un pointeur vers la liste
 * \param     dataPerLine     Le nombre de données à afficher par ligne, mettre 0 si l'on ne veut pas de mise à la ligne automatique
 */
void ZSinglyLinkedList_dumpMemoryCallback(ZSinglyLinkedList *list, int32_t dataPerLine);

#endif // ZDS_SINGLY_LINKED_LIST_H_INCLUDED