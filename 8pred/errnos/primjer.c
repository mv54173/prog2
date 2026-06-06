#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/*
 * errno je globalna int varijabla definirana u <errno.h>.
 * Sistemski pozivi (fopen, fread, malloc...) postavljaju errno
 * na odgovarajući kod kad dođe do greške.
 * Vrijednost 0 znači "nema greške".
 *
 * VAŽNO: errno se ne resetira automatski — uvijek ga čitaj
 * odmah nakon poziva koji je pao, inače ga sljedeći poziv može prepisati.
 *
 * TRI NAČINA ISPISIVANJA GREŠKE:
 *
 * 1. perror("poruka")
 *    Ispisuje "poruka: <opis greške>" u stderr.
 *    Opis dolazi iz internog errno — ne trebaš mu ga eksplicitno proslijediti.
 *    Izlaz: "Dogodila se greška pri otvaranju datoteke: No such file or directory"
 *
 * 2. strerror(errno)
 *    Vraća char * s opisom greške za zadani kod.
 *    Korisno kad opis greške trebaš ugraditi u vlastitu poruku.
 *
 * 3. errno direktno
 *    Numerički kod greške — npr. 2 = ENOENT (No such file or directory).
 *    Rijetko koristan sam, ali dobar za dijagnostiku.
 *
 * exit(1) — odmah završava program s kodom 1 (greška).
 * Razlika od return: exit radi iz bilo koje funkcije, ne samo iz main.
 *
 * fprintf(stderr, ...) — piše u standardni tok grešaka (stderr).
 * Stderr i stdout su odvojeni tokovi — stderr se obično prikazuje u terminalu
 * čak i kad je stdout preusmjeren u datoteku.
 */
int main(void)
{
    FILE *fp = NULL;
    fp = fopen("nepostoji.txt", "r");

    if (NULL == fp)
    {
        perror("Dogodila se greška pri otvaranju datoteke");
        fprintf(stderr, "Pri otvaranju nepostoji.txt dobili smo %d %s",
                errno, strerror(errno));
        exit(1);
    }

    fclose(fp);

    return 0;
}
