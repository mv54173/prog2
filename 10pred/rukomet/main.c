#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int dan;
    int mjesec;
    int godina;
} datum;

typedef struct
{
    char tim1[30];
    char tim2[30];
    int golovi1;
    int golovi2;
    datum nadnevak;
} rukomet;

int main(void)
{
    int n;

    /* Unos broja utakmica uz validaciju (0 < n < 100) */
    do
    {
        scanf("%d", &n);
    } while (!(n > 0 && n < 100));
    getchar(); /* Gutanje \n koji ostaje nakon scanf */

    rukomet polje[n];

    for (int i = 0; i < n; i++)
    {
        /* fgets čita cijeli redak uključujući \n, pa ga uklanjamo */
        fgets(polje[i].tim1, 30, stdin);
        polje[i].tim1[strlen(polje[i].tim1) - 1] = '\0';
        fgets(polje[i].tim2, 30, stdin);
        polje[i].tim2[strlen(polje[i].tim2) - 1] = '\0';

        scanf("%d ", &polje[i].golovi1);
        scanf("%d ", &polje[i].golovi2);

        /* Format DD.MM.GGGG. — svaka točka u formatu guta odgovarajuću točku iz ulaza */
        scanf("%d.%d.%d.", &polje[i].nadnevak.dan, &polje[i].nadnevak.mjesec, &polje[i].nadnevak.godina);
        getchar(); /* Gutanje \n iza datuma, priprema za fgets sljedeće iteracije */
    }

    FILE *fp = fopen("pobjednici.txt", "w");
    if (fp == NULL)
    {
        perror("Greska je");
        exit(1);
    }

    /* Prolazak kroz utakmice — u datoteku zapisujemo pobjednike iz prvog mjeseca */
    for (int i = 0; i < n; i++)
    {
        if (polje[i].nadnevak.mjesec == 1)
        {
            if (polje[i].golovi1 > polje[i].golovi2)
            {
                fprintf(fp, "%s ", polje[i].tim1);
            }
            else if (polje[i].golovi1 < polje[i].golovi2)
            {
                fprintf(fp, "%s ", polje[i].tim2);
            }
            else
            {
                continue; /* Neriješeno — ne zapisujemo pobjednika */
            }
        }
    }

    fclose(fp);
    return 0;
}
