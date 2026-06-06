# Zadatak – Stipendije

Napraviti program koji unosi `n` studenata. Za svakog studenta unose se ime, prezime, broj bodova iz ispita i prosjek ocjena.

Potrebno je pronaći studenta koji ima pravo na stipendiju i ima najveći broj bodova. Student ima pravo na stipendiju ako ima `bodovi >= 80` i `prosjek >= 4.0`.
Ako postoji takav student, ispisati njegove podatke. Ako ne postoji, ispisati poruku da nijedan student ne zadovoljava uvjet.

Program treba biti podijeljen u tri datoteke:
- `functions.h` — definicija strukture `Student` i prototipovi funkcija
- `functions.c` — implementacije funkcija
- `main.c` — glavni program

Funkcija `pronadiNajboljeg` mora vratiti adresu najboljeg studenta za stipendiju. Ako takav student ne postoji, funkcija vraća `NULL`.

Definirati strukturu podataka Student i implementirati funkcije:

1. `void unesiStudente(Student *studenti, int n)` — učitava n studenata
2. `Student *pronadiNajboljeg(Student *studenti, int n)` — vraća pokazivač na najboljeg ili NULL
3. `void ispisiStudenta(Student *s)` — ispisuje podatke jednog studenta

## Kompajliranje

```
gcc main.c functions.c -o stipendije
```

## Primjer 1 — postoji dobitnik

**Ulaz:**
```
3
Ana Anic 85 4.5
Ivan Ivic 72 4.8
Pero Peric 90 3.9
```

**Izlaz:**
```
REZULTATI:
Ana Anic 85 4.50
```

## Primjer 2 — nema dobitnika

**Ulaz:**
```
2
Maja Majic 79 4.9
Luka Lukic 95 3.5
```

**Izlaz:**
```
REZULTATI:
Nijedan student ne zadovoljava uvjet.
```