#ifndef HEADER_H
#define HEADER_H

typedef struct knjiga
{
    char *naslov;
    char *autor;
    int godina_izdanja;
    float ocjena;
    struct knjiga *nextNode;
} KNJIGA;

void inputBookData(KNJIGA *book); // Unos podataka za jednu knjigu

void deleteNodeSLList(KNJIGA **head, KNJIGA *target); // Brisanje jednog čvora iz liste

void obrisiKnjigeStarijeOd(KNJIGA **head, int godina); // Brisanje knjiga starijih od unesene godine

float averageRating(KNJIGA *);
KNJIGA *createSLList(void);
void traverseSLList(KNJIGA *);
KNJIGA *insertNewNodeSLList(KNJIGA *);

KNJIGA *deleteWholeSLList(KNJIGA *);

#endif