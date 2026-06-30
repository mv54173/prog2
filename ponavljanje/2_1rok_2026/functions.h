/* functions.h */
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct {
    char naziv[50];
    char kuhinja[50];
    int godinaObjave;
    char kategorija[30];
    int vrijemePripreme;   // u minutama
} Recept;

Recept *ucitajRecepte(const char *imeDatoteke, int *brojRecepata);
float izracunajProsjecnoVrijeme(Recept *recepti, int brojRecepata, const char *kategorija);
void pretraziPoNazivu(Recept *recepti, int brojRecepata, const char *naziv);
void ispisNajbrzihRecepata(Recept *recepti, int brojRecepata, int n);

#endif
