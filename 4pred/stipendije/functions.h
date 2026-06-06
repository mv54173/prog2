/*
 * Sprječava višestruko uključivanje iste header datoteke.
 * Problem bez guarda: ako dva .c fajla uključe isti .h, prevodilac
 * vidi istu typedef deklaraciju dvaput i javlja grešku.
 *
 * Kako radi:
 *   - #ifndef FUNCTIONS_H — "ako FUNCTIONS_H nije definiran..."
 *   - #define FUNCTIONS_H — "...definiraj ga (sad je definiran)"
 *   - #endif              — kraj uvjetnog bloka
 * Drugi put kad prevodilac naiđe na ovaj .h, FUNCTIONS_H već postoji
 * pa preskače cijeli sadržaj.
 */
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

/*
 * Struktura se definira u .h datoteci kako bi bila vidljiva u svim
 * .c datotekama koje uključuju ovaj header.
 * Definiranje u .c datoteci ograničilo bi vidljivost samo na tu datoteku.
 */
typedef struct
{
    char ime[50];
    char prezime[50];
    int bodovi;
    float prosjek;
} Student;

/*
 * Prototip govori prevodiocu potpis funkcije (povratni tip + parametri)
 * prije nego što vidi njenu definiciju u functions.c.
 * Bez prototipa, poziv funkcije iz main.c bio bi greška pri prevođenju.
 *
 * Pravilo: definicija je u .c datoteci, deklaracija (prototip) u .h datoteci.
 */
void unesiStudente(Student *studenti, int n);
Student *pronadiNajboljeg(Student *studenti, int n);
void ispisiStudenta(Student *s);

#endif
