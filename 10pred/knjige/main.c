#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "functions.h"

int main(void)
{
    /*
     * fgets čita cijeli redak uključujući znak '\n' na kraju.
     * Zato ga ručno brišemo postavljanjem tog znaka na '\0'
     * (strlen - 1 daje indeks zadnjeg znaka prije '\0').
     */
    char imeDatoteke[50];
    fgets(imeDatoteke, 50, stdin);
    imeDatoteke[strlen(imeDatoteke) - 1] = '\0';

    /*
     * ucitajKnjige otvara datoteku, alocira memoriju i puni polje struktura.
     * Broj pročitanih knjiga vraća se kroz pokazivač &n (izlazni parametar).
     * Funkcija vraća pokazivač na dinamički alocirano polje — moramo ga osloboditi!
     */
    int n;
    KNJIGA *polje = ucitajKnjige(imeDatoteke, &n);

    if (n == -1) /* Datoteka je bila prazna, polje je NULL — ne smijemo ga koristiti */
    {
        return 1;
    }

    printf("%d\n", n);
    printf("%s\n", polje[0].naslov); /* Pristup prvom elementu polja struktura */

    /*
     * Zovemo izračun prosječnog broja stranica za 2023.
     */
    float prosjekZa2023 = izracunajProsjecnBrojStr(polje, n, 2023);

    printf("%f\n", prosjekZa2023);

    /*
     * Pozivamo prebrojavanje knjiha u žanru Kuharica
     */
    int brojKuharica = prebrojiPoZanru(polje, n, "Kuharica");

    printf("%d\n", brojKuharica);

    /*
     * Obavezno oslobađamo memoriju koju je alocirao calloc unutar ucitajKnjige.
     * Postavljanje na NULL sprječava slučajno korištenje oslobođenog pokazivača.
     */
    free(polje);
    polje = NULL;
    return 0;
}
