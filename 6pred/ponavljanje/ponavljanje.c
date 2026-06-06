#include <stdio.h>
#include <stdlib.h>

/*
 * fgetc(fp) čita jedan znak i vraća ga kao int (ne char!).
 * Razlog za int: EOF je -1, a char može biti unsigned na nekim platformama
 * pa -1 ne bi stalo — int garantira ispravan prikaz EOF-a.
 *
 * Petlja while ((znak = fgetc(pUlaz)) != EOF) čita dok ima znakova.
 *   Dodjela unutar uvjeta: znak = fgetc(...) dogodi se PRIJE usporedbe s EOF.
 *   Zagrade oko dodjele su obavezne — bez njih bi se != izvršio prvi.
 *
 * Varijabla "prethodni" pamti zadnji ISPISANI znak.
 * Inicijaliziramo je na -1 (nije razmak) — sigurno za prvi znak u datoteci.
 *
 * Uvjet za preskakanje: trenutni i prethodni znak su razmaci.
 * continue preskače ostatak tijela petlje i ide na sljedeću iteraciju —
 * prethodni se ne ažurira, što je ispravno jer razmak nije ispisan.
 *
 * fputc(znak, fp) piše jedan znak u datoteku.
 * Ažuriramo prethodni tek nakon ispisa — ako preskočimo
 * razmak s continue, prethodni ostaje ' ' što je ispravno.
 */
void pretvorba(FILE *pUlaz, FILE *pIzlaz)
{
    int znak;
    int prethodni = -1;

    while ((znak = fgetc(pUlaz)) != EOF)
    {
        if (znak == ' ' && prethodni == ' ')
        {
            continue;
        }
        else
        {
            fputc(znak, pIzlaz);
            prethodni = znak;
        }
    }
}

int main(void)
{
    /*
     * fopen(ime, mod) otvara datoteku i vraća FILE * ili NULL ako ne uspije.
     * Modovi:
     *   "r"  — čitanje (datoteka mora postojati)
     *   "w"  — pisanje (kreira novu ili briše postojeću)
     *   "a"  — dodavanje na kraj (append)
     *   "r+" — čitanje i pisanje
     *
     * fopen vraća NULL ako datoteka ne postoji ("r"), nema dozvola, ili
     * sustav ne može otvoriti više datoteka. Dereferenciranje NULL FILE *
     * je nedefinrano ponašanje — uvijek provjeravamo prije upotrebe.
     */
    FILE *pUlaz = NULL;
    FILE *pIzlaz = NULL;

    pUlaz = fopen("ulaz.txt", "r");
    if (NULL == pUlaz)
    {
        printf("Nisam uspio otvoriti ulaznu datoteku!\n");
        return 1;
    }

    pIzlaz = fopen("izlaz.txt", "w");
    if (NULL == pUlaz || NULL == pIzlaz)
    {
        printf("Nisam uspio otvoriti izlaznu datoteku!\n");
        fclose(pUlaz); // s obzirom da smo je uspješno otvorili moramo je zatvoriti
        return 1;
    }

    pretvorba(pUlaz, pIzlaz);

    /*
     * Zatvaramo redom — redosljed nije bitan, ali je dobra praksa
     * zatvoriti izlaz prije ulaza jer izlaz može imati podatke u bufferu.
     */
    fclose(pIzlaz);
    fclose(pUlaz);

    return 0;
}
