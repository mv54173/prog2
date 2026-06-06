/*
 * Sprječava višestruko uključivanje iste header datoteke.
 */
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

/*
 * <stdio.h> je potreban u header datoteci jer prototip zapisiTemperature
 * koristi tip FILE * — bez #include <stdio.h> prevodilac ne bi znao što je FILE.
 * Općenito: sve što koristiš u prototipima mora biti deklarirano u .h datoteci.
 */
#include <stdio.h>
#include <stdlib.h>

/*
 * Struktura se definira u .h datoteci kako bi bila vidljiva u svim
 * .c datotekama koje uključuju ovaj header.
 */
typedef struct
{
    char grad[30];
    int mjesec;
    float temperatura;
} mjerenje_t;

mjerenje_t *rekordnaTemperatura(mjerenje_t temperature[], int n);
void zapisiTemperature(FILE *fileTemperature, int n);

#endif
