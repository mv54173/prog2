#include <stdio.h>
#include <stdlib.h>

/*
Napišite program u programskom jeziku C koji iz binarne datoteke kviz.bin
učitava podatke o rezultatima kviza. Ekipe su u datoteci već poredane po
rezultatu (od najbolje prema najlošijoj) i imaju ime (maks 20 znakova), broj članova
i postotak rješenosti kviza. Budući da broj ekipa nije unaprijed poznat,
potrebno je dinamički alocirati memoriju za polje struktura nakon što
se odredi veličina datoteke.
Nakon uspješnog učitavanja, program pod ključnom riječi REZULTATI: mora ispisati:

    - Nagrađene ekipe: ime prve tri ekipe (1., 2. i 3. mjesto) te
    ime predzadnje ekipe na tablici.

    - Prosječan postotak rješenosti svih ekipa (ispisan na dvije decimale).

*/

typedef struct
{
    char ime[20];
    int brojClanova;
    float postotakRjesenosti;
} ekipa_t;

long brojEkipa(FILE *rezultatiFile);
void ispisiNagradene(FILE *rezultatiFile);
float prosjecnaRjesenost(FILE *rezultatiFile);

int main(void)
{
    FILE *fp = fopen("kviz.bin", "rb");
    if (NULL == fp)
    {
        perror("Dogodila se greška");
        return 1;
    }

    printf("REZULTATI:\n");
    ispisiNagradene(fp);
    /* moramo se vratiti na početak datoteke */
    fseek(fp, 0, SEEK_SET);
    float prosjek = prosjecnaRjesenost(fp);
    printf("Prosjek je: %.2f\n", prosjek);

    fclose(fp);
    return 0;
}

/*
 * Alociramo prostor samo za jednu ekipu i višekratno rekoristimo isti
 * blok memorije — svaki fread prepisuje prethodne podatke.
 * Ovo je memorijski učinkovito kad nam ne trebaju svi zapisi odjednom.
 *
 * fseek(fp, -2 * sizeof(ekipa_t), SEEK_END) pozicionira se na
 * predzadnji zapis:
 *   SEEK_END = kraj datoteke (iza zadnjeg bajta)
 *   -1 * sizeof(ekipa_t) = zadnji zapis (posljednja ekipa)
 *   -2 * sizeof(ekipa_t) = predzadnji zapis
 * Negativan offset od SEEK_END znači "idi unazad od kraja".
 *
 */
void ispisiNagradene(FILE *rezultatiFile)
{
    ekipa_t *nagradena = (ekipa_t *)malloc(sizeof(ekipa_t));

    /* tri uzastopna fread čitaju 1., 2. i 3. ekipu — pozicija se automatski pomiče */
    fread(nagradena, sizeof(ekipa_t), 1, rezultatiFile);
    printf("%s\n", nagradena->ime);

    fread(nagradena, sizeof(ekipa_t), 1, rezultatiFile);
    printf("%s\n", nagradena->ime);

    fread(nagradena, sizeof(ekipa_t), 1, rezultatiFile);
    printf("%s\n", nagradena->ime);

    fseek(rezultatiFile, -2 * (long)sizeof(ekipa_t), SEEK_END);
    fread(nagradena, sizeof(ekipa_t), 1, rezultatiFile);
    printf("%s\n", nagradena->ime);

    free(nagradena);
    nagradena = NULL;
}

/*
 * Standardni idiom: fseek na kraj + ftell = veličina u bajtovima.
 * Broj zapisa = veličina / sizeof(ekipa_t).
 * Pretpostavka: svi zapisi su jednake veličine (vrijedi za binarne datoteke struktura).
 *
 * Pamtimo sve trenutnu pozicuju u curr kako funkcija ne bi pomakla kazaljku. Na kraju
 * funkcije postavljamo poziciju ponovo na tu poziciju.
 */
long brojEkipa(FILE *rezultatiFile)
{
    long curr = ftell(rezultatiFile);

    fseek(rezultatiFile, 0, SEEK_END);
    long velicina = ftell(rezultatiFile);

    fseek(rezultatiFile, curr, SEEK_SET);
    return velicina / sizeof(ekipa_t);
}

/*
 * malloc(brEkipa * sizeof(ekipa_t)) alocira polje od brEkipa struktura.
 * Za razliku od VLA (stack), ovo je sigurno za velik n jer heap nije
 * ograničen veličinom stoga (tipično ~1–8 MB).
 *
 * fread(polje, sizeof(ekipa_t), brEkipa, fp) čita SVE zapise odjednom
 * u dinamički alocirano polje — jedan poziv umjesto petlje s n fread-ova.
 *
 * Nakon upotrebe moramo pozvati free(polje) —
 * inače je svaki poziv prosjecnaRjesenost() memory leak.
 */
float prosjecnaRjesenost(FILE *rezultatiFile)
{
    long brEkipa = brojEkipa(rezultatiFile);

    ekipa_t *polje = (ekipa_t *)malloc(brEkipa * sizeof(ekipa_t));

    fread(polje, sizeof(ekipa_t), brEkipa, rezultatiFile);

    float suma = 0;
    for (int i = 0; i < brEkipa; i++)
    {
        suma += polje[i].postotakRjesenosti;
    }

    free(polje);
    return suma / brEkipa;
}
