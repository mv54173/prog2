#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char grad[30];
    int mjesec;
    float temperatura;
} mjerenje_t;

int main(void)
{
    /*
     * U binarnoj datoteci strukture su zapisane kao sirovi bajtovi —
     * točno onako kako izgledaju u memoriji, bez razmaka, zareza ni teksta.
     * Mod "rb" otvara datoteku za binarno čitanje ("r" + "b" = read binary).
     */
    FILE *fileTemperature = fopen("temperature.bin", "rb");
    if (NULL == fileTemperature)
    {
        perror("Greska");
        return 1;
    }

    /*
     * fseek(fp, offset, odakle) pomiče pokazivač čitanja/pisanja.
     *
     * Treći argument — polazišna točka:
     *   SEEK_SET — od POČETKA datoteke
     *   SEEK_CUR — od TRENUTNE pozicije
     *   SEEK_END — od KRAJA datoteke
     *
     * Drugi argument — pomak u BAJTOVIMA od polazišne točke.
     *
     * sizeof(mjerenje_t) * 4 — preskačemo prvih 4 zapisa (indeksi 0–3)
     * i pozicioniramo se na početak 5. zapisa (indeks 4).
     * Ovo je moguće samo u binarnim datotekama jer su svi zapisi
     * jednake veličine — u tekstualnim datotekama retci mogu biti različite duljine.
     *
     * fread(adresa, velicina, broj, fp) čita "broj" elemenata veličine "velicina"
     * i sprema ih na "adresa". Vraća broj uspješno pročitanih elemenata.
     *
     * &petoMjerenje         — adresa varijable u koju čitamo
     * sizeof(mjerenje_t) — veličina jednog zapisa u bajtovima
     * 1              — čitamo 1 zapis
     */
    fseek(fileTemperature, sizeof(mjerenje_t) * 4, SEEK_SET);
    mjerenje_t petoMjerenje;
    fread(&petoMjerenje, sizeof(mjerenje_t), 1, fileTemperature);

    /*
     * SEEK_SET s offsetom 0 — premotaj na početak datoteke.
     * Ekvivalentno "rewind(fp)".
     *
     * Petlja čita 10 zapisa uzastopno — svaki fread automatski
     * pomiče pokazivač za sizeof(mjerenje_t) bajtova naprijed.
     * Nakon 10 iteracija pokazivač stoji iza 10. zapisa.
     */
    fseek(fileTemperature, 0, SEEK_SET);
    mjerenje_t trenutna;

    for (int i = 0; i < 10; i++)
    {
        fread(&trenutna, sizeof(mjerenje_t), 1, fileTemperature);
    }

    /*
     * ftell(fp) vraća trenutnu poziciju pokazivača kao broj bajtova od početka.
     * Nakon 10 fread poziva: a == sizeof(mjerenje_t) * 10.
     * Korisno za provjeru koliko smo pročitali ili za snimanje pozicije
     * da se možemo vratiti na nju kasnije s fseek(fp, a, SEEK_SET).
     */
    long a = ftell(fileTemperature);
    printf("%ld\n", a); /* ispis pozicije radi provjere */

    printf("%d %f\n", petoMjerenje.mjesec, petoMjerenje.temperatura);

    /*
     * Standardni način za izračun veličine datoteke:
     *   1. fseek na kraj (SEEK_END, offset 0)
     *   2. ftell vraća poziciju = ukupan broj bajtova
     *   3. Ne trebamo fseek nazad jer smo gotovi s čitanjem
     *
     * Broj zapisa = veličina datoteke / veličina jednog zapisa.
     * Cjelobrojna dijeljenje je ispravno — datoteka ne može imati
     * djelomičan zapis ako je ispravno zapisana.
     */
    fseek(fileTemperature, 0, SEEK_END);
    long velicina = ftell(fileTemperature);
    long brojZapisa = velicina / sizeof(mjerenje_t);

    printf("Velicina datoteke: %ld bajtova\n", velicina);
    printf("Velicina jednog zapisa: %zu bajtova\n", sizeof(mjerenje_t));
    printf("Broj zapisa: %ld\n", brojZapisa);

    fclose(fileTemperature);
    return 0;
}

/*
 * SADRŽAJ temperature.bin (5 zapisa):
 * Svaki redak = jedan mjerenje_t zapis
 *   grad  mjesec  temperatura
 *   zg    1       2.0
 *   os    1       2.0
 *   st    3       4.0
 *   pu    2       5.0
 *   ck    3       5.0        ← 5. zapis (indeks 4), fseek nas dovodi ovdje
 */
