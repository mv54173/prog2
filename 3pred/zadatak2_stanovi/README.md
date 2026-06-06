# Zadatak 2 – Stanovi

Napišite program koji upravlja evidencijom stanova za prodaju.
Za svaki stan potrebno je pohraniti sljedeće podatke:

| Polje              | Tip     | Opis                                  |
|--------------------|---------|---------------------------------------|
| `kvadratura`       | float   | Površina stana u m²                   |
| `cijena`           | float   | Ukupna cijena stana u EUR             |
| `adresa`           | string  | Adresa stana (max. 100 znakova)       |
| `energetski_razred`| char    | Energetski razred (A, B, C, D, ...)   |
| `klima`            | int     | 1 ako stan ima klimu, 0 ako nema      |

Prvo se unosi broj stanova `n` (mora biti između 1 i 99 uključivo; unos se ponavlja dok nije ispravan). Za svaki stan unose se redom: kvadratura, cijena, adresa, energetski razred, klima.

Implementirati sljedeće funkcije:

1. `popuniStanove(stan_t stanovi[], int n)`
Učitava podatke za `n` stanova s standardnog ulaza i pohranjuje ih u polje.

2. `ispisiPoKriteriju(stan_t stanovi[], int n)`
Ispisuje adresu i cijenu svih stanova koji zadovoljavaju **barem jedan** od sljedećih uvjeta:
- cijena po m² je **manja od 900 EUR/m²**, ili
- cijena po m² je **veća od 1100 EUR/m²** i stan **nema klimu**

Ako nijedan stan ne zadovoljava uvjete, ispisuje se poruka:
```
Niti jedan stan ne odgovara kriterijima.
```
3. `pronadjiNajveciStan(stan_t stanovi[], int n)`
Vraća pokazivač na stan s najvećom kvadraturom.

Program ispisuje:
```
REZULTATI:
<adresa>, <cijena>
...
Najveci stan je: <adresa>, <kvadratura>
```

## Primjer

**Ulaz:**
```
3
45.5
40000
Ulica Kralja Tomislava 5
B
1
72.0
75000
Ilica 22
C
0
30.0
32000
Savska 10
A
0
```

**Izlaz:**
```
REZULTATI:
Ulica Kralja Tomislava 5, 40000.00
Najveci stan je: Ilica 22, 72.00
```
