#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*
 * ERRNO KONSTANTE — IMENOVANI KODOVI GREŠAKA
 * --------------------------------------------
 * Umjesto magičnih brojeva (2, 13...) koristimo simboličke konstante iz <errno.h>:
 *   ENOENT  — 2  — No such file or directory (datoteka ne postoji)
 *   EACCES  — 13 — Permission denied (zabranjen pristup)
 *
 * Switch na errno omogućuje drugačiju reakciju na svaku vrstu greške.
 * Redosljed provjere: case 0 (uspjeh) → specifične greške → default (sve ostalo).
 *
 */
int main(void)
{
    FILE *fp = fopen("pr.bin", "rb");

    switch (errno)
    {
    case 0:
        printf("otvorio sam datoteku");
        break;
    case ENOENT:
        fprintf(stderr, "Datoteka pr.bin ne postoji %d", errno);
        exit(1);
    case EACCES:
        perror("Ne smijem otvarati"); /* ispisuje "Ne smijem otvarati: Permission denied" */
        exit(1);
    default:
        fprintf(stderr, "Greška %d %s", errno, strerror(errno));
        exit(1);
    }

    fclose(fp);
    return 0;
}
