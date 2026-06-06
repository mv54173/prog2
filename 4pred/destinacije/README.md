# Zadatak – Turističke destinacije

Napraviti program koji unosi `n` turističkih destinacija. Za svaku destinaciju unose se naziv, država, cijena putovanja i ocjena.

Korisnik unosi budžet. Potrebno je pronaći destinaciju s najvećom ocjenom koja je unutar budžeta.

Ako takva destinacija postoji, ispisati je. Ako ne postoji, ispisati poruku da nema destinacije unutar budžeta.

Program treba biti podijeljen u tri datoteke:
- `functions.h` — definicija strukture `Destinacija` i prototipovi funkcija
- `functions.c` — implementacije funkcija
- `main.c` — glavni program

Funkcija `pronadiNajboljuDestinaciju` prima budžet kao parametar i vraća adresu najbolje destinacije ili `NULL`.

Definirati strukturu Destinacija i implementirati funkcije:

1. `void unesiDestinacije(Destinacija *destinacije, int n)` — učitava n destinacija
2. `Destinacija *pronadiNajboljuDestinaciju(Destinacija *destinacije, int n, float budzet)` — vraća pokazivač na najbolju ili NULL
3. `void ispisiDestinaciju(Destinacija *d)` — ispisuje podatke destinacije

Format ispisa: `naziv drzava cijena ocjena`

## Kompajliranje

```
gcc main.c functions.c -o destinacije
```

## Primjer 1 — postoji destinacija unutar budžeta

**Ulaz:**
```
3
Dubrovnik
Hrvatska
800.00
4.8
Pariz
Francuska
2000.00
4.9
Bec
Austrija
1200.00
4.5
1500
```

**Izlaz:**
```
REZULTATI:
Dubrovnik Hrvatska 800.00 4.80
```

## Primjer 2 — nema destinacije unutar budžeta

**Ulaz:**
```
2
New York
SAD
3500.00
4.7
Tokio
Japan
4200.00
4.9
500
```

**Izlaz:**
```
REZULTATI:
Nema destinacije unutar budzeta.
```