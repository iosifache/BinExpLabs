# CTF

## Descriere

CTF-ul evaluează practic cunoștințele deprinse la aceste laboratoare. El se desfășoară pe o durată de 7 zile.

## Componență

CTF-ul este format din 4 probleme ce pot fi rezolvate individual (fără vreo dependență între ele). Fiecare problemă presupune exploatarea unui executabil conform descrierilor individuale de mai jos.

### `improved_flag_checker`

- **Scop**: Deducerea conținutului fișierului `flag.txt` cu ajutorul executabilului oferit
- **Puncte**: `2`

### `multifunctional`

- **Scop**: Deducerea conținutului fișierului `flag.txt` cu ajutorul executabilului oferit
- **Puncte**: `3`

### `shellcode_sandbox`

- **Scop**: Deducerea conținutului fișierului `flag.txt` cu ajutorul executabilului oferit
- **Puncte**: `2`

### `classic`

- **Scop**: Obținerea unui *shell*
- **Puncte**: `2`
- **Cerințe**: Rularea în prealabil a comenzii `echo 0 | sudo tee /proc/sys/kernel/randomize_va_space` pentru dezactivarea ASLR-ului

## Trimiterea Rezolvărilor

După rezolvarea exercițiilor, se va crea o arhivă ZIP numită `GRUPĂ_NUME_PRENUME.zip`, unde `GRUPĂ` este indicativul grupei de studiu (de exemplu, `C124`). Ea va fi încărcată pe Moodle.

Arhiva trebuie să respecte următoarea structură:

```
.
├── classic
│   ├── WRITEUP.md               Fișier de detaliere a rezolvării
│   └── ...                      Alte fișiere care demonstrează rezolvarea
├── improved_flag_checker
│   ├── WRITEUP.md               Fișier de detaliere a rezolvării
│   └── ...                      Alte fișiere care demonstrează rezolvarea
├── multifunctional
│   ├── WRITEUP.md               Fișier de detaliere a rezolvării
│   └── ...                      Alte fișiere care demonstrează rezolvarea
└── multifunctional
    ├── WRITEUP.md               Fișier de detaliere a rezolvării
    └── ...                      Alte fișiere care demonstrează rezolvarea
```

`WRITEUP.md` reprezintă un fișier Markdown în care se detaliază modalitatea în care problema a fost rezolvată. El trebuie să respecte structura fișierului [`WRITEUP.md`](WRITEUP.md) din acest director.

## Corectare

Corectarea va presupune notarea pe o scară de la 1 la 10 a fiecărei probleme. În final, se va face o medie ponderată, ținându-se cont de punctele oferite pentru fiecare problemă.

În cazul în care fișierul de detaliere a rezolvării unei probleme nu este trimis, problema respectivă nu va fi corectată și punctată.