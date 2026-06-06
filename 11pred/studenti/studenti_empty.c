#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student
{
    int id;
    char *ime;
    char *prezime;
    float prosjek;
    struct student *nextNode;
} STUDENT;

STUDENT *createList(void);
STUDENT *insertNewNode(STUDENT *);
void ispisiPopis(STUDENT *);
STUDENT *deleteWholeList(STUDENT *);

/* ============================================================
 * ZADATAK: Implementirati sljedeće 4 funkcije!
 * Prototipovi su dani, a opisi u komentarima iznad svake funkcije.
 * ============================================================ */
void unosPodataka(STUDENT *);
float prosjekSvihStudenata(STUDENT *);
void deleteNode(STUDENT **, STUDENT *);
STUDENT *searchList(STUDENT *, int);

int main(void)
{
    int n;
    printf("Unesite broj studenata!\n");
    scanf("%d", &n);

    STUDENT *headNode = createList();
    if (headNode == NULL)
    {
        return 1;
    }
    for (int i = 1; i < n; i++)
    {
        headNode = insertNewNode(headNode);
    }

    printf("REZULTATI:\n");
    ispisiPopis(headNode);
    printf("Ukupan prosjek svih studenata je: %.2f\n", prosjekSvihStudenata(headNode));

    int trazeniId;
    printf("Unesite ID studenta za brisanje!\n");
    scanf("%d", &trazeniId);

    STUDENT *targetNode = searchList(headNode, trazeniId);
    if (targetNode == NULL)
    {
        printf("Student s trazenim ID-em nije pronadjen!\n");
    }
    else
    {
        deleteNode(&headNode, targetNode);
        ispisiPopis(headNode);
        printf("Ukupan prosjek svih studenata je: %.2f\n", prosjekSvihStudenata(headNode));
    }

    headNode = deleteWholeList(headNode);
    return 0;
}

STUDENT *createList(void)
{
    STUDENT *headNode = (STUDENT *)calloc(1, sizeof(STUDENT));
    if (headNode == NULL)
    {
        perror("Kreiranje");
        return NULL;
    }
    else
    {
        unosPodataka(headNode);
        headNode->nextNode = NULL;
    }
    return headNode;
}

STUDENT *insertNewNode(STUDENT *headNode)
{
    STUDENT *newHeadNode = (STUDENT *)calloc(1, sizeof(STUDENT));
    if (newHeadNode == NULL)
    {
        perror("Kreiranje");
        return headNode;
    }
    else
    {
        unosPodataka(newHeadNode);
        newHeadNode->nextNode = headNode;
    }
    return newHeadNode;
}

void ispisiPopis(STUDENT *traverseNode)
{
    while (traverseNode)
    {
        printf("ID: %d - %s %s, prosjek: %.2f\n", traverseNode->id,
               traverseNode->ime, traverseNode->prezime, traverseNode->prosjek);
        traverseNode = traverseNode->nextNode;
    }
}

STUDENT *deleteWholeList(STUDENT *traverseNode)
{
    STUDENT *deleteNode = NULL;
    while (traverseNode)
    {
        deleteNode = traverseNode;
        traverseNode = traverseNode->nextNode;
        free(deleteNode->ime);
        free(deleteNode->prezime);
        free(deleteNode);
    }
    return NULL;
}

/*
 * Učitava podatke s tipkovnice i sprema ih u već alocirani čvor "student".
 *
 * Parametar student: pokazivač na čvor čija se polja trebaju popuniti.
 *                    Čvor je već alociran - ova funkcija ga samo puni!
 *
 * Koraci koje treba implementirati:
 *   1. Učitaj student->id                        (scanf, cijeli broj)
 *   2. Učitaj ime u privremeni buffer            (scanf, string)
 *   3. Alociraj student->ime  = calloc(strlen(buffer)+1, sizeof(char))
 *      i kopiraj buffer u student->ime           (strcpy)
 *   4. Isto za student->prezime
 *   5. Učitaj student->prosjek                  (scanf, float)
 *
 * NAPOMENA: "strlen(buffer) + 1" - +1 je za završni nul-terminator '\0'!
 *           Bez njega strcpy bi pisao izvan alocirane memorije (buffer overflow).
 */
void unosPodataka(STUDENT *student)
{
    char buffer[256];
    scanf("%d", &student->id);

    scanf("%s", buffer);
    student->ime = (char *)calloc(strlen(buffer) + 1, sizeof(char));
    if (strcpy(student->ime, buffer) == NULL)
    {
        perror("Unos");
        free(student);
        exit(1);
    }

    scanf("%s", buffer);
    student->prezime = (char *)calloc(strlen(buffer) + 1, sizeof(char));
    if (strcpy(student->prezime, buffer) == NULL)
    {
        perror("Unos");
        free(student);
        exit(1);
    }

    scanf("%f", &student->prosjek);
}

/*
 * Prolazi kroz cijelu listu i izračunava aritmetičku sredinu svih prosjeka.
 *
 * Parametar head: pokazivač na prvi čvor liste.
 * Povratna vrijednost: prosječni prosjek svih studenata (float).
 *
 * Koraci koje treba implementirati:
 *   1. Inicijaliziraj akumulator "suma" i brojač "counter" na 0
 *   2. Prođi kroz cijelu listu (while petlja dok head != NULL)
 *      - suma += head->prosjek
 *      - counter++
 *      - pomakni se na sljedeći čvor: head = head->nextNode
 *   3. Vrati suma / counter
 *
 * OPREZ: Dijeljenje s nulom ako je lista prazna (counter == 0)!
 *        U ovom zadatku pretpostavljamo da lista nikad nije prazna.
 */
float prosjekSvihStudenata(STUDENT *head)
{
    float suma = 0;
    int counter = 0;

    while (head)
    {
        suma += head->prosjek;
        counter++;
        head = head->nextNode;
    }

    return suma / counter;
}

/*
 * Briše točno određeni čvor iz liste i oslobađa svu njegovu memoriju.
 *
 * Parametar head: DVOSTRUKI pokazivač - jer ako brišemo PRVI čvor,
 *                 moramo promijeniti samu varijablu "headNode" u main-u.
 *                 Poziv: deleteNode(&headNode, target);
 * Parametar target: pokazivač na čvor koji treba obrisati.
 *
 * Koraci koje treba implementirati:
 *   1. Provjeri je li target NULL - ako jest, ispiši poruku i vrati se
 *   2. Je li target == *head? (brišemo PRVI čvor)
 *      DA:  *head = (*head)->nextNode   (pomakni head na sljedeći)
 *      NE:  Traži prethodnika traverseNode čiji je nextNode == target,
 *           pa postavi traverse->nextNode = target->nextNode
 *   3. Oslobodi dinamički alocirana polja čvora: free(target->ime), free(target->prezime)
 *   4. Oslobodi sam čvor: free(target)
 *
 * Vizualno (brisanje [B]):
 *   Prije:  [A|next->B] -> [B|next->C] -> [C|NULL]
 *   Poslije: [A|next->C] -> [C|NULL]      (B je freed)
 *
 * VAŽNO: Kod STUDENTA ima dinamički alocirane stringove (ime, prezime).
 *        Moramo ih osloboditi POSEBNO prije free(target), inače memory leak!
 */
void deleteNode(STUDENT **head, STUDENT *target)
{
    if (NULL == target)
    {
        printf("Target je NULL!");
        return;
    }

    if (*head == target)
    {
        *head = (*head)->nextNode;
    }
    else
    {
        STUDENT *traverse = *head;

        while (traverse->nextNode)
        {
            if (traverse->nextNode == target)
            {
                traverse->nextNode = target->nextNode;
                break;
            }
            traverse = traverse->nextNode;
        }
    }
    free(target->ime);
    free(target->prezime);
    free(target);
}

/*
 * Prolazi listom i vraća pokazivač na čvor čiji je "id" jednak traženom.
 *
 * Parametar head: pokazivač na prvi čvor liste.
 * Parametar id: ID studenta kojeg tražimo.
 * Povratna vrijednost: pokazivač na pronađeni čvor, ili NULL ako nije nađen.
 *
 * Koraci koje treba implementirati:
 *   1. Petlja dok head != NULL:
 *      - ako head->id == id → vrati head odmah (return head)
 *      - pomakni se na sljedeći: head = head->nextNode   ← NE ZABORAVITI!
 *   2. Ako smo prošli cijelu listu bez nalaza → vrati NULL
 *
 * !!! ČESTA GREŠKA: Zaboraviti "head = head->nextNode" unutar petlje !!!
 *     Tada petlja nikad ne napreduje → beskonačna petlja → program se zamrzne.
 */
STUDENT *searchList(STUDENT *head, int id)
{
    while (head)
    {
        if (head->id == id)
        {
            return head;
        }
        head = head->nextNode; /* BEZ OVOG RETKA: beskonačna petlja! */
    }
    return NULL;
}
