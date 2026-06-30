/*

Napisati funkcije za rad s jednostruko povezanim popisom knjiga.  
Svaka knjiga sadrži sljedeće podatke:

    - naslov (dinamički alocirani niz znakova)
    - autor (dinamički alocirani niz znakova)
    - godina izdanja (cijeli broj)
    - ocjena čitatelja (realni broj)
    - pokazivač na sljedeći čvor u listi

Vaš zadatak je implementirati sljedeće tri funkcije:

    [1.] void inputBookData(KNJIGA* book);
         – Funkcija prima pokazivač na jednu knjigu te unosi njegove podatke s tipkovnice:
           naslov, autor, godina izdanja, ocjena čitatelja
           Za tekstualne podatke potrebno je prethodno dinamički alocirati memoriju.

    [2.] void deleteNodeSLList(KNJIGA** head, KNJIGA* target);
         – Funkcija briše jedan zadani čvor iz liste. Ako je riječ o prvom čvoru, ažurira pokazivač na glavu liste.
           Oslobađa zauzetu memoriju za cijeli uređaj, uključujući stringove.

    [3.] void obrisiKnjigeStarijeOd(KNJIGA** head, int godina);
         – Funkcija prolazi kroz cijelu listu i briše sve knjige čija je godina izdanja manja od zadane vrijednosti.
           Za svaki obrisani čvor potrebno je osloboditi zauzetu memoriju (struktura + stringovi).
           Funkcija koristi deleteNodeSLList za brisanje pojedinačnih čvorova.
         - Paziti ako obriše sve iz liste!

U potpunosti rukovati memorijom za sve varijable za koje je to nužno.

Ostale funkcije i struktura KNJIGA su već implementirane i dane u projektu:

    1. KNJIGA* createSLList(void);
       – Stvara prvi čvor liste i poziva funkciju za unos podataka.

    2. KNJIGA* insertNewNodeSLList(KNJIGA* head);
       – Stvara novi čvor, unosi podatke i umeće ga na početak postojeće liste.

    3. void traverseSLList(KNJIGA* head);
       – Ispisuje sve uređaje iz liste redom, s prikazom marke, modela, godine i ocjene.

    4. float averageRating(KNJIGA* head);
       – Vraća prosječnu ocjenu svih uređaja u listi.

    5. KNJIGA* deleteWholeSLList(KNJIGA* head);
       – Briše cijelu listu, čvor po čvor, i oslobađa sav zauzeti prostor.
    
    6. float averageRating(KNJIGA* head);
       – Vraća prosječnu ocjenu svih knjiga u listi.
         Koristi se za provjeru ispravnosti podataka nakon unosa ili brisanja.


!!!!! VAŽNO !!!!
Sva predana rješenja bit će dodatno evaluirana nakon predaje.
Za ostvarenje punog broja bodova, rješenje mora ispravno implementirati 
sve tražene funkcionalnosti bez grešaka u logici ili radu s memorijom.

Djelomično riješeni zadaci mogu ostvariti djelomičan broj bodova, ovisno o kvaliteti implementacije i stabilnosti programa.

Rješenja s ozbiljnim pogreškama (npr. curenje memorije, rušenje programa, neispravno brisanje 
ili povezivanje čvorova) neće ostvariti maksimalan broj bodova, 
čak i ako je dio funkcionalnosti djelomično prisutan.
*/

#include <stdio.h>
#include <stdlib.h>
#include "Funkcije.h"

int main() {
    int n, i, godina;
    KNJIGA *headNode = NULL;
    

    printf("Koliko knjiga želiš unijeti? ");
    scanf("%d", &n);

    headNode = createSLList();  // unos prve knjige

    for (i = 0; i < n - 1; i++) {
        headNode = insertNewNodeSLList(headNode);  // unos preostalih knjiga
    }

    printf("\nSve unesene knjige :\n");
    traverseSLList(headNode);
    printf("Prosječna ocjena svih knjiga: %.2f\n", averageRating(headNode));

    printf("\nUnesi godinu – sve knjige starije od te godine bit će obrisane: ");
    scanf("%d", &godina);
    
    printf("REZULTATI:\n");
    obrisiKnjigeStarijeOd(&headNode, godina);

    printf("Nakon brisanja:\n");
    traverseSLList(headNode);
    printf("Prosječna ocjena preostalih knjiga: %.2f\n", averageRating(headNode));

    headNode = deleteWholeSLList(headNode);  // čišćenje memorije

    return 0;
}

