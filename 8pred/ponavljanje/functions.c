#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Vanjski if filtrira: samo mjerenja iz lipnja (6), srpnja (7) ili kolovoza (8).
 * Unutarnji if traži maksimum među filtriranim:
 *   NULL == rekordna → prvi ljetni zapis postaje rekord
 *   temperatura > rekordna->temperatura → pronašli smo viši rekord
 *
 * Vraćamo pokazivač na element unutar polja temperature[] —
 * sigurno jer polje živi u main() i ne nestaje nakon povratka.
 * Vraćamo NULL ako nijedan zapis nije iz ljetnih mjeseci.
 */
mjerenje_t *rekordnaTemperatura(mjerenje_t temperature[], int n)
{
    mjerenje_t *rekordna = NULL;

    for (int i = 0; i < n; i++)
    {
        if (temperature[i].mjesec >= 6 && temperature[i].mjesec <= 8)
        {
            if (NULL == rekordna || temperature[i].temperatura > rekordna->temperatura)
            {
                rekordna = &temperature[i];
            }
        }
    }

    return rekordna;
}

/*
 * fwrite(&temperatura, sizeof(mjerenje_t), 1, fp) zapisuje strukturu kao
 * sirove bajtove — točno onako kako leži u memoriji.
 *
 * Parametri fwrite(adresa, velicina_elementa, broj_elemenata, fp):
 *   &temperatura       — adresa podatka koji zapisujemo
 *   sizeof(mjerenje_t) — veličina jednog zapisa u bajtovima
 *   1                  — zapisujemo 1 zapis
 *   fileTemperature    — ciljna datoteka
 *
 * Funkcija čita mjerenja sa stdin i odmah zapisuje svako u datoteku —
 * ne mora ih sve držati u memoriji odjednom.
 * %s u scanf čita jednu riječ (grad bez razmaka).
 */
void zapisiTemperature(FILE *fileTemperature, int n)
{
    for (int i = 0; i < n; i++)
    {
        mjerenje_t temperatura;
        scanf("%s %d %f", temperatura.grad,
              &temperatura.mjesec,
              &temperatura.temperatura);
        fwrite(&temperatura, sizeof(mjerenje_t), 1, fileTemperature);
    }
}
