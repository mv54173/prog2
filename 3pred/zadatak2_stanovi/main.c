#include <stdio.h>
#include <string.h>

/*
 * "typedef struct { ... } stan_t;" omogućuje da umjesto "struct stan_t"
 * pišemo samo "stan_t" kao tip — čišći kod.
 *
 * +1 u char adresa[100 + 1] rezervira mjesto za terminirajući '\0',
 */
typedef struct
{
    float kvadratura;
    float cijena;
    char adresa[100 + 1];
    char energetski_razred;
    int klima;
} stan_t;

/*
 * Polje se uvijek prosljeđuje kao pokazivač na prvi element —
 * unutar funkcije stanovi[] i *stanovi su ekvivalentni zapisi.
 * Promjene unutar funkcije MIJENJAJU originalno polje (nema kopiranja).
 * Zbog toga obavezno prosljeđujemo i duljinu n — funkcija sama
 * ne može znati koliko je elemenata u polju.
 */
void popuniStanove(stan_t stanovi[], int n)
{
    for (int i = 0; i < n; i++)
    {
        /*
         * scanf("%f ") — razmak IZA formata konzumira sve bjeline
         * (razmake, tabulatore, newline-ove) koji ostanu u bufferu
         * nakon učitavanja broja. To je ključno prije fgets-a jer
         * bi inače fgets odmah pokupio zaostali '\n' kao praznu liniju.
         */
        scanf("%f ", &stanovi[i].kvadratura);
        scanf("%f ", &stanovi[i].cijena);

        /*
         * fgets(dest, max_znakova, stream)
         * Čita cijelu liniju uključujući '\n' na kraju.
         * Zato ručno zamjenjujemo zadnji znak ('\n') s '\0'
         * da ne bismo ispisivali nepotrebni prijelom retka.
         *
         * strlen vraca duljinu bez '\0', pa je [strlen-1] indeks '\n'.
         */
        fgets(stanovi[i].adresa, 100 + 1, stdin);
        stanovi[i].adresa[strlen(stanovi[i].adresa) - 1] = '\0';

        /*
         * scanf(" %c") — razmak ISPRED %c preskače bjeline/newline
         * koji su ostali u bufferu. Bez razmaka bi %c pokupio '\n'
         * umjesto stvarnog znaka. Ovo je česta greška na ispitu!
         */
        scanf(" %c", &stanovi[i].energetski_razred);
        scanf("%d", &stanovi[i].klima);
    }
}

/*
 * Varijabla "pronadjen" je zastavica — inicijalno 0 (false),
 * postavlja se na 1 (true) čim pronađemo barem jedan rezultat.
 * Na kraju provjeravamo je li itko bio ispisan i ispisujemo
 * poruku ako nije.
 *
 * Uvjet: cijena_po_m2 < 900 ILI (cijena_po_m2 > 1100 I nema klime)
 * Operator || ima niži prioritet od &&, ali zagrade su dodane
 * radi čitljivosti — uvijek ih pišite kad miješate && i ||.
 */
void ispisiPoKriteriju(stan_t stanovi[], int n)
{
    int pronadjen = 0;

    for (int i = 0; i < n; i++)
    {
        float cijena_po_m2 = stanovi[i].cijena / stanovi[i].kvadratura;
        if (cijena_po_m2 < 900.0f || (cijena_po_m2 > 1100.0f && stanovi[i].klima == 0))
        {
            printf("%s, %.2f\n", stanovi[i].adresa, stanovi[i].cijena);
            pronadjen = 1;
        }
    }

    if (!pronadjen)
    {
        printf("Niti jedan stan ne odgovara kriterijima.\n");
    }
}

/*
 * Funkcija vraća pokazivač (stan_t *) na element unutar polja stanovi[].
 * To je sigurno jer polje živi u main() i nije lokalna varijabla ove funkcije.
 * NIKAD ne vraćajte pokazivač na lokalnu varijablu — ona nestaje kad funkcija završi!
 *
 * Algoritam:
 *   - Pretpostavljamo da je prvi element najveći (najveci = &stanovi[0])
 *   - Prolazimo od i=1 i ažuriramo pokazivač kad nađemo većeg
 *   - Na kraju pokazivač pokazuje na najveći element
 *
 * Pristup članu kroz pokazivač: najveci->kvadratura
 */
stan_t *pronadjiNajveciStan(stan_t stanovi[], int n)
{
    stan_t *najveci = &stanovi[0];

    for (int i = 1; i < n; i++)
    {
        if (stanovi[i].kvadratura > najveci->kvadratura)
        {
            najveci = &stanovi[i];
        }
    }

    return najveci;
}

int main(void)
{
    int n;

    /*
     * do-while se izvršava BAREM jedanput — idealna za validaciju jer
     * uvijek moramo pročitati unos prije nego ga možemo provjeriti.
     * Petlja se ponavlja dok uvjet u while() ostaje istinit (tj. unos nije valjan).
     */
    do
    {
        scanf("%d", &n);
    } while (!(n > 0 && n < 100));

    /*
     * Veličina polja određuje se u trenutku izvođenja (runtime), a ne
     * pri prevođenju. VLA se alocira na stogu (stack), pa za veliki n
     * može doći do stack overflowa — u produkcijskom kodu koristimo malloc.
     */
    stan_t stanovi[n];

    popuniStanove(stanovi, n);

    printf("REZULTATI:\n");
    /*
     * Pozivamo funkciju predavši polje (tj., pokazivač na prvi član) i broj članova.
     */
    ispisiPoKriteriju(stanovi, n);

    /*
     * Pokazivač koji vraća pronadjiNajveciStan pokazuje na element
     * unutar polja stanovi[] — možemo ga odmah koristiti za ispis
     * članova strukture operatorom ->.
     */
    stan_t *najveci = pronadjiNajveciStan(stanovi, n);
    printf("Najveci stan je: %s, %.2f", najveci->adresa, najveci->kvadratura);

    return 0;
}
