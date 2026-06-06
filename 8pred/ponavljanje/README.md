# Zadatak – Rekordna ljetna temperatura

Napisati program koji učitava `n` mjerenja temperatura s tipkovnice, zapisuje ih u binarnu datoteku `temperature.bin`, zatim ih čita natrag i pronalazi najvišu temperaturu zabilježenu u ljetnim mjesecima (lipanj, srpanj ili kolovoz — mjeseci 6, 7, 8).

Ako postoji takvo mjerenje, ispisati temperaturu i grad. Ako ne postoji, ispisati poruku.

Program treba biti podijeljen u tri datoteke:
- `functions.h` — definicija strukture i prototipovi
- `functions.c` — implementacije funkcija
- `main.c` — glavni program

Definirati strukturu mjerenje_t i implementirati funkcije:

1. `void zapisiTemperature(FILE *fileTemperature, int n)` — učitava n mjerenja sa stdin i zapisuje ih u binarnu datoteku
2. `mjerenje_t *rekordnaTemperatura(mjerenje_t temperature[], int n)` — vraća pokazivač na mjerenje s najvišom ljetnom temperaturom ili NULL

## Kompajliranje

```
gcc main.c functions.c -o ponavljanje
```

## Primjer

**Ulaz:**
```
5
Zagreb 3 12.5
Split 7 38.2
Osijek 6 35.1
Rijeka 8 31.0
Dubrovnik 1 8.3
```

**Izlaz:**
```
38.20 Split
```
