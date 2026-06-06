# Zadatak 4 – Stipendisti

U datoteci `studenti.txt` nalaze se zapisi o studentima. U svakom retku nalazi se ime, prezime, godina studiranja i prosjek ocjena.

Student ima pravo na stipendiju ako vrijedi:
- `prosjek >= 4.00` i
- `godinaStudiranja <= 3` (preddiplomski studij, 1.–3. godina)

## Zadatak 4 (zad4.c)

Pronaći sve stipendiste i prepisati njihova imena i prezimena u novu datoteku `stipendija.txt`.

## Zadatak 4a (zad4a.c)

Pohraniti stipendiste u polje struktura, a zatim na kraj iste datoteke `studenti_append.txt` dopisati redak `******STIPENDISTI******` i ispod njega sva imena i prezimena stipendista. U datoteci je maksimalno 50 redaka.

---

## Primjer

**studenti.txt:**
```
Ivan Horvat 2 3.85
Ana Kovacevic 3 4.52
Marko Babic 1 3.12
Petra Novak 2 4.78
Luka Juric 4 3.67
Mia Kralj 3 4.21
```

**stipendija.txt** (nakon zad4):
```
Ana Kovacevic
Petra Novak
Mia Kralj
```

**studenti_append.txt** (nakon zad4a):
```
Ivan Horvat 2 3.85
Ana Kovacevic 3 4.52
Marko Babic 1 3.12
Petra Novak 2 4.78
Luka Juric 4 3.67
Mia Kralj 3 4.21

******STIPENDISTI******
Ana Kovacevic
Petra Novak
Mia Kralj
```
