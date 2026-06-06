#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * calloc(broj_elemenata, velicina_elementa) alocira memoriju i
 * automatski inicijalizira sve bajtove na 0.
 *
 * Razlika od malloc:
 *   malloc(n)         — alocira n bajtova, sadržaj NIJE definiran (smeće)
 *   calloc(n, size)   — alocira n*size bajtova, sve postavljeno na 0
 *
 * Ovdje: calloc(strlen(str) + 1, sizeof(char))
 *   strlen(str) + 1  — duljina stringa + 1 za terminirajući '\0'
 *   sizeof(char)     — veličina jednog znaka (uvijek 1 bajt)
 *
 *
 * Velika slova (A–Z) imaju ASCII vrijednosti 65–90.
 * Mala slova  (a–z) imaju ASCII vrijednosti 97–122.
 * Razlika je točno 32 — dodavanjem 32 na veliko slovo dobivamo malo.
 *   'A' + 32 = 'a',  'Z' + 32 = 'z'
 *
 * Funkcija radi na kopiji — str[] se čita ali nikad ne piše.
 * Ovo je primjer "non-destructive" operacije koja čuva ulazni podatak.
 */
char *kopirajVelikaUMala(char str[])
{
    char *kopija = (char *)calloc(strlen(str) + 1, sizeof(char));

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            kopija[i] = str[i] + 32; /* veliko → malo: +32 u ASCII tablici */
        }
        else
        {
            kopija[i] = str[i]; /* ostali znakovi (mala slova, razmaci...) se kopiraju */
        }
    }

    kopija[strlen(str)] = '\0'; /* eksplicitno terminiranje */
    return kopija;              /* vraćamo heap pokazivač — pozivatelj mora zvati free() */
}

int main()
{
    char str[50];
    fgets(str, 50, stdin);
    str[strlen(str) - 1] = '\0';

    char *kopiraniStr = kopirajVelikaUMala(str);

    printf("%s\n", kopiraniStr);

    /* free + NULL — standardni obrazac za sigurno oslobađanje heap memorije */
    free(kopiraniStr);
    kopiraniStr = NULL;
    return 0;
}
