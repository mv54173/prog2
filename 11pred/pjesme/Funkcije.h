#ifndef HEADER_H
#define HEADER_H

typedef struct
{
    char *naslov;
    char *izvodjac;
    int trajanje_s;
    float ocjena;
} PJESMA;

typedef struct node
{
    PJESMA song;
    struct node *nextNode;
} NODE;

/* za implementirati */
void inputSongData(PJESMA *s);
void deleteNodeSLList(NODE **head, NODE *target);
void obrisiPjesmePoOcjeni(NODE **head, float minOcjena);

/* ne mijenjati */
float averageRating(NODE *head);
NODE *createSLList(void);
NODE *insertNewNodeSLList(NODE *head);
void traverseSLList(NODE *node);
NODE *deleteWholeSLList(NODE *head);

#endif
