# Zadatak – Trokuti i točke u 3D prostoru

Napišite program koji radi s točkama i trokutima u trodimenzionalnom prostoru.

Napraviti sljedeće strukture:

- Točka u 3d prostoru:

| Polje | Tip | Opis              |
|-------|-----|-------------------|
| `x`   | int | x-koordinata      |
| `y`   | int | y-koordinata      |
| `z`   | int | z-koordinata      |

- Trokut:

| Polje | Tip       | Opis            |
|-------|-----------|-----------------|
| `A`   | point_t * | pokazivač na prvu točku  |
| `B`   | point_t * | pokazivač na drugu točku |
| `C`   | point_t * | pokazivač na treću točku |

Unosi se broj točaka `m` i broj trokuta `n`. U sljedećih `m` redaka upisuju se koordinate svake točke: `x y z`. Zatim u `n` redaka, definiraju se trokuti kao tri indeksa točaka iz gore unesenog polja: `iA iB iC`

Implementirati sljedeće funkcije:

1. `unesiTocke(point_t *tocke, int m)`
Učitava `m` točaka s standardnog ulaza.

2. `unesiTrokute(triangle_t *trokuti, int n, point_t *tocke)`
Učitava `n` trokuta. Za svaki trokut unose se indeksi točaka iz polja `tocke`. Svaki trokut pohranjuje pokazivače na odgovarajuće točke (ne kopije).

3. `int equalPoints(point_t *p1, point_t *p2)`
Vraća `1` ako su dvije točke jednake u svim koordinatama, inače `0`.

4. `printTriangles(triangle_t *trokuti, int n)`
Ispisuje sve trokute čije su sve tri točke međusobno različite (valjani trokuti).  
Format ispisa po trokutu:
```
Triangle <i>: (<x>, <y>, <z>), (<x>, <y>, <z>), (<x>, <y>, <z>)
```

5. `float izracunajDuljinu(point_t *p1, point_t *p2)`
Vraća euklidsku udaljenost između dvije točke u 3D prostoru:
$$d = \sqrt{(x_2-x_1)^2 + (y_2-y_1)^2 + (z_2-z_1)^2}$$

6. `float izracunajOpseg(triangle_t *trokut)`
Vraća opseg trokuta (zbroj duljina svih triju stranica).

7. `triangle_t *maxOpseg(triangle_t *trokuti, int n)`
Vraća pokazivač na trokut s najvećim opsegom.

Program ispisuje
```
Triangle <i>: (<x>, <y>, <z>), (<x>, <y>, <z>), (<x>, <y>, <z>)
...
Largest triangle: (<x>, <y>, <z>), (<x>, <y>, <z>), (<x>, <y>, <z>)
```
Prvo se ispisuju svi valjani trokuti, zatim trokut s najvećim opsegom (bez indeksa).

## Primjer

**Ulaz:**
```
4
3
0 0 0
1 0 0
0 1 0
0 0 1
0 1 2
1 2 3
0 0 0
```

**Izlaz:**
```
Triangle 0: (0, 0, 0), (1, 0, 0), (0, 1, 0)
Triangle 1: (1, 0, 0), (0, 1, 0), (0, 0, 1)
Largest triangle: (1, 0, 0), (0, 1, 0), (0, 0, 1)
```
