#include <stdio.h>
#include <stdlib.h>

/*
 * fscanf(fp, "%s %s %d %f", ime, prezime, &god, &prosjek) čita jedan redak.
 * %s čita do prvog razmaka — ovdje je ime uvijek jedna riječ, pa je ispravno.
 * Vraća broj uspješno pročitanih polja (ovdje 4) ili EOF na kraju datoteke.
 * Provjera != EOF: petlja se zaustavlja kad nestane podataka.
 *
 * U uvjetu prosjek >= 4.0f && godinaStudiranja <= 3 provjera se ako
 * student zadovoljava uvjete stipendije, ako da upiše se u datoteku.
 * fprintf(fp, format, ...) radi isto kao printf, ali piše u FILE * umjesto stdout.
 * Ovdje upisujemo samo ime i prezime — ostale podatke (godina, prosjek) ne trebamo
 * u izlaznoj datoteci, pa ih čitamo u lokalne varijable i ignoriramo.
 */
void traziStipendiste(FILE *studenti, FILE *stipendija)
{
    char ime[30];
    char prezime[30];
    int godinaStudiranja;
    float prosjek;

    // čak i bolja varijanta je jer tako osiguravamo da čitamo sve dok imamo dovoljno podataka
    // while (fscanf(studenti, "%s %s %d %f",
    //              ime, prezime, &godinaStudiranja, &prosjek) == 4)
    while (fscanf(studenti, "%s %s %d %f",
                  ime, prezime, &godinaStudiranja, &prosjek) != EOF)
    {
        if (prosjek >= 4.0f && godinaStudiranja <= 3)
        {
            fprintf(stipendija, "%s %s\n", ime, prezime);
        }
    }
}

int main(void)
{
    FILE *studenti = fopen("studenti.txt", "r");
    if (NULL == studenti)
    {
        return 1;
    }

    /* "w" — kreira novu datoteku ili briše postojeću i piše od početka */
    FILE *stipendija = fopen("stipendija.txt", "w");
    if (NULL == stipendija)
    {
        fclose(studenti);
        return 1;
    }

    traziStipendiste(studenti, stipendija);

    fclose(studenti);
    fclose(stipendija);
    return 0;
}
