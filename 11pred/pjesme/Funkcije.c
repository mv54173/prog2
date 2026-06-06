#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Funkcije.h"

void inputSongData(PJESMA *s)
{
    char buffer[256];

    scanf(" %255[^\n]", buffer);
    s->naslov = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
    if (s->naslov == NULL)
    {
        perror("malloc");
        exit(1);
    }
    strcpy(s->naslov, buffer);

    scanf(" %255[^\n]", buffer);
    s->izvodjac = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
    if (s->izvodjac == NULL)
    {
        perror("malloc");
        exit(1);
    }
    strcpy(s->izvodjac, buffer);

    scanf("%d", &s->trajanje_s);
    scanf("%f", &s->ocjena);
}

/*
 * Briše čvor target iz liste i oslobađa svu njegovu memoriju.
 *
 * Prima **head jer ako brišemo glavu liste, moramo ažurirati sam pokazivač
 * na glavu koji se nalazi u pozivatelju (main ili obrisiPjesmePoOcjeni).
 *
 * Dva slučaja:
 *   1. target je glava  → nova glava postaje target->nextNode
 *   2. target je drugdje → prolazimo do prethodnika i preskačemo target
 */
void deleteNodeSLList(NODE **head, NODE *target)
{
    if (NULL == target)
    {
        return;
    }

    if (*head == target)
    {
        *head = target->nextNode;
    }
    else
    {
        /* Tražimo prethodnika da ga povežemo s target->nextNode */
        NODE *prev = *head;
        while (prev->nextNode != target)
        {
            prev = prev->nextNode;
        }
        prev->nextNode = target->nextNode;
    }

    free(target->song.naslov);
    free(target->song.izvodjac);
    free(target);
}

/*
 * Prolazi kroz cijelu listu i briše sve čvorove čija je ocjena >= minOcjena.
 *
 * Ključna stvar: traverse se pomaka PRIJE brisanja (traverse = traverse->nextNode),
 * jer nakon deleteNodeSLList pokazivač toDelete više nije validan.
 */
void obrisiPjesmePoOcjeni(NODE **head, float minOcjena)
{
    NODE *traverse = *head;

    while (traverse)
    {
        if (traverse->song.ocjena >= minOcjena)
        {
            NODE *toDelete = traverse;
            traverse = traverse->nextNode; /* Pomak prije brisanja! */
            deleteNodeSLList(head, toDelete);
        }
        else
        {
            traverse = traverse->nextNode;
        }
    }
}

// ============= DANO U PROJEKTU (NE MIJENJATI) =============

float averageRating(NODE *head)
{
    int count = 0;
    float suma = 0.0f;
    while (head)
    {
        suma += head->song.ocjena;
        count++;
        head = head->nextNode;
    }
    return count > 0 ? suma / count : 0.0f;
}

NODE *createSLList(void)
{
    NODE *head = (NODE *)calloc(1, sizeof(NODE));
    if (!head)
    {
        perror("Kreiranje");
        return NULL;
    }
    inputSongData(&head->song);
    head->nextNode = NULL;
    return head;
}

NODE *insertNewNodeSLList(NODE *head)
{
    NODE *newNode = (NODE *)calloc(1, sizeof(NODE));
    if (!newNode)
    {
        perror("Kreiranje");
        return head;
    }
    inputSongData(&newNode->song);
    newNode->nextNode = head;
    return newNode;
}

void traverseSLList(NODE *node)
{
    if (!node)
    {
        printf("(prazna lista)\n");
        return;
    }
    while (node)
    {
        printf("Naslov: %s, Izvodjac: %s, Trajanje: %d s, Ocjena: %.2f\n",
               node->song.naslov, node->song.izvodjac,
               node->song.trajanje_s, node->song.ocjena);
        node = node->nextNode;
    }
}

NODE *deleteWholeSLList(NODE *head)
{
    NODE *tmp = NULL;
    while (head)
    {
        tmp = head;
        head = head->nextNode;
        free(tmp->song.naslov);
        free(tmp->song.izvodjac);
        free(tmp);
    }
    return NULL;
}
