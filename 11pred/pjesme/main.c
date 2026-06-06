#include <stdio.h>
#include <stdlib.h>
#include "Funkcije.h"

int main(void)
{
    int n, i;
    float prag;
    NODE *headNode = NULL;

    printf("Koliko pjesama zelis unijeti? ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Neispravan unos.\n");
        return 0;
    }

    /* createSLList alocira prvi čvor i traži unos podataka za prvu pjesmu */
    headNode = createSLList();

    /*
     * insertNewNodeSLList alocira novi čvor, traži unos i umeće ga na početak liste.
     * Zato je redoslijed ispisa obrnut od redoslijeda unosa. (n-1) jer smo prvi već upisali.
     */
    for (i = 0; i < n - 1; i++)
    {
        headNode = insertNewNodeSLList(headNode);
    }

    printf("\nSvi uneseni zapisi (SLL):\n");
    traverseSLList(headNode);
    printf("Prosjecna ocjena: %.2f\n", averageRating(headNode));

    printf("\nUnesi minimalnu ocjenu (pjesme ispod toga brisemo): ");
    if (scanf("%f", &prag) != 1)
        prag = 0.0f;

    /*
     * Brišemo sve čvorove čija je ocjena >= prag.
     * Funkcija prima **head jer može trebati promijeniti samu glavu liste.
     */
    printf("REZULTATI:\n");
    obrisiPjesmePoOcjeni(&headNode, prag);

    printf("Nakon brisanja:\n");
    traverseSLList(headNode);
    printf("Prosjecna ocjena preostalih pjesama: %.2f\n", averageRating(headNode));

    /* Oslobađamo svu preostalu memoriju — funkcija vraća NULL koji postavljamo u headNode */
    headNode = deleteWholeSLList(headNode);
    return 0;
}
