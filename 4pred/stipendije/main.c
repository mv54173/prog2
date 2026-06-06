#include <stdio.h>
/*
 * Uključujemo "functions.h" koji sadrži:
 *   - typedef struct Student  (definicija strukture)
 *   - prototipe svih funkcija (unesiStudente, pronadiNajboljeg, ispisiStudenta)
 *
 * main.c ne treba znati kako su funkcije implementirane — to je u functions.c.
 * Prevodilac prevodi main.c i functions.c odvojeno, a linker ih spaja:
 *   gcc main.c functions.c -o stipendije
 */
#include "functions.h"

int main(void)
{
    int n;

    scanf("%d", &n);

    /*
     * VLA — polje čija veličina ovisi o n koji se čita u runtime.
     * Alocira se na stogu (stack). Tip Student dolazi iz functions.h.
     */
    Student studenti[n];

    unesiStudente(studenti, n);

    /*
     * pronadiNajboljeg vraća Student * — ili adresu najboljeg studenta
     * unutar polja studenti[], ili NULL ako nitko ne zadovoljava uvjet.
     *
     * Provjeravamo povratnu vrijednost pokazivačkih funkcija
     * prije dereferenciranja — dereferenciranje NULL-a je nedefinrano ponašanje
     * i tipično uzrokuje grešku (Segmentation fault).
     *
     * Konvencija usporedbe NULL == najbolji. Štiti od slučajnog = umjesto ==
     * jer NULL = najbolji je greška pri prevođenju, a najbolji = NULL bila bi tiha logička greška.
     */
    Student *najbolji = pronadiNajboljeg(studenti, n);

    printf("REZULTATI:\n");
    if (NULL == najbolji)
    {
        printf("Nijedan student ne zadovoljava uvjet.\n");
    }
    else
    {
        ispisiStudenta(najbolji);
    }

    return 0;
}
