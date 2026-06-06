#include <stdio.h>
#include <stdlib.h>

/*
 * Do sada smo koristili lokalne varijable i polja alocirana na STOGU (stack):
 *   int n = 5;           → stack, nestaje kad funkcija završi
 *   mjerenje_t arr[n];   → stack (VLA), nestaje kad funkcija završi
 *
 * malloc(n_bajtova) alocira memoriju na heapu:
 *   - živi dok je eksplicitno ne oslobodimo s free()
 *   - ne nestaje kad funkcija završi — možemo je sigurno vrati iz funkcije
 *   - vraća void * (generički pokazivač) koji castamo u željeni tip
 *   - vraća NULL ako alokacija nije uspjela (nema dovoljno memorije)
 *
 * sizeof(kompleksni_t) daje točan broj bajtova za strukturu —
 * uvijek koristimo sizeof umjesto hardkodiranog broja jer compiler
 * može dodati padding između članova (poravnanje memorije).
 */
typedef struct
{
    float re;
    float im;
} kompleksni_t;

/*
 * Funkcija alocira novi kompleksni_t na heapu, upisuje rezultat i vraća adresu.
 * Ovo je sigurno — za razliku od vraćanja pokazivača na lokalnu varijablu
 * (koja bi nestala po izlasku iz funkcije), heap memorija ostaje valjana
 * sve dok je ne oslobodimo s free().
 *
 * Pozivatelj (main) mora pozvati free() kad mu rezultat više ne treba.
 * Propuštanje free() = curenje memorije (memory leak) — program polako
 * troši sve više RAM-a. U dugotrajnim programima to može biti kritično.
 *
 * Cast (kompleksni_t *) ispred malloc:
 * U C-u nije obavezan (void * se implicitno konvertira), ali je čest
 * u edukativnom kodu radi jasnoće. U C++ je obavezan.
 */
kompleksni_t *zbroji(kompleksni_t *k1, kompleksni_t *k2)
{
    kompleksni_t *rezultat = (kompleksni_t *)malloc(sizeof(kompleksni_t));
    rezultat->re = k1->re + k2->re;
    rezultat->im = k1->im + k2->im;
    return rezultat;
}

int main(void)
{
    kompleksni_t k1, k2, k3;
    scanf("%f %f", &k1.re, &k1.im);
    scanf("%f %f", &k2.re, &k2.im);
    scanf("%f %f", &k3.re, &k3.im);

    kompleksni_t *rezultat = zbroji(&k1, &k2);

    printf("%.2f + %.2fi\n", rezultat->re, rezultat->im);

    /* %p ispisuje adresu pokazivača u heksadecimalnom obliku
     * npr. 0x55a3f2c010 — adresa na heap-u gdje živi struktura */
    printf("%p\n", rezultat);

    /*
     * Nakon free(rezultat), memorija je vraćena sustavu — ali varijabla
     * rezultat i dalje drži istu adresu (nije automatski postavljena na NULL).
     * Dereferenciranje takvog pokazivača je nedefinirano ponašanje:
     *   - može ispisati stare vrijednosti (ako memorija još nije prepisana)
     *   - može ispisati smeće (ako je memorija već zauzeta za nešto drugo)
     *   - može uzrokovati crash
     * Dobar obrazac: rezultat = NULL; odmah nakon free().
     */
    free(rezultat);                                       /* oslobađamo heap memoriju */
    printf("%.2f + %.2fi\n", rezultat->re, rezultat->im); /* UB! dangling pointer */

    rezultat = NULL;

    rezultat = zbroji(&k2, &k3);
    printf("%.2f + %.2fi\n", rezultat->re, rezultat->im);
    printf("%p\n", rezultat);

    free(rezultat);
    rezultat = NULL;
    return 0;
}
