#include <stdio.h>
#include <stdlib.h>

/*
 * fgets(buf, max, fp) čita jedan redak iz datoteke:
 *   - čita najviše max-1 znakova (ostavlja mjesto za '\0')
 *   - staje na '\n' (koji uključuje u string) ili EOF
 *   - vraća buf ako je pročitao barem jedan znak, NULL na kraju datoteke ili grešci
 *
 * Idiom: while (fgets(redak, sizeof(redak), fp) != NULL)
 *   - petlja se izvršava za svaki redak
 *   - automatski staje kad nema više redaka (fgets vrati NULL)
 *
 * redak[0] je prvi znak pročitanog retka.
 * Velika slova u ASCII tablici su u rasponu 'A' (65) do 'Z' (90).
 * Uvjet redak[0] >= 'A' && redak[0] <= 'Z' provjerava je li prvi
 * znak u tom rasponu — čitljivije i prenosivije nego usporedba s brojevima.
 *
 * printf("%s", redak) ispisuje string do '\0' — '\n' koji fgets uključi
 * ovdje je ŽELJENO ponašanje jer ispisujemo cijeli redak s prijelomom.
 */
void velikaSlova(FILE *recenice)
{
    char redak[200 + 1];
    while (fgets(redak, 200 + 1, recenice) != NULL)
    {
        if (redak[0] >= 'A' && redak[0] <= 'Z')
        {
            printf("%s", redak);
        }
    }
}

/*
 * fopen(ime, mod) otvara datoteku i vraća FILE * ili NULL ako ne uspije.
 * Mod "r" — čitanje (datoteka mora postojati).
 *
 * Provjera NULL odmah nakon fopena — ako datoteka ne postoji ili
 * nema dozvola, dereferenciranje NULL FILE * bi bila greška.
 * return 1 signalizira operacijskom sustavu da program nije završio uspješno
 *
 * fclose(fp) isprazni buffer i oslobodi resurse.
 * Svaka uspješno otvorena datoteka mora biti zatvorena.
 */
int main()
{
    FILE *recenice = fopen("recenice.txt", "r");

    if (NULL == recenice)
    {
        printf("Nisam uspio otvoriti recenice.txt!");
        return 1;
    }

    velikaSlova(recenice);

    fclose(recenice);
    return 0;
}
