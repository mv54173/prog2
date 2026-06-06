# Zadatak – Uklanjanje višestrukih razmaka

Napisati program koji kopira sadržaj datoteke `ulaz.txt` u datoteku `izlaz.txt` tako da se više uzastopnih razmaka zamijeni točno jednim razmakom. Pojedinačni razmaci, slova, brojevi i ostali znakovi prepisuju se nepromijenjeni. Implementirati funkciju

1. `void pretvorba(FILE *pUlaz, FILE *pIzlaz)` — čita znakove iz ulazne datoteke i piše u izlaznu, preskačući višak razmaka

## Primjer

**ulaz.txt:**
```
Ovo  je    primjer   s   visak   razmaka.
Novi    redak    takodjer    radi.
```

**izlaz.txt:**
```
Ovo je primjer s visak razmaka.
Novi redak takodjer radi.
```
