/*
 * #include "functions.h" — navodnici znače: traži datoteku RELATIVNO
 * od trenutnog direktorija (vlastite datoteke projekta).
 * #include <stdio.h>     — kutne zagrade znače: traži u sistemskim
 * direktorijima prevoditelja (standardne biblioteke).
 */
#include <stdio.h>
#include <string.h>
#include "functions.h"

/*
 * fgets čita cijelu liniju uključujući razmake — omogućuje višerječne nazive.
 * fgets uključuje '\n' na kraju, pa ga ručno zamjenjujemo s '\0'.
 * strlen(s) - 1 je indeks tog '\n'.
 *
 * REDOSLJED UNOSA po destinaciji (svako polje u posebnom retku):
 *   1. naziv  (fgets)
 *   2. drzava (fgets)
 *   3. cijena (scanf "%f" + getchar)
 *   4. ocjena (scanf "%f" + getchar)
 */
void unesiDestinacije(Destinacija *destinacije, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        fgets(destinacije[i].naziv, 50, stdin);
        destinacije[i].naziv[strlen(destinacije[i].naziv) - 1] = '\0';

        fgets(destinacije[i].drzava, 50, stdin);
        destinacije[i].drzava[strlen(destinacije[i].drzava) - 1] = '\0';

        scanf("%f", &destinacije[i].cijena);
        getchar();

        scanf("%f", &destinacije[i].ocjena);
        getchar();
    }
}

/*
 * Funkcija prima budzet kao parametar. Inicijaliziramo pokazivač na NULL — posebna vrijednost koja znači
 * "pokazivač ne pokazuje ni na što valjano".
 *
 * Dvostruki if — vanjski filtrira, unutarnji traži maksimum:
 *   1. cijena <= budzet  — destinacija je unutar budžeta
 *   2. najbolja == NULL || ocjena > najbolja->ocjena — ažuriraj ako je bolja
 *
 * Nema casta jer su cijena i ocjena već float — usporedba float vrijednosti
 * je direktna, bez rizika od cjelobrojnog dijeljenja.
 */
Destinacija *pronadiNajboljuDestinaciju(Destinacija *destinacije, int n, float budzet)
{
    Destinacija *najbolja = NULL;
    int i;
    for (i = 0; i < n; i++)
    {
        if (destinacije[i].cijena <= budzet)
        {
            if (najbolja == NULL || destinacije[i].ocjena > najbolja->ocjena)
            {
                najbolja = &destinacije[i];
            }
        }
    }
    return najbolja;
}

/*
 * Funkcija prima Destinacija * (pokazivač) — pristupamo članovima s ->.
 * %.2f ispisuje float na 2 decimalna mjesta.
 */
void ispisiDestinaciju(Destinacija *d)
{
    printf("%s %s %.2f %.2f\n", d->naziv, d->drzava, d->cijena, d->ocjena);
}
