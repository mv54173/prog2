#include <stdio.h>
#include <stdlib.h>

/*
 * fscanf(fp, format, ...) radi isto kao scanf, ali čita iz FILE * umjesto stdin.
 * Vraća broj uspješno pročitanih vrijednosti, ili EOF kad nema više podataka.
 *
 * Idiom: while (fscanf(fp, "%d", &ulaz) != EOF)
 * Čita broj po broj dok god postoji što pročitati — automatski preskače
 * razmake i newline-ove između brojeva (fscanf ih tretira kao razdvojnike).
 *
 * Strožija provjera: fscanf može vratiti 0 ako naiđe na ne-broj (npr. slovo).
 * U tom slučaju petlja ne bi završila — beskonačna petlja.
 * Za robustnost: while (fscanf(fp, "%d", &ulaz) == 1).
 *
 * Funkcija mora vratiti i brojac i sumu. C funkcija ima jedan povratni tip,
 * pa drugi podatak vraćamo kroz pokazivač:
 *   int *suma — funkcija upisuje rezultat na adresu koju joj pošaljemo.
 *   *suma = 0 — dereferenciramo pokazivač da inicijaliziramo vrijednost
 *   *suma += ulaz — dereferenciramo da akumuliramo zbroj
 *
 * Pozivatelj (main) mora proslijediti adresu lokalne varijable: &suma.
 * Nakon poziva, suma u main-u sadrži zbroj koji je funkcija upisala.
 */
int prebrojiIZbroji(FILE *brojevi, int *suma)
{
    *suma = 0;
    int brojac = 0;

    int ulaz;
    // while (fscanf(brojevi, "%d", &ulaz) != EOF)
    while (fscanf(brojevi, "%d", &ulaz) == 1)
    {
        brojac++;
        *suma += ulaz;
    }

    return brojac;
}

/*
 * suma i brojac su int, pa suma/brojac bez casta daje cjelobrojna dijeljenje.
 * (float)suma pretvara jedan operand u float — rezultat je float.
 */
int main(void)
{
    FILE *brojevi = fopen("brojevi.txt", "r");
    if (NULL == brojevi)
    {
        return 1;
    }

    int suma;
    int brojac = prebrojiIZbroji(brojevi, &suma);

    if (0 == brojac)
    {
        printf("Nema brojeva u datoteci.");
    }

    printf("%d %d %.2f", brojac, suma, (float)suma / brojac);

    fclose(brojevi);
    return 0;
}