#include <stdio.h>
#include <stdlib.h>

/*
 * Učitavamo redak iz datoteke pjesme koristeći fgets.
 * Pozivamo fputs dvaput za isti redak — svaki poziv upisuje cijeli
 * redak uključujući '\n' koji je fgets pročitao, pa dobivamo:
 *   redak\n
 *   redak\n
 */
void prepisiDvaput(FILE *pjesme, FILE *dnevnik)
{
    char redak[200 + 1];
    while (fgets(redak, 200 + 1, pjesme) != NULL)
    {
        fputs(redak, dnevnik);
        fputs(redak, dnevnik);
    }
}

/*
 * fopen("dnevnik.txt", "a") otvara datoteku za dopisivanje:
 *   - ako datoteka ne postoji, kreira je
 *   - ako postoji, sadržaj se ČUVA, novi podaci idu na kraj
 * Razlika od "w": mod "w" briše postojeći sadržaj pri otvaranju.
 *
 * Ako fopen za dnevnik vrati NULL, pjesme je već otvorena.
 * Moramo je zatvoriti prije izlaska — propuštanje fclose znači
 * curenje resursa (OS drži handle otvoren do kraja procesa).
 * Ovdje to nije napravljeno — u produkcijskom kodu treba dodati
 * fclose(pjesme) prije return 1 u drugoj provjeri.
 */
int main(void)
{
    FILE *pjesme = fopen("pjesme.txt", "r");
    if (NULL == pjesme)
    {
        return 1;
    }

    FILE *dnevnik = fopen("dnevnik.txt", "a");
    if (NULL == dnevnik)
    {
        fclose(pjesme);
        return 1;
    }

    prepisiDvaput(pjesme, dnevnik);

    fclose(dnevnik);
    fclose(pjesme);
    return 0;
}
