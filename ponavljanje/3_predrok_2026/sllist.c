/* ==========================================================================
   FUNKCIJE KOJE JE POTREBNO IMPLEMENTIRATI U DATOTECI "sllist.c"
   ========================================================================== */
#include <stdio.h>
#include <stdlib.h>
#include "sll_data_type.h"
#include "sllist.h"

/*
 * Funkcija: inputNodeData
 * -----------------------
 * Pomoćna funkcija koja sa standardnog ulaza čita podatke za jedno računalo
 * i zapisuje ih u strukturu proslijeđenog čvora (node->data).
 * * Format unosa (scanf): "%19s %19s %d %lf" (proizvođač, model, ramGB, cijena).
 * * Pokazivač 'node' mora biti osiguran od NULL vrijednosti.
 * Vraća: 1 ako su uspješno pročitana i dodijeljena sva 4 člana strukture, inače vraća 0.
 * Primjer: if(scanf("%d", &n) == 1) return 1; Ako scanf() uspješno upiše int u varijablu n funkcija vraća 1, u suprotno 0.
 */
int inputNodeData(SLLNODE *node)
{
   if (node == NULL)
   {
      return 0;
   }

   if (scanf("%19s %19s %d %lf", node->data.proizvodjac, node->data.model,
             &node->data.ramGB, &node->data.cijena) == 4)
   {
      return 1;
   }
   return 0;
}

/*
 * Funkcija: createSLList
 * ----------------------
 * Stvara i inicijalizira prvi čvor (glavu) jednostruko povezanog popisa.
 * * Koraci:
 * 1. Alocira memoriju za jedan čvor pomoću 'calloc'.
 * 2. Ako alokacija ne uspije, vraća NULL.
 * 3. Poziva funkciju 'inputNodeData' za unos podataka u alocirani čvor.
 * 4. Ako unos podataka ne uspije (ne vrati 1), oslobađa alocirani čvor i vraća NULL.
 * 5. Postavlja pokazivač 'nextNode' unutar čvora na NULL.
 * * Vraća: Pokazivač na novokreiranu glavu popisa (SLLNODE*) ili NULL u slučaju neuspjeha.
 * Primjer: if(inputNodeData(headNode) != 1) { free(headNode); return NULL;}
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
      if (inputNodeData(headNode) != 1)
      {
         free(headNode);
         return NULL;
      }
      headNode->nextNode = NULL;
   }
   return headNode;
}

/*
 * Funkcija: insertNewNodeSLList
 * -----------------------------
 * Kreira novi čvor i umeće ga NA POČETAK postojećeg popisa (postaje nova glava).
 * * Koraci:
 * 1. Alocira memoriju za novi čvor pomoću 'calloc'.
 * 2. Ako alokacija ne uspije, vraća nepromijenjenu staru glavu ('headNode').
 * 3. Poziva funkciju 'inputNodeData' za unos podataka u novi čvor.
 * 4. Ako unos ne uspije, oslobađa memoriju novog čvora i vraća staru glavu ('headNode').
 * 5. Povezuje novi čvor tako da njegov 'nextNode' pokazuje na dosadašnju glavu ('headNode').
 * * Vraća: Pokazivač na novi čvor koji sada predstavlja novu glavu popisa.
 * Primjer: if(inputNodeData(newHeadNode) != 1) { free(newHeadNode); return headNode;}
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
      if (inputNodeData(newHeadNode) != 1)
      {
         free(newHeadNode);
         return headNode;
      }
      newHeadNode->nextNode = headNode;
   }
   return newHeadNode;
}

/*
 * Funkcija: traverseSLList
 * ------------------------
 * Prolazi kroz popis od proslijeđenog čvora do kraja i ispisuje podatke.
 * * Svako računalo ispisuje se u vlastiti redak u točnom formatu:
 * "%s %s %d %.2lf\n" (proizvođač, model, ramGB, cijena).
 * Ako je popis prazan (traverseNode == NULL), funkcija ne ispisuje ništa.
 * * Vraća: Ukupan broj prebrojanih i ispisanih čvorova u popisu.
 */
int traverseSLList(SLLNODE *traverseNode)
{
   int counter = 0;
   if (traverseNode == NULL)
   {
      return -1;
   }
   else
   {
      while (traverseNode)
      {
         counter++;
         printf("%s %s %d %.2lf\n", traverseNode->data.proizvodjac,
                traverseNode->data.model,
                traverseNode->data.ramGB,
                traverseNode->data.cijena);
         traverseNode = traverseNode->nextNode;
      }
   }
   return counter;
}

/*
 * Funkcija: searchSLList
 * ----------------------
 * Pretražuje popis i traži čvor u kojem polje 'data.ramGB' odgovara traženoj vrijednosti.
 * * Pretraga kreće od čvora 'traverseNode' i ide sekvencijalno prema kraju popisa.
 * Vraća: Pokazivač na PRVI pronađeni čvor koji zadovoljava uvjet, ili NULL ako čvor ne postoji.
 */
SLLNODE *searchSLList(SLLNODE *traverseNode, int ramGB)
{
   if (traverseNode == NULL)
   {
      return NULL;
   }
   else
   {
      while (traverseNode)
      {
         if (traverseNode->data.ramGB == ramGB)
         {
            return traverseNode;
         }
         traverseNode = traverseNode->nextNode;
      }
   }
   return NULL;
}

/*
 * Funkcija: deleteNodeSLList
 * --------------------------
 * Briše točno određeni čvor ('targetNode') iz popisa i oslobađa njegovu memoriju.
 * * Funkcija prima dvostruki pokazivač na glavu popisa ('SLLNODE **headNode') kako bi,
 * u slučaju da je traženi čvor zapravo prva glava popisa, mogla preusmjeriti glavu na sljedeći čvor.
 * * Koraci:
 * 1. Provjeriti jesu li pokazivači (ili sam popis) NULL (NULL-safe provjera).
 * 2. Ako je 'targetNode' prva glava popisa, pomaknuti glavu na '(*headNode)->nextNode' i osloboditi 'targetNode'.
 * 3. U suprotnom, proći kroz popis, pronaći čvor koji se nalazi NEPOSREDNO PRIJE 'targetNode'-a,
 * preusmjeriti njegov 'nextNode' na 'targetNode->nextNode' i napraviti 'free(targetNode)'.
 */
void deleteNodeSLList(SLLNODE **headNode, SLLNODE *targetNode)
{
   if (NULL == headNode || NULL == targetNode || NULL == *headNode)
   {
      return;
   }

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
/*
 * Funkcija: deleteWholeSLList
 * ---------------------------
 * ITERATIVNO prolazi kroz cijeli popis i oslobađa memoriju ('free') svakog pojedinog čvora.
 * * Pazite na redoslijed: prije oslobađanja trenutnog čvora, morate pohraniti pokazivač na
 * sljedeći čvor kako ne biste izgubili vezu s ostatkom popisa.
 * * Vraća: Uvijek vraća NULL (kako bi se glava popisa u glavnom programu mogla postaviti na NULL).
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