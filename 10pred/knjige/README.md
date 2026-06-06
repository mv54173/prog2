Potrebno je dovršiti C program koji učitava sve knjige iz binarne datoteke, čije ime korisnik unosi s tipkovnice, zatim računa prosječni broj stranica knjiga prema godini izdanja te prebrojava knjige po žanru. Prva vrijednost koja je zapisana u tekstualnoj datoteci je broj knjiga, nakon čega su zapisani podaci o knjigama.

Primjer zapisa u datoteci:
> 
> brojKnjiga
> naslov godinaIzdavanja autor zanr brojStranica
> ...
> 

Implementirati sljedeće funkcije:
/*
prima ime datoteke koje je ranije uneseno s tipkovnice, a sadrži informacije o
knjigama te pokazivač na cjelobrojnu varijablu u koju je potrebno spremiti broj
knjiga koje su zapisane u datoteci (prva vrijednost). Povratna vrijednost je 
pokazivač na polje knjiga koje je zauzeto unutar funkcije i sadrži informacije
o svim knjigama. Ukoliko unutar datoteke nema informacija o broju knjiga, 
postaviti varijablu broj knjiga na -1.
*/
`KNJIGA *ucitajKnjige(const char *imeDatoteke, int *brojKnjiga);`

/*
prima pokazivač na polje knjiga, broj knjiga u polju te godinu 
izdavanja prema kojoj treba filtrirati knjige i ispisati koliko 
je prosječno stranica knjiga u toj godini
*/
`float izracunajProsjecnBrojStr(KNJIGA *knjige, int brojKnjiga, int godina);`

/*
prima pokazivač na polje knjiga, broj knjiga u polju te string
žanra prema kojem se treba filtrirati sve knjige te vratiti cijeli
broj koji govori koliko knjiga ima iz tog žanra
*/
`int prebrojiPoZanru(KNJIGA *knjige, int brojKnjiga, const char *zanr);`


Očekivani ispis za knjige.bin:
knjige.bin
7
Suncane Terase
108.571426
3
