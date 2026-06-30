/*


Potrebno je dovršiti C program koji učitava recepte iz tekstualne datoteke.

Ime datoteke korisnik unosi s tipkovnice, zatim se unosi kategorija recepata za koju se želi 
izračunati prosječno vrijeme pripreme te naziv recepta koji se pretražuje i za njega 
se ispisuju sve informacije.

Svaki recept je zapisan u jednom retku tekstualne datoteke u sljedećem formatu:
broj_recepata;naziv;kuhinja;godinaObjave;kategorija;vrijemePripreme

Primjer sadržaja datoteke:
3
Margherita pizza;Talijanska;2023;Vegetarijansko;45
Beef stroganoff;Ruska;2021;90
Tiramisu;Talijanska;2022;Desert;30

Funkcija main() je djelomično dana te ju trebate nadopuniti — pogledati kojim se 
slijedom pozivaju funkcije koje trebate završiti.
Nadopuniti provjeru vezanu uz postojanje datoteke:

    -ako datoteka ne postoji, ispisati poruku: "Datoteka ne postoji.\n"
    -ako datoteka postoji, ali nema zapisa, ispisati poruku: "Datoteka ne sadrzi 
	podatke o receptima.\n"

Funkcije koje je potrebno napisati u functions.c
1 — ucitajRecepte()

    Prima ime datoteke uneseno s tipkovnice te pokazivač na cjelobrojnu varijablu 
	u koju je potrebno spremiti broj učitanih recepata.
    Funkcija čita datoteku redak po redak i za svaki redak parsira podatke u strukturu Recept.
    Povratna vrijednost je pokazivač na polje recepata zauzeto unutar funkcije 
	(obvezna provjera uspješno zauzete memorije).
    Ukoliko datoteka ne sadrži niti jedan ispravan redak, postaviti varijablu brojRecepata na 0.
    

2 — izracunajProsjecnoVrijeme()
    
    Prima pokazivač na polje recepata, broj recepata te naziv kategorije.
    Izračunati prosječno vrijeme pripreme recepata te kategorije i vratiti 
	ga povratno u main funkciju.
    Ukoliko nema recepata zadane kategorije, vratiti -1.0
    
3 — pretraziPoNazivu()

    Prima pokazivač na polje recepata, broj recepata te naziv recepta kojeg treba pronaći.
    Ukoliko je recept pronađen, ispisati poruku u obliku:
    printf("Recept: %s, Kuhinja: %s, Godina objave: %d, Kategorija: %s, 
	Vrijeme pripreme: %d min\n", .....);
    Ukoliko recept nije pronađen, ispisati poruku u obliku:
    printf("Recept s nazivom %s nije pronaden.\n", .....);
    
4 — ispisNajbrzihRecepata() (dodatna funkcija)

    Prima pokazivač na polje recepata, broj recepata te cijeli broj n.
    Ispisuje nazive i vremena pripreme n recepata s najkraćim vremenom pripreme, 
	poredanih uzlazno po vremenu pripreme.
    Ukoliko je n veći od ukupnog broja recepata, ispisati sve recepte.
    Ispis svakog recepta u obliku:
    printf("%d. %s (%d min)\n", redBroj, .....);

Deklaracije funkcija i struktura dani su u functions.h te ga nije potrebno mijenjati.

Pridržavati se organizacije projekta.
Svi pokušaji ispisivanja rezultata testova bez algoritamske logike će biti nulirani.
*/
/* main.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main() {
    char imeDatoteke[100];
    char kategorija[30];
    char naziv[50];
    int n;
    int brojRecepata = 0;

    printf("Unesite ime datoteke: ");
    scanf("%99s", imeDatoteke);

   
    FILE *provjera = fopen(imeDatoteke, "r");
    // TODO: Nadopuniti provjeru datoteke
    if(provjera == NULL){
    	printf("REZULTATI:\n");
    	printf("Datoteka ne postoji.\n");
    	return 0;
	}
	fclose(provjera);
    // Pokušaj otvaranja datoteke radi provjere postojanja
    

    Recept *recepti = ucitajRecepte(imeDatoteke, &brojRecepata);
    
  	// TODO: Nadopuniti provjeru da li ima zapisa u datoteci
    if(brojRecepata == 0 || recepti == NULL){
    	printf("REZULTATI:\n");
    	printf("Datoteka ne sadrzi podatke o receptima.\n");
    	return 0;
	}

    // prosječno vrijeme po kategoriji
    printf("Unesite kategoriju: ");
    scanf("%29s", kategorija);
    printf("REZULTATI:\n");
    float prosjek = izracunajProsjecnoVrijeme(recepti, brojRecepata, kategorija);
    if (prosjek < 0){
         
        printf("Nema recepata u kategoriji %s.\n", kategorija);
    }
    else{
         
         printf("Prosjecno vrijeme pripreme za kategoriju %s je %.1f min\n", kategorija, prosjek);

    }
       
    // pretraga po nazivu
    //printf("Unesite naziv recepta: ");
    scanf(" %49[^\n]", naziv);

    pretraziPoNazivu(recepti, brojRecepata, naziv);

    // ispis N najbrže recepata
    //printf("Unesite broj najbrze recepata za ispis: ");
    scanf("%d", &n);

    ispisNajbrzihRecepata(recepti, brojRecepata, n);

    free(recepti);
    return 0;
}
