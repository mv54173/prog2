#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char ime[30];
    char prezime[30];
    int godinaStudiranja;
    float prosjek;
} student_t;

/*
 * fscanf uvijek čita u stipendisti[brojac] — trenutni slobodni slot.
 * Ako student ne kvalificira, brojac se ne povećava, pa sljedeći fscanf
 * prepisuje isti slot. Kvalificirani student "zauzme" slot i pomakne brojac.
 *
 * Vizualizacija za primjer iz datoteke:
 *   Ivan  (3.85, god.2) → ne kvalificira → stipendisti[0] ostaje slobodan
 *   Ana   (4.52, god.3) → kvalificira    → stipendisti[0]=Ana, brojac=1
 *   Marko (3.12, god.1) → ne kvalificira → stipendisti[1] ostaje slobodan
 *   Petra (4.78, god.2) → kvalificira    → stipendisti[1]=Petra, brojac=2
 *   Luka  (3.67, god.4) → ne kvalificira (god>3) → stipendisti[2] slobodan
 *   Mia   (4.21, god.3) → kvalificira    → stipendisti[2]=Mia, brojac=3
 *
 * Nakon fscanf petlje slijedi fprintf koji piše u istu datoteku.
 * Zahvaljujući "a+" modu, fprintf automatski piše na kraj — ne treba
 * fseek ni ručno postavljanje pozicije.
 */
void traziStipendiste(FILE *studenti)
{
    student_t stipendisti[50];
    int brojac = 0;

    while (fscanf(studenti, "%s %s %d %f",
                  stipendisti[brojac].ime,
                  stipendisti[brojac].prezime,
                  &stipendisti[brojac].godinaStudiranja,
                  &stipendisti[brojac].prosjek) != EOF)
    {
        if (stipendisti[brojac].prosjek >= 4.0f &&
            stipendisti[brojac].godinaStudiranja <= 3)
        {
            brojac++;
        }
    }

    /* fprintf s istim FILE * — "a+" jamči da ide na kraj datoteke */
    fprintf(studenti, "\n******STIPENDISTI******\n");

    for (int i = 0; i < brojac; i++)
    {
        fprintf(studenti, "%s %s\n", stipendisti[i].ime,
                stipendisti[i].prezime);
    }
}

/*
 * fopen("datoteka", "a+") otvara datoteku za čitanje I pisanje:
 *   - čitanje počinje od POČETKA datoteke
 *   - pisanje uvijek ide na KRAJ datoteke (append), bez obzira na poziciju čitanja
 *   - ako datoteka ne postoji, kreira se
 *
 * Ovo je ključno za ovaj zadatak: trebamo pročitati cijelu datoteku,
 * a zatim dopisati stipendiste na kraj — sve s jednim file handleom.
 * Alternativa bi bila otvoriti datoteku dvaput ("r" za čitanje, "a" za pisanje),
 * ali "a+" to elegantno rješava u jednom pozivu fopen.
 */
int main(void)
{
    FILE *studenti = fopen("studenti_append.txt", "a+");
    if (NULL == studenti)
    {
        return 1;
    }

    traziStipendiste(studenti);

    fclose(studenti);
    return 0;
}
