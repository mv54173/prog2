#ifndef mojHeader
#define mojHeader

/*
 * Struktura KNJIGA opisuje jedan zapis o knjizi.
 * Svako polje odgovara jednom podatku koji se čita iz binarne datoteke.
 */
typedef struct
{
    char naslov[50]; /* Naslov knjige (do 49 znakova + '\0') */
    int godina;      /* Godina izdanja */
    char autor[50];  /* Ime autora */
    char zanr[20];   /* Žanr (npr. "Kuharica", "Roman" ...) */
    int brojStr;     /* Broj stranica */
} KNJIGA;

KNJIGA *ucitajKnjige(const char *imeDatoteke, int *brojKnjiga);
float izracunajProsjecnBrojStr(KNJIGA *knjige, int brojKnjiga, int godina);
int prebrojiPoZanru(KNJIGA *knjige, int brojKnjiga, const char *zanr);

#endif // !mojHeader
