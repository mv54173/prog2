#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Funkcije.h"

/*
    [1.] void inputBookData(KNJIGA* book);
         – Funkcija prima pokazivač na jednu knjigu te unosi njegove podatke s tipkovnice:
           naslov, autor, godina izdanja, ocjena čitatelja
           Za tekstualne podatke potrebno je prethodno dinamički alocirati memoriju.
*/
void inputBookData(KNJIGA *book)
{
    if (NULL == book)
    {
        return;
    }

    char buffer[256];

    scanf(" %255[^\n]", buffer);
    book->naslov = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
    if (book->naslov == NULL)
    {
        return;
    }
    strcpy(book->naslov, buffer);

    scanf(" %255[^\n]", buffer);
    book->autor = (char *)calloc(strlen(buffer) + 1, sizeof(char));
    if (book->autor == NULL)
    {
        free(book->naslov);
        return;
    }
    strcpy(book->autor, buffer);

    scanf(" %d", &book->godina_izdanja);
    scanf(" %f", &book->ocjena);
}

/*
 [2.] void deleteNodeSLList(KNJIGA** head, KNJIGA* target);
         – Funkcija briše jedan zadani čvor iz liste. Ako je riječ o prvom čvoru, ažurira pokazivač na glavu liste.
           Oslobađa zauzetu memoriju za cijeli uređaj, uključujući stringove.

*/
void deleteNodeSLList(KNJIGA **head, KNJIGA *target)
{
    if (*head == target)
    {
        *head = (*head)->nextNode;
        free(target->naslov);
        free(target->autor);
        free(target);
    }
    else
    {
        KNJIGA *traverseNode = *head;
        while (traverseNode->nextNode)
        {
            if (traverseNode->nextNode == target)
            {
                traverseNode->nextNode = target->nextNode;
                free(target->naslov);
                free(target->autor);
                free(target);
                break;
            }
            traverseNode = traverseNode->nextNode;
        }
    }
}

void obrisiKnjigeStarijeOd(KNJIGA **head, int godina)
{
    KNJIGA *traverseNode = *head;
    KNJIGA *deleteNode = NULL;

    while (traverseNode)
    {
        if (traverseNode->godina_izdanja < godina)
        {
            deleteNode = traverseNode;
            traverseNode = traverseNode->nextNode;
            deleteNodeSLList(head, deleteNode);
        }
        else
        {
            traverseNode = traverseNode->nextNode;
        }
    }
}

float averageRating(KNJIGA *head)
{
    int count = 0;
    float suma = 0.0;

    while (head)
    {
        suma += head->ocjena;
        count++;
        head = head->nextNode;
    }
    return count > 0 ? suma / count : 0.0;
}

KNJIGA *createSLList(void)
{
    KNJIGA *head = (KNJIGA *)calloc(1, sizeof(KNJIGA));
    if (!head)
    {
        perror("Kreiranje");
        return NULL;
    }

    inputBookData(head);
    head->nextNode = NULL;
    return head;
}

KNJIGA *insertNewNodeSLList(KNJIGA *head)
{
    KNJIGA *newNode = (KNJIGA *)calloc(1, sizeof(KNJIGA));
    if (!newNode)
    {
        perror("Kreiranje");
        return head;
    }

    inputBookData(newNode);
    newNode->nextNode = head;
    return newNode;
}

void traverseSLList(KNJIGA *node)
{
    while (node)
    {
        printf("Naslov: %s, Autor: %s, Godina: %d, Ocjena: %.2f\n",
               node->naslov, node->autor, node->godina_izdanja, node->ocjena);
        node = node->nextNode;
    }
}

KNJIGA *deleteWholeSLList(KNJIGA *head)
{
    KNJIGA *tmp = NULL;
    while (head)
    {
        tmp = head;
        head = head->nextNode;
        free(tmp->naslov);
        free(tmp->autor);
        free(tmp);
    }
    return NULL;
}
