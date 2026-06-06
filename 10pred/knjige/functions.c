#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

/*
 * Čita knjige iz binarne datoteke čiji je format:
 *   [ int n ][ KNJIGA 0 ][ KNJIGA 1 ] ... [ KNJIGA n-1 ]
 *
 * Parametar brojKnjiga je izlazni parametar — funkcija kroz njega
 * vraća koliko je knjiga zapravo pročitano (caller ne zna unaprijed).
 */
KNJIGA *ucitajKnjige(const char *imeDatoteke, int *brojKnjiga)
{
    FILE *fp = NULL;
    fp = fopen(imeDatoteke, "rb"); /* "rb" = read binary, važno na Windowsima */
    if (fp == NULL)
    {
        perror("Greška je");
        exit(1);
    }

    /*
     * fread(odrediste, velicina_jednog_elementa, broj_elemenata, datoteka)
     * Ovdje čitamo jedan int — broj knjiga zapisan na početku datoteke.
     * Povratna vrijednost je broj USPJEŠNO pročitanih elemenata (očekujemo 1).
     */
    int procitano = fread(brojKnjiga, sizeof(int), 1, fp);

    if (procitano == 0) /* Datoteka je prazna — nije pročitan ni broj knjiga */
    {
        *brojKnjiga = -1; /* Signaliziramo grešku pozivatelju kroz izlazni parametar */
        fclose(fp);
        return NULL;
    }

    /*
     * calloc(*brojKnjiga, sizeof(KNJIGA)) alocira memoriju za n struktura
     * i inicijalizira sve bajtove na nulu (za razliku od malloc koji to ne radi).
     * Vraća void* koji kastamo u KNJIGA*.
     */
    KNJIGA *polje = (KNJIGA *)calloc(*brojKnjiga, sizeof(KNJIGA));

    /*
     * Čitamo sve knjige odjednom — fread puni polje struktura direktno iz datoteke.
     * Povratna vrijednost je broj stvarno pročitanih struktura (može biti manji
     * od *brojKnjiga ako je datoteka kraća nego što zaglavlje obećava).
     */
    procitano = fread(polje, sizeof(KNJIGA), *brojKnjiga, fp);

    *brojKnjiga = procitano; /* Ažuriramo na stvarni broj pročitanih knjiga */

    fclose(fp);
    return polje; /* Pozivatelj je odgovoran za free() ovog pokazivača */
}

/*
 * Prolazi kroz sva polja i zbraja broj stranica knjiga iz zadane godine.
 */
float izracunajProsjecnBrojStr(KNJIGA *knjige, int brojKnjiga, int godina)
{
    float suma = 0;
    int brojac = 0;

    for (int i = 0; i < brojKnjiga; i++)
    {
        if (godina == knjige[i].godina)
        {
            suma += knjige[i].brojStr;
            brojac++;
        }
    }

    /*
     * Ako nema nijedne knjige iz te godine vraćamo nula jer bi inače imali
     * grešku dijeljenja s nulom.
     */
    if (brojac == 0)
    {
        return 0;
    }

    return suma / brojac;
}

/*
 * strcmp vraća 0 ako su nizovi znakova jednaki.
 * Usporedba je case-sensitive: "kuharica" != "Kuharica".
 */
int prebrojiPoZanru(KNJIGA *knjige, int brojKnjiga, const char *zanr)
{
    int brojac = 0;

    for (int i = 0; i < brojKnjiga; i++)
    {
        if (strcmp(knjige[i].zanr, zanr) == 0)
        {
            brojac++;
        }
    }

    return brojac;
}
