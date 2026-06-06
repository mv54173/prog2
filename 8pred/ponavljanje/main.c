#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main(void)
{
    int n;
    scanf("%d", &n);

    /*
     * MOD "wb" — binarno pisanje
     * obavezno za binarne datoteke jer bi konverzija pokvarila bajtove strukture.
     *
     * Zatvaramo datoteku prije ponovnog otvaranja za čitanje.
     * Razlog: fclose isprazni write buffer na disk — bez fclose podaci
     * možda još nisu fizički zapisani, pa bi fread čitao nepotpunu datoteku.
     */
    FILE *fileTemperature = NULL;
    fileTemperature = fopen("temperature.bin", "wb");

    zapisiTemperature(fileTemperature, n);
    fclose(fileTemperature);

    fileTemperature = fopen("temperature.bin", "rb");
    /*
     * fread(temperature, sizeof(mjerenje_t), n, fp) čita n zapisa odjednom
     * i puni polje temperature[] — ekvivalentno n uzastopnih fread poziva
     * po 1 zapis, ali u jednom pozivu.
     *
     * Parametri fread(adresa, velicina_elementa, broj_elemenata, fp):
     *   temperature        — adresa prvog elementa polja (niz = pokazivač)
     *   sizeof(mjerenje_t) — veličina jednog zapisa
     *   n                  — koliko zapisa čitamo
     *   fileTemperature    — izvorišna datoteka
     *
     * VLA temperature[n] — veličina određena u runtime, alocira se na stogu.
     */
    mjerenje_t temperature[n];
    fread(temperature, sizeof(mjerenje_t), n, fileTemperature);

    mjerenje_t *najvisa = rekordnaTemperatura(temperature, n);

    if (NULL == najvisa)
    {
        printf("Nije zabiljezena nijedna ljetna temperatura");
    }
    else
    {
        printf("%.2f %s", najvisa->temperatura, najvisa->grad);
    }

    fclose(fileTemperature);
    return 0;
}
