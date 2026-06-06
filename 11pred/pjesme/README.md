# Pjesme — jednostruko povezana lista

## Zadatak

Implementirati program koji upravlja playlistom pjesama koristeći **jednostruko povezanu listu (SLL)**.

Svaka pjesma (`PJESMA`) sadrži:
- `naslov` — dinamički alocirani string
- `izvodjac` — dinamički alocirani string
- `trajanje_s` — trajanje u sekundama (int)
- `ocjena` — ocjena pjesme (float)

Korisnik unosi broj pjesama, a zatim podatke za svaku. Nakon unosa, program ispisuje sve pjesme i prosječnu ocjenu. Zatim korisnik unosi prag ocjene, brišu se sve pjesme **čija je ocjena >= pragu**, i ispisuju se preostale pjesme s novom prosječnom ocjenom.

## Funkcije za implementaciju

```c
/*
 * Briše jedan čvor iz liste i oslobađa svu njegovu memoriju.
 * Ažurira *head ako je obrisan prvi čvor.
 */
void deleteNodeSLList(NODE **head, NODE *target);

/*
 * Prolazi kroz listu i briše sve pjesme čija je ocjena >= minOcjena.
 * Koristi deleteNodeSLList za svaki pronađeni čvor.
 */
void obrisiPjesmePoOcjeni(NODE **head, float minOcjena);
```

## Primjer rada programa

```
Koliko pjesama zelis unijeti? 3
Bohemian Rhapsody
Queen
354
9.5
Smells Like Teen Spirit
Nirvana
301
8.0
Hotel California
Eagles
391
7.5

Svi uneseni zapisi (SLL):
Naslov: Hotel California, Izvodjac: Eagles, Trajanje: 391 s, Ocjena: 7.50
Naslov: Smells Like Teen Spirit, Izvodjac: Nirvana, Trajanje: 301 s, Ocjena: 8.00
Naslov: Bohemian Rhapsody, Izvodjac: Queen, Trajanje: 354 s, Ocjena: 9.50
Prosjecna ocjena: 8.33

Unesi minimalnu ocjenu (pjesme ispod toga brisemo): 8.5
REZULTATI:
Nakon brisanja:
Naslov: Smells Like Teen Spirit, Izvodjac: Nirvana, Trajanje: 301 s, Ocjena: 8.00
Naslov: Hotel California, Izvodjac: Eagles, Trajanje: 391 s, Ocjena: 7.50
Prosjecna ocjena preostalih pjesama: 7.75
```

> **Napomena:** `insertNewNodeSLList` umeće nove čvorove na **početak** liste, pa je redoslijed ispisa obrnut od unosa.
