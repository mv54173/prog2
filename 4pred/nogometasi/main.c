#include <stdio.h>
/*
 * Uključujemo "functions.h" koji sadrži:
 *   - typedef struct Igrac  (definicija strukture)
 *   - prototipe svih funkcija (unesiIgrace, pronadiNajboljegIgraca, ispisiIgraca)
 *
 * main.c ne treba znati kako su funkcije implementirane — to je u functions.c.
 * Prevodilac prevodi main.c i functions.c odvojeno, a linker ih spaja:
 *   gcc main.c functions.c -o nogometasi
 */
#include "functions.h"

int main(void)
{
    int n;

    scanf("%d", &n);
    getchar();

    /*
     * VLA — polje čija veličina ovisi o n koji se čita u runtime.
     * Alocira se na stogu (stack). Tip Igrac dolazi iz functions.h.
     */
    Igrac igraci[n];

    unesiIgrace(igraci, n);

    /*
     * pronadiNajboljegIgraca vraća Igrac * — ili adresu najboljeg igrača
     * unutar polja igraci[], ili NULL ako nitko ne zadovoljava uvjet.
     *
     * Provjeravamo povratnu vrijednost pokazivačkih funkcija
     * prije dereferenciranja — dereferenciranje NULL-a je nedefinrano ponašanje
     * i tipično uzrokuje grešku (Segmentation fault).
     */
    Igrac *najbolji = pronadiNajboljegIgraca(igraci, n);

    printf("REZULTATI:\n");
    if (najbolji == NULL)
    {
        printf("Nema igraca s dovoljno utakmica.\n");
    }
    else
    {
        ispisiIgraca(najbolji);
    }

    return 0;
}
