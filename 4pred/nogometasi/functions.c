/*
 * #include "functions.h" — navodnici znače: traži datoteku RELATIVNO
 * od trenutnog direktorija (vlastite datoteke projekta).
 * #include <stdio.h>     — kutne zagrade znače: traži u sistemskim
 * direktorijima prevoditelja (standardne biblioteke).
 */
#include <stdio.h>
#include <string.h>
#include "functions.h"

/*
 * fgets(dest, max_znakova, stdin) čita cijelu liniju uključujući razmake,
 * što omogućuje višerječna imena i klubove (npr. "Real Madrid", "Van Dijk").
 * fgets uključuje '\n' na kraju pročitanog stringa.
 * strlen(s) - 1 je indeks tog '\n' — zamjenjujemo ga s '\0'.
 *
 * REDOSLJED UNOSA po igraču:
 *   1. ime   (fgets — može imati razmake)
 *   2. klub  (fgets — može imati razmake)
 *   3. utakmice (scanf "%d" + getchar za čišćenje '\n')
 *   4. golovi   (scanf "%d" + getchar za čišćenje '\n')
 *
 */
void unesiIgrace(Igrac *igraci, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        fgets(igraci[i].ime, 50, stdin);
        igraci[i].ime[strlen(igraci[i].ime) - 1] = '\0';

        fgets(igraci[i].klub, 50, stdin);
        igraci[i].klub[strlen(igraci[i].klub) - 1] = '\0';

        scanf("%d", &igraci[i].utakmice);
        getchar();

        scanf("%d", &igraci[i].golovi);
        getchar();
    }
}

/*
 * golovi i utakmice su int. Bez casta:
 *   5 / 10 = 0  (cjelobrojna dijeljenje, decimalni dio se odbacuje)
 * S castom na float:
 *   (float)5 / 10 = 0.5  (jedan operand je float → rezultat je float)
 *
 * Cast se piše samo na jedan operand — C automatski "promovirá"
 * drugi operand u float (implicitna konverzija).
 *
 * Za razliku od traženja maksimuma po cijelo-brojnom polju (bodovi),
 * ovdje uspoređujemo izračunatu vrijednost (omjer). Zbog toga pamtimo
 * i posebnu varijablu najboljjiOmjer uz pokazivač na najboljeg igrača.
 *
 * Inicijaliziramo pokazivač na NULL — posebna vrijednost koja znači
 * "pokazivač ne pokazuje ni na što valjano".
 * Uvjet NULL == najbolji || omjer > najboljiiOmjer:
 *   - prvi put uvijek ulazimo (nije još pronađen nijedan kandidat)
 *   - svaki idući put ulazimo samo ako je novi omjer bolji
 */
Igrac *pronadiNajboljegIgraca(Igrac *igraci, int n)
{
    Igrac *najbolji = NULL;
    float najboljiiOmjer = 0.0f;
    int i;
    for (i = 0; i < n; i++)
    {
        if (igraci[i].utakmice >= 5)
        {
            float omjer = (float)igraci[i].golovi / igraci[i].utakmice;
            if (najbolji == NULL || omjer > najboljiiOmjer)
            {
                najbolji = &igraci[i];
                najboljiiOmjer = omjer;
            }
        }
    }
    return najbolji;
}

/*
 * Omjer se ponovo računa pri ispisu jer ga struktura Igrac ne pohranjuje —
 * to je izvedena vrijednost (golovi / utakmice), ne izvorni podatak.
 *
 * Funkcija prima Igrac * (pokazivač) — pristupamo članovima s ->.
 * %.2f ispisuje float na 2 decimalna mjesta.
 */
void ispisiIgraca(Igrac *i)
{
    float omjer = (float)i->golovi / i->utakmice;
    printf("%s %s %d %d %.2f\n", i->ime, i->klub, i->utakmice, i->golovi, omjer);
}
