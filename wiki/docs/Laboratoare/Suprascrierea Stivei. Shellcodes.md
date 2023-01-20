---
slug: /bof-shellcode
sidebar_position: 2
---

# Suprascrierea Stivei. Shellcodes

## Suport

<a href="https://github.com/iosifache/BinExpLabs/blob/main/labs/bof-shellcode/support/export.pdf">
    <img src="https://raw.githubusercontent.com/iosifache/BinExpLabs/main/labs/bof-shellcode/support/preview.png" width="400px" alt="Preview"/>
</a>

# Exerciții

### 1 - Suprascrierea Stivei 🏁

Analizați fișierul executabil `cookie_lover.elf` pentru a identifica funcționalitatea ce permite suprascrierea stivei și a o exploata pentru obținerea *flag*-ului.

### 2 - Crearea și Testarea unui *Shellcode* 💁

Rolul acestei sarcini este de a observa modul în care un *shellcode* este creat, compilat și rulat într-un mediu controlat (spre deosebire de execuția lui în cadrului unui *exploit*), cu ajutorul a două metode. Efectuați pașii de mai jos:
1. Vizualizați conținutul fișierului `shellcode.S`. Care este funcționalitatea lui?
2. Rulați comanda `make get_shellcode`. Ce reprezintă octeții returnați?
3. Plasați șirul de octeți obținut anterior în fișierul `execution_from_stack.c`. Rulați comanda `make execution_from_stack.elf` și, ulterior, executați programul. Folosiți instrumentele prezentate în primul laborator pentru a înțelege cum se rulează *shellcode*-ul.
4. Plasați șirul de octeți obținut anterior în fișierul `execution_with_mprotect.c`. Rulați comanda `make execution_with_mprotect.elf` și, ulterior, executați programul. Folosiți instrumentele prezentate în primul laborator pentru a înțelege cum se rulează *shellcode*-ul.

### 3 - Folosirea Apelului de Sistem `execve` în *Shellcode* 💁

Folosind Ghidra, identificați vulnerabilitatea executabilului ultimului exercițiu din al doilea laborator, `essay-checker.elf`. Căutați un *shellcode* pe *website*-ul [shell-storm.org](http://shell-storm.org/shellcode/) care să lanseze în execuție `/bin/bash` sau `/bin/sh`. Combinând aceste două informații și utilizând simbolul `helper`, creați un *payload* care să exploateze executabilul pentru lansarea în execuție a unui *shell*.