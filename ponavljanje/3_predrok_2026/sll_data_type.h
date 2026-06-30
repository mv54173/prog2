#ifndef SLL_DATA_TYPE_H
#define SLL_DATA_TYPE_H

typedef struct {
    char proizvodjac[20];
    char model[20];
    int ramGB;
    double cijena;
} COMPUTER;

typedef struct sllist {
    COMPUTER data;
    struct sllist *nextNode;
} SLLNODE;

#endif //SLL_DATA_TYPE_H