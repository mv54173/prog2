#include <stdio.h>
/*
 * Uključujemo "functions.h" koji sadrži:
 *   - typedef struct Destinacija  (definicija strukture)
 *   - prototipe svih funkcija
 */
#include "functions.h"

int main(void)
{
    int n;
    float budzet;

    scanf("%d", &n);
    getchar(); /* konzumira '\n' iza scanf-a, inače bi prvi fgets pokupio praznu liniju */

    /*
     * VLA — polje čija veličina ovisi o n koji se čita u runtime.
     * Alocira se na stogu (stack). Tip Destinacija dolazi iz functions.h.
     */
    Destinacija destinacije[n];

    unesiDestinacije(destinacije, n);

    /*
     * Budžet se čita nakon destinacija.
     */
    scanf("%f", &budzet);

    /*
     * pronadiNajboljuDestinaciju vraća Destinacija * — ili adresu najbolje
     * destinacije unutar budžeta, ili NULL ako nijedna ne odgovara.
     *
     * Provjeravamo povratnu vrijednost pokazivačkih funkcija
     * prije dereferenciranja — dereferenciranje NULL-a je nedefinrano ponašanje
     * i tipično uzrokuje grešku (Segmentation fault).
     */
    Destinacija *najbolja = pronadiNajboljuDestinaciju(destinacije, n, budzet);

    printf("REZULTATI:\n");
    if (najbolja == NULL)
    {
        printf("Nema destinacije unutar budzeta.\n");
    }
    else
    {
        ispisiDestinaciju(najbolja);
    }

    return 0;
}
