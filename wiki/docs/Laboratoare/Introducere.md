---
slug: /intro
sidebar_position: 0
---

# Introducere

## Suport

<a href="https://github.com/iosifache/BinExpLabs/blob/main/labs/intro/support/export.pdf">
    <img src="https://raw.githubusercontent.com/iosifache/BinExpLabs/main/labs/intro/support/preview.png" width="400px" alt="Preview"/>
</a>

## Exerciții

<a href="https://github.com/iosifache/BinExpLabs/releases/download/v1.1/intro.zip">
    <img src="https://img.shields.io/badge/Release%20cu%20Fișierele%20Necesare-Descarcă-blue?style=for-the-badge&logo=github"/>
</a>

### 1 - Număr de Șiruri de Caractere Printabile 🏁

Câte șiruri de caractere cu lungime mai mare de 10 există în executabilul `lyrics.elf`?

*Flag*-ul este în format `[0-9]*`.

### 2 - Tipuri de Șiruri de Caractere Printabile 💁

De unde provin șirurile de caractere găsite în executabilul `lyrics.elf`?

### 3 - Număr de Simboluri 🏁

Identificați numărul de simboluri din segmentul de cod al executabilului `lyrics.elf`.

*Flag*-ul este în format `[0-9]*`.

### 4 - Proveniența Simbolurilor 💁

Judecând după tipurile pe care comanda `nm` le produce asupra executabilului `lyrics.elf`, presupuneți de unde vin simbolurile `lyrics`, `puts` și `main`.

### 5 - Automatizarea Analizei Dinamice cu `pwntools` 🏁

Rulați programul `flag-checker.elf`. Cum operațiunile ce trebuiesc efectuate sunt prea multe, automatizați tot procesul de identificare a *flag*-ului cu ajutorul librăriei `pwntools`.

*Flag*-ul este în format `SI{[A-Z_]*}`.

### 6 - Librării Dinamice 💁

Identificați modalitatea prin care executabilul `flag-checker.elf` apelează funcția de verificare a *flag*-ului.

### 7 - Dezasamblarea Programelor 💁

Puteți identifica *flag*-ul de la sarcina de mai sus prin rularea comenzii `strings` asupra programului?

Dacă nu, vă puteți da seama de ce din dezasamblarea funcției `check_flag` din librăria `libcheckflag.so`? Încercați aceeași tip de dezasamblare în Ghidra, eventual folosind funcția de decompilare.

### 8 - Apeluri de Sistem 💁

Comanda `python3 -m http.server 8080` poate fi utilizată pentru crearea rapidă a unui server web pe portul 8080. Folosiți comanda `strace` pentru a identifica apelurile de sistem specifice creării unui *socket* și a acceptării conexiunilor pe el.

### 9 - Conexiuni 💁

Folosind aceeași comandă ca la exercițiul anterior, identificați portul deschis folosind comanda `netstat`. Puteți filtra în funcție de starea în care se află *socket*-ul și de protocolul folosit.
