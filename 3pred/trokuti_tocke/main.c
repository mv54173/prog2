#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * point_t je obična struktura s tri int člana.
 *
 * triangle_t ne sadrži kopije točaka nego POKAZIVAČE na njih (point_t *).
 * Prednosti:
 *   - Više trokuta može dijeliti istu točku bez dupliciranja podataka.
 *   - Promjena koordinate točke automatski se vidi u svim trokutima koji
 *     pokazuju na nju.
 * Opasnost:
 *   - Ako točka nestane iz memorije (npr. lokalna varijabla izađe iz scopea),
 *     pokazivači u trokutima postaju "dangling" (vise u zraku) — nedefinrano ponašanje.
 */
typedef struct
{
    int x;
    int y;
    int z;
} point_t;

typedef struct
{
    point_t *A;
    point_t *B;
    point_t *C;
} triangle_t;

/*
 * &(tocke[i].x) — operator & daje adresu člana x i-tog elementa polja.
 * Ekvivalentno: &tocke[i].x  (operator . ima viši prioritet od &,
 * zagrade nisu nužne ali povećavaju čitljivost).
 *
 * Sve tri koordinate čitaju se u jednom pozivu scanf-a s formatom "%d %d %d".
 * Razmak u formatu konzumira bilo koji broj bjelina između brojeva.
 */
void unesiTocke(point_t *tocke, int m)
{
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d %d", &(tocke[i].x), &(tocke[i].y), &(tocke[i].z));
    }
}

/*
 * Unos trokuta funkcionira u dva koraka:
 *   1. Čitamo indekse (tockaA, tockaB, tockaC) — cijeli brojevi koji
 *      predstavljaju pozicije u polju tocke[].
 *   2. Koristimo operator & da dobijemo adresu (pokazivač) na tu točku
 *      i pohranimo je u strukturu trokuta.
 *
 * trokuti[i].A = &(tocke[tockaA]);
 *   - tocke[tockaA]    — sama struktura point_t (vrijednost)
 *   - &(tocke[tockaA]) — adresa te strukture (point_t * pokazivač)
 *
 * Na taj način trokut "zna" gdje u memoriji žive njegove točke,
 * bez da ih kopira — promjene na tocke[] odmah su vidljive kroz trokut.
 */
void unesiTrokute(triangle_t *trokuti, int n, point_t *tocke)
{
    int tockaA, tockaB, tockaC;
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d %d", &tockaA, &tockaB, &tockaC);
        trokuti[i].A = &(tocke[tockaA]);
        trokuti[i].B = &(tocke[tockaB]);
        trokuti[i].C = &(tocke[tockaC]);
    }
}

/*
 * C ne podržava == za usporedbu struktura — mora se usporediti svaki član posebno.
 * Ovdje uspoređujemo sve tri koordinate operatorom && (logički I).
 *
 * Funkcija prima pokazivače (point_t *) umjesto vrijednosti (point_t)
 * kako bi se izbjeglo kopiranje strukture pri pozivu.
 * Pristup članu kroz pokazivač: p1->x  (ekvivalentno (*p1).x)
 */
int equalPoints(point_t *p1, point_t *p2)
{
    if (p1->x == p2->x && p1->y == p2->y && p1->z == p2->z)
    {
        return 1;
    }

    return 0;
}

/*
 * Prolazimo kroz sve trokute i ispisujemo samo one koji zadovoljavaju uvjet:
 * sve tri točke moraju biti međusobno različite (valjan trokut),
 * što je ekvivalentno: NE (A==B ILI A==C ILI B==C)
 *
 * Operator -> dereferencira pokazivač na točku i pristupa članu u jednom koraku.
 */
void printTriangles(triangle_t *trokuti, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (equalPoints(trokuti[i].A, trokuti[i].B) == 0 &&
            equalPoints(trokuti[i].A, trokuti[i].C) == 0 &&
            equalPoints(trokuti[i].C, trokuti[i].B) == 0)
        {
            printf("Triangle %d: (%d, %d, %d), (%d, %d, %d), (%d, %d, %d)\n", i,
                   trokuti[i].A->x, trokuti[i].A->y, trokuti[i].A->z,
                   trokuti[i].B->x, trokuti[i].B->y, trokuti[i].B->z,
                   trokuti[i].C->x, trokuti[i].C->y, trokuti[i].C->z);
        }
    }
}

/*
 * sqrt(x)    — kvadratni korijen (vraća double)
 * pow(x, n)  — potenciranje: x^n (vraća double)
 *
 * Euklidska udaljenost u 3D: d = sqrt((x2-x1)^2 + (y2-y1)^2 + (z2-z1)^2)
 *
 */
float izracunajDuljinu(point_t *p1, point_t *p2)
{
    return sqrt(pow(p1->x - p2->x, 2) +
                pow(p1->y - p2->y, 2) +
                pow(p1->z - p2->z, 2));
}

/*
 * izracunajOpseg prima triangle_t * (pokazivač), ne triangle_t (kopiju).
 * Razlog: izbjegavamo kopiranje strukture pri svakom pozivu — posebno
 * važno kad struktura sadrži pokazivače, jer bi kopija pokazivača
 * i dalje pokazivala na iste točke (plitka kopija).
 *
 * Opseg = AB + AC + CB (zbroj duljina triju stranica).
 */
float izracunajOpseg(triangle_t *trokut)
{
    float a = izracunajDuljinu(trokut->A, trokut->B);
    float b = izracunajDuljinu(trokut->A, trokut->C);
    float c = izracunajDuljinu(trokut->C, trokut->B);

    return a + b + c;
}

/*
 * Algoritam s praćenjem indeksa:
 *   - max = 0, maxIdx = 0 (pretpostavljamo da je prvi najveći)
 *   - Prolazimo kroz sve elemente i ažuriramo kad nađemo većeg
 *   - Vraćamo &trokuti[maxIdx] — adresu elementa unutar polja
 *
 * Sigurno je vratiti pokazivač na element polja trokuti[] jer to polje
 * živi u main() i neće biti uništeno nakon povratka iz ove funkcije.
 *
 * GREŠKA koju treba izbjegavati: ne vraćati pokazivač na lokalnu varijablu
 * (npr. triangle_t temp = ...; return &temp;) — lokalna varijabla nestaje
 * kad funkcija završi, a pokazivač postaje dangling pointer!
 */
triangle_t *maxOpseg(triangle_t *trokuti, int n)
{
    float max = 0;
    int maxIdx = 0;

    for (int i = 0; i < n; i++)
    {
        if (izracunajOpseg(&trokuti[i]) > max)
        {
            max = izracunajOpseg(&trokuti[i]);
            maxIdx = i;
        }
    }

    return &trokuti[maxIdx];
}

int main()
{
    int n, m;

    scanf("%d", &m);
    scanf("%d", &n);

    /*
     * Polja fiksne veličine (10 i 5) — u produkcijskom kodu koristili bismo
     * VLA (point_t tocke[m]) ili dinamičku alokaciju (malloc) da podržimo
     * proizvoljan broj elemenata bez hardkodiranih granica.
     */
    point_t tocke[10];
    unesiTocke(tocke, m);

    triangle_t trokuti[5];
    unesiTrokute(trokuti, n, tocke);

    printTriangles(trokuti, n);

    /*
     * maxOpseg vraća triangle_t * — pokazivač na element unutar trokuti[].
     * Pristupamo članovima kroz -> jer je trokutSNajvecimOpsegom pokazivač.
     * A, B, C su također pokazivači (point_t *), pa opet koristimo ->:
     *   trokutSNajvecimOpsegom->A->x
     * Dva uzastopna -> su uobičajen obrazac s ugniježđenim pokazivačima.
     */
    triangle_t *trokutSNajvecimOpsegom = maxOpseg(trokuti, n);

    printf("Largest triangle: (%d, %d, %d), (%d, %d, %d), (%d, %d, %d)\n",
           trokutSNajvecimOpsegom->A->x, trokutSNajvecimOpsegom->A->y, trokutSNajvecimOpsegom->A->z,
           trokutSNajvecimOpsegom->B->x, trokutSNajvecimOpsegom->B->y, trokutSNajvecimOpsegom->B->z,
           trokutSNajvecimOpsegom->C->x, trokutSNajvecimOpsegom->C->y, trokutSNajvecimOpsegom->C->z);

    return 0;
}
