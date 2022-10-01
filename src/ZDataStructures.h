#ifndef Z_DATA_STRUCTURES_H_INCLUDED
#define Z_DATA_STRUCTURES_H_INCLUDED

/**
 * \file      ZDataStructures.h
 * \author    Zahkthar
 * \brief     Déclare les structures et les fonctions de la lib.
 */

#include <stdio.h> // printf
#include <stdlib.h> // malloc, free
#include <stdint.h> // int32_t
#include <string.h> // strnlen

/*
 * Singly Linked List
 */

/**
 * \brief     La structure qui contient la liste
 * \details   Contient un pointeur vers la tête de la liste
 */
typedef struct ZSinglyLinkedList {
    struct ZSinglyLinkedListNode *head;
} ZSinglyLinkedList;

/**
 * \brief     La structure qui contient un élement de la liste
 * \details   Contient un pointeur générique vers la donnée, et un pointeur vers l'élement suivant de la liste
 */
typedef struct ZSinglyLinkedListNode {
    void *data;
    struct ZSinglyLinkedListNode *next;
} ZSinglyLinkedListNode;

// Allocation and free

/**
 * \brief     Initialise la liste
 * \details   Met à NULL le pointeur vers la tête pour avoir une liste vide
 * 
 * \return    Un pointeur vers une liste vide de type \e ZSinglyLinkedList dont la valeur de la tête est à NULL
 */
ZSinglyLinkedList *ZSinglyLinkedList_create();

/**
 * \brief     Libère la mémoire allouée par la liste
 * \details   Libère tous les pointeurs de donnée et les élements de type \e ZSinglyLinkedListNode
 * 
 * \param     list   Un pointeur vers la liste
 */
void ZSinglyLinkedList_free(ZSinglyLinkedList *list);

// Generic ZSinglyLinkedList functions

/**
 * \brief     Ajoute un élement au début de la liste
 * \details   Crée un nouvel élement de type \e ZSinglyLinkedListNode dont le pointeur next pointera vers l'ancienne tête.
 *            Remplace l'ancienne tête par le nouvel élement
 * 
 * \param     list   Un pointeur vers la liste
 * \param     data   Un pointeur vers la donnée à ajouter
 */
void ZSinglyLinkedList_pushFront(ZSinglyLinkedList *list, void* data);

/**
 * \brief     Ajoute un élement à la fin de la liste
 * \details   Crée un nouvel élement de type \e ZSinglyLinkedListNode dont le pointeur next pointe vers NULL.
 *            Le dernier élement de la liste pointera vers le nouvel élement.
 * 
 * \param     list   Un pointeur vers la liste
 * \param     data   Un pointeur vers la donnée à ajouter
 */
void ZSinglyLinkedList_pushBack(ZSinglyLinkedList *list, void* data);

/**
 * \brief     Supprime un élement de la liste à une position passée en paramètre
 * 
 * \param     list         Un pointeur vers la liste
 * \param     position     La position de l'élement à supprimer
 */
void ZSinglyLinkedList_delete(ZSinglyLinkedList *list, size_t position);

/**
 * \brief     Supprime le premier élement de la liste
 * 
 * \param     list         Un pointeur vers la liste
 */
void ZSinglyLinkedList_deleteFront(ZSinglyLinkedList *list);

/**
 * \brief     Supprime le dernier élement de la liste
 * 
 * \param     list         Un pointeur vers la liste
 */
void ZSinglyLinkedList_deleteBack(ZSinglyLinkedList *list);

/**
 * \brief     Renvoie un élement de la liste à une position passée en paramètre
 * 
 * \param     list         Un pointeur vers la liste
 * \param     position     La position de l'élement à retourner
 * 
 * \return    Un \e void* étant la donnée à la position \e position de la liste.
 */
void *ZSinglyLinkedList_showValue(ZSinglyLinkedList *list, size_t position);

/**
 * \brief     Renvoie le premier élement de la liste
 * 
 * \param     list         Un pointeur vers la liste
 * 
 * \return    Un \e void* étant la donnée au début de la liste.
 */
void *ZSinglyLinkedList_showValueFront(ZSinglyLinkedList *list);

/**
 * \brief     Renvoie le dernier élement de la liste
 * 
 * \param     list         Un pointeur vers la liste
 * 
 * \return    Un \e void* étant la donnée à la fin de la liste.
 */
void *ZSinglyLinkedList_showValueBack(ZSinglyLinkedList *list);

// Search functions

/**
 * \brief     Recherche une donnée dans la liste selon un type spécifié par le format
 * 
 * \param     list          Un pointeur vers la liste
 * \param     data          Un pointeur contenant la donnée à chercher
 * \param     format        Le format pour comparer correctement les données : \n
 *                          - "p" -> pointeur (utiliser ZSinglyLinkedList_dumpMemoryPtr) \n
 *                          - "d" -> int32_t \n
 *                          - "u" -> uint32_t \n
 *                          - "o" -> octal \n
 *                          - "x" -> hexadécimal \n
 *                          - "c" -> char \n
 *                          - "s" -> char* \n
 *                          - "f" -> float \n
 *                          - "lf" -> double \n
 */
void ZSinglyLinkedList_linearSearch(ZSinglyLinkedList *list, void* data, char *format);

// Sort functions

/**
 * \brief     Trie la liste à l'aide d'un tri à bulle 
 * 
 * \param     list          Un pointeur vers la liste
 */
void ZSinglyLinkedList_BubbleSort(ZSinglyLinkedList *list);

// Debug singly linked list functions

/**
 * \brief     Affiche les données de la liste sous formes de pointeur
 * \details   A la même fonction que ZSinglyLinkedList_dumpMemoryFormat 
 *            mais avec un format par défaut qui est "p" pour afficher les données sous formes de pointeurs.
 * 
 * \param     list          Un pointeur vers la liste
 * \param     dataPerLine   Le nombre de données à afficher par ligne
 */
void ZSinglyLinkedList_dumpMemoryPtr(ZSinglyLinkedList *list, int32_t dataPerLine);

/**
 * \brief     Affiche les données de la liste selon une forme définie par un format
 * \details   Permet d'afficher un nombre de données par ligne de la liste dans un certain format 
 * 
 * \param     list          Un pointeur vers la liste
 * \param     dataPerLine   Le nombre de données à afficher par ligne
 * \param     format        Le format pour afficher correctement les données : \n
 *                          - "p" -> pointeur (utiliser ZSinglyLinkedList_dumpMemoryPtr) \n
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

/*
 * Circular Linked List
 */

/*
 * Doubly Linked List
 */

/*
 * Circular Doubly Linked List
 */

/*
 * Stack
 */

/*
 * Queue
 */

#endif // Z_DATA_STRUCTURES_H_INCLUDED