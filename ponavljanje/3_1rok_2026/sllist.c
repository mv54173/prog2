/* ==========================================================================
   FUNKCIJE KOJE JE POTREBNO IMPLEMENTIRATI U DATOTECI "sllist.c"
   ========================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include "sll_data_type.h"
#include "sllist.h"

/**
 * Funkcija: inputNodeData
 * -----------------------
 * Učitava cjelobrojnu vrijednost s tipkovnice i sprema je u podatak
 * 'number' unutar proslijeđenog čvora.
 * * node: pokazivač na čvor u koji se sprema pročitana vrijednost.
 * * Vraća: 1 ako je učitavanje uspješno, odnosno 0 ako nije (npr. greška
 * pri korištenju funkcije scanf).
 * Primjer: if(scanf("%d", &m) != 1) return 0;
 */
int inputNodeData(SLLNODE *node)
{
    if (NULL == node)
    {
        return 0;
    }

    if (scanf("%d", &node->number) != 1)
    {
        return 0;
    }

    return 1;
}

/**
 * Funkcija: createSLList
 * ----------------------
 * Dinamički alocira memoriju za prvi čvor jednostruko povezanog popisa,
 * postavlja njegov pokazivač 'nextNode' na NULL te poziva funkciju
 * inputNodeData za unos vrijednosti.
 * * Vraća: Pokazivač na novokreirani čvor. Ako alokacija ne uspije ili
 * učitavanje podatka propadne, treba osloboditi memoriju i vratiti NULL.
 */
SLLNODE *createSLList(void)
{
    SLLNODE *headNode = (SLLNODE *)calloc(1, sizeof(SLLNODE));
    if (headNode == NULL)
    {
        perror("Kreiranje");
        return NULL;
    }
    else
    {
        if (inputNodeData(headNode) == 0)
        {
            free(headNode);
            return NULL;
        }
        headNode->nextNode = NULL;
    }
    return headNode;
}

/**
 * Funkcija: insertNewNodeSLList
 * -----------------------------
 * Alocira memoriju za novi čvor, poziva funkciju inputNodeData te
 * dodaje taj novi čvor NA POČETAK popisa (novi čvor postaje nova glava
 * popisa i pokazuje na staru glavu).
 * * headNode: pokazivač na trenutnu glavu (prvi element) popisa.
 * * Vraća: Pokazivač na novu glavu popisa. Ako alokacija ili unos ne uspiju,
 * vraća originalni pokazivač 'headNode'.
 */
SLLNODE *insertNewNodeSLList(SLLNODE *headNode)
{
    SLLNODE *newHeadNode = (SLLNODE *)calloc(1, sizeof(SLLNODE));
    if (newHeadNode == NULL)
    {
        perror("Kreiranje");
        return headNode;
    }
    else
    {
        if (inputNodeData(newHeadNode) == 0)
        {
            free(newHeadNode);
            return headNode;
        }
        newHeadNode->nextNode = headNode;
    }
    return newHeadNode;
}

/**
 * Funkcija: traverseSLList
 * ------------------------
 * Prolazi kroz cijelu listu i ispisuje podatak 'number' iz svakog čvora.
 * Elementi moraju biti odvojeni jednim razmakom, a nakon ispisa cijele
 * popisa potrebno je ispisati znak za novi red (\n).
 * * traverseNode: pokazivač na glavu popisa od koje započinje ispis.
 * * Vraća: 0 (ili broj ispisanih elemenata, ovisno o internoj konvenciji).
 */
int traverseSLList(SLLNODE *traverseNode)
{
    int counter = 0;
    if (traverseNode == NULL)
    {
        return 0;
    }
    else
    {
        while (traverseNode)
        {
            counter++;
            printf(" %d", traverseNode->number);
            traverseNode = traverseNode->nextNode;
        }
        printf("\n");
    }
    return counter;
}

/**
 * Funkcija: searchSLList
 * ----------------------
 * Prolazi kroz listu i traži čvor koji sadrži vrijednost 'criteria'.
 * * traverseNode: pokazivač na glavu popisa.
 * criteria: vrijednost koja se traži u popisu.
 * * Vraća: Pokazivač na pronađeni čvor, ili NULL ako element ne postoji.
 */
SLLNODE *searchSLList(SLLNODE *traverseNode, int criteria)
{
    if (traverseNode == NULL)
    {
        return NULL;
    }
    else
    {
        while (traverseNode)
        {
            if (traverseNode->number == criteria)
            {
                return traverseNode;
            }
            traverseNode = traverseNode->nextNode;
        }
    }
    return NULL;
}

/**
 * Funkcija: deleteNodeSLList
 * --------------------------
 * Briše proslijeđeni čvor ('targetNode') iz jednostruko povezanog popisa i
 * oslobađa njegovu memoriju. Potrebno je ispravno povezati prethodni i
 * idući čvor. Posebnu pažnju treba obratiti na slučaj kada se briše prvi
 * element u popisu (zato se glava popisa šalje kao dvostruki pokazivač).
 * * headNode: dvostruki pokazivač na glavu popisa.
 * targetNode: pokazivač na čvor koji je potrebno obrisati.
 * * Vraća: Ništa (void).
 */
void deleteNodeSLList(SLLNODE **headNode, SLLNODE *targetNode)
{
    if (*headNode == targetNode)
    {
        *headNode = (*headNode)->nextNode;
        free(targetNode);
    }
    else
    {
        SLLNODE *traverseNode = *headNode;
        while (traverseNode->nextNode)
        {
            if (traverseNode->nextNode == targetNode)
            {
                traverseNode->nextNode = targetNode->nextNode;
                free(targetNode);
                break;
            }
            traverseNode = traverseNode->nextNode;
        }
    }
}
/**
 * Funkcija: deleteWholeSLList
 * ---------------------------
 * Prolazi kroz cijelu listu i redom oslobađa memoriju svakog pojedinog
 * čvora dok popis ne postane prazan.
 * * traverseNode: pokazivač na glavu popisa.
 * * Vraća: NULL (kao pokazatelj da je popis sada potpuno prazna).
 */
SLLNODE *deleteWholeSLList(SLLNODE *traverseNode)
{
    SLLNODE *deleteNode = NULL;
    while (traverseNode)
    {
        deleteNode = traverseNode;
        traverseNode = traverseNode->nextNode;
        free(deleteNode);
    }
    return NULL;
}