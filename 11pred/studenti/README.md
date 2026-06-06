# Zadatak: Jednostruko povezana lista studenata

## Opis zadatka

Implementirati jednostruko povezanu listu (SLL) gdje svaki čvor predstavlja jednog studenta. Dio koda je već napisan — 
vaš zadatak je implementirati 4 funkcije označene u kodu. Funkcije koje treba implementirati:

1. `void unosPodataka(STUDENT *student)` - Učitava podatke s tipkovnice i sprema ih u predani čvor.

2. `float prosjekSvihStudenata(STUDENT *head)` - Prolazi kroz cijelu listu i vraća aritmetičku sredinu svih prosjeka studenata.

3. `void deleteNode(STUDENT **head, STUDENT *target)` - Briše točno određeni čvor iz liste i oslobađa svu njegovu memoriju.

 4. `STUDENT *searchList(STUDENT *head, int id)` - Traži čvor s određenim `id`-em i vraća pokazivač na njega (ili `NULL` ako ne postoji).

## Primjer ulaza / izlaza

**Ulaz:**
```
3
1 Ana Anić 4.5
2 Pero Perić 3.2
3 Iva Ivić 4.8
```

**Ispis liste:**
```
REZULTATI:
ID: 3 - Iva Ivić, prosjek: 4.80
ID: 2 - Pero Perić, prosjek: 3.20
ID: 1 - Ana Anić, prosjek: 4.50
Ukupan prosjek svih studenata je: 4.17
```
