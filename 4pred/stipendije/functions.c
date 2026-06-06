/*
 * #include "functions.h" — navodnici znače: traži datoteku RELATIVNO
 * od trenutnog direktorija (vlastite datoteke projekta).
 * #include <stdio.h>     — kutne zagrade znače: traži u sistemskim
 * direktorijima prevoditelja (standardne biblioteke).
 */
#include <stdio.h>
#include "functions.h"

/*
 * "%s" čita jednu "riječ" — zaustavlja se na prvom bjelu znaku
 * (razmak, tab, newline). Zbog toga su ime i prezime posebna polja.
 *
 * Za char polje new pišemo & ispred imena:
 *   studenti[i].ime     — već je pokazivač na prvi znak niza (adresa)
 *   &studenti[i].bodovi — int nije polje, treba & za adresu
 *
 * Formatni string "%s %s %d %f" čita sve četiri vrijednosti odjednom;
 * razmaci u formatu konzumiraju bjeline između unosa.
 */
void unesiStudente(Student *studenti, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        scanf("%s %s %d %f",
              studenti[i].ime,
              studenti[i].prezime,
              &studenti[i].bodovi,
              &studenti[i].prosjek);
    }
}

/*
 * Inicijaliziramo pokazivač na NULL — posebna vrijednost koja znači
 * "pokazivač ne pokazuje ni na što valjano".
 *
 * Algoritam kombinira dva uvjeta pri ažuriranju najboljeg:
 *   1. najbolji == NULL  — još nismo pronašli nijednog kandidata
 *   2. studenti[i].bodovi > najbolji->bodovi  — pronašli smo boljeg
 *
 * Operator || (ili) znači: ažuriraj ako je barem jedan uvjet ispunjen.
 * Bez provjere NULL-a, dereferencirani &(*najbolji).bodovi bio bi
 * nedefinrano ponašanje (UB) jer NULL nije valjana adresa.
 *
 * Povratna vrijednost NULL signalizira pozivatelju da nitko nije
 * zadovoljio uvjete — pozivatelj mora provjeriti prije dereferenciranja!
 */
Student *pronadiNajboljeg(Student *studenti, int n)
{
    Student *najbolji = NULL;
    int i;
    for (i = 0; i < n; i++)
    {
        if (studenti[i].bodovi >= 80 && studenti[i].prosjek >= 4.0f)
        {
            if (najbolji == NULL || studenti[i].bodovi > najbolji->bodovi)
            {
                najbolji = &studenti[i];
            }
        }
    }
    return najbolji;
}

/*
 * Funkcija prima Student * (pokazivač) — pristupamo članovima s ->.
 * %.2f ispisuje float na 2 decimalna mjesta.
 * %s ispisuje char niz do prvog '\0'.
 */
void ispisiStudenta(Student *s)
{
    printf("%s %s %d %.2f\n", s->ime, s->prezime, s->bodovi, s->prosjek);
}
