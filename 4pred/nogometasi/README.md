# Zadatak – Nogometaši

Napraviti program koji unosi `n` nogometaša. Za svakog igrača unose se ime, klub, broj odigranih utakmica i broj postignutih golova.

Potrebno je pronaći igrača koji ima najbolji omjer golova po utakmici (`golovi / utakmice`). U obzir ulaze samo igrači koji su odigrali barem 5 utakmica.

Ako postoji igrač koji zadovoljava uvjet, ispisati ga. Ako ne postoji, ispisati poruku da nema igrača s dovoljno utakmica.

Program treba biti podijeljen u tri datoteke:
- `functions.h` — definicija strukture `Igrac` i prototipovi funkcija
- `functions.c` — implementacije funkcija
- `main.c` — glavni program

Funkcija `pronadiNajboljegIgraca` mora vratiti adresu najboljeg igrača. Ako takav igrač ne postoji, funkcija vraća `NULL`.

Definirati strukturu Igrav i implementirati funkcije:

1. `void unesiIgrace(Igrac *igraci, int n)` — učitava n igrača
2. `Igrac *pronadiNajboljegIgraca(Igrac *igraci, int n)` — vraća pokazivač na najboljeg ili NULL
3. `void ispisiIgraca(Igrac *i)` — ispisuje podatke igrača uključujući omjer

Format ispisa: `ime klub utakmice golovi omjer`

## Kompajliranje

```
gcc main.c functions.c -o nogometasi
```

## Primjer 1 — postoji pobjednik

**Ulaz:**
```
4
Messi
Barcelona
10
8
Ronaldo
Madrid
3
2
Suarez
Liverpool
7
5
Neymar
PSG
6
6
```
**Izlaz:**
```
REZULTATI:
Neymar PSG 6 6 1.00
```

## Primjer 2 — nema igrača s dovoljno utakmica

**Ulaz:**
```
2
Benzema
Real Madrid
4
3
Kane
Spurs
2
1
```

**Izlaz:**
```
REZULTATI:
Nema igraca s dovoljno utakmica.
```