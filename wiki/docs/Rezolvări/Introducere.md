---
slug: /solve-intro
sidebar_position: 0
---

# Introducere

## 1 - Număr de Șiruri de Caractere Printabile 🏁

### Flag

`44`

### Rezolvare

Vezi codul de mai jos. Odată rulat cu comanda, va afișa *flag*-ul.

```python
#!/usr/bin/env python3

import string

from pwn import log

FILENAME = "../Exerciții/lyrics/lyrics.elf"
MIN_LENGTH = 15


def get_printable_transformation() -> str:
    # Creează un vector de 256 de elemente
    chars = 256 * ['\0']

    # Plasează elementele de interes
    for i in range(32, 127):
        chars[i] = chr(i)
    chars[ord('\n')] = "\n"
    chars[ord('\t')] = "\t"

    return "".join(chars).encode("utf-8")


def get_strings(filename: str, min_length: int) -> list:
    # Citește conținutul fișierului
    content = open(filename, "rb").read()

    # Transformă caracterele neprintabile în NULL, obținand astfel o listă
    all_strings = content.translate(
        get_printable_transformation()).split(b'\0')

    # Filtrează lista astfel încat să conțina numai șiruri de caractere cu
    # lungimea minimă
    all_strings = [
        string.decode("utf-8") for string in all_strings
        if len(string) >= min_length
    ]

    return all_strings


def main() -> None:
    # Obține șirurile de caractere printabile
    all_strings = get_strings(FILENAME, MIN_LENGTH)

    # Printează câte au fost găsite
    log.info("Numărul de șiruri de caractere printabile este {}.".format(
        len(all_strings)))

    # Printează șirurile de caractere
    log.info("Șirurile de caractere găsite sunt:")
    for string in all_strings:
        print("\t- {}".format(string))


if __name__ == "__main__":
    main()
```

Comportamentul lui este asemănător utilitarului `strings`, ce putea fi utilizat aici astfel: `strings lyrics.elf -n 15 | wc -l`.

## 2 - Tipuri de Șiruri de Caractere Printabile 💁

### Rezolvare

- Numele unor librării dinamice folosite în procesul de *linking*: `libc.so.6`
- Numele unor funcții importate: `sleep`
- Șiruri de caractere definite în program: `Cinco pasos y te perdon`
- Detalii despre procesul de compilare: `GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0`
- Numele unor simboluri definite în program: `main` (funcție), `lyrics` (variabilă), `.text` (secțiune)

## 3 - Număr de Simboluri 🏁

### Flag

`16`

### Rezolvare

Vezi codul de mai jos. Odată rulat cu comanda, va afișa *flag*-ul.

```python
#!/usr/bin/env python3

import string

from pwn import log, ELF

FILENAME = "lyrics.elf"
TEXT_SECTION = ".text"
EXECUTABLE_FLAG = 1


def get_symbols(filename: str) -> list:
    elf = ELF(filename, checksec=False)

    # Preia secțiunea .text
    text_section = [
        section for section in elf.sections if section.name == TEXT_SECTION
    ][0]

    # Preia segmentele executabile
    exe_segments = [
        segment for segment in elf.segments
        if segment.header.p_flags & EXECUTABLE_FLAG
    ]

    # Verifică dacă segmentele executabile gasite se află în sectiunea .text
    text_exe_segments = [
        segment for segment in exe_segments
        if segment.section_in_segment(text_section)
    ]

    symbols = []
    for segment in text_exe_segments:
        # Preia adresele de start și de început ale segmentului curent
        start_address = segment.header['p_vaddr']
        end_address = start_address + segment.header['p_filesz']

        # Preia simbolurile care se află în acest segment
        for key in elf.symbols.keys():
            address = elf.symbols[key]

            if (address >= start_address and address < end_address):
                symbols.append(key)

    return symbols


def main() -> None:
    all_symbols = get_symbols(FILENAME)

    # Printează câte au fost găsite
    log.info("Număr de simboluri gasite este {}.".format(len(all_symbols)))

    # Printează simbolurile
    log.info("Simbolurile găsite sunt:")
    for symbol in all_symbols:
        print("\t- {}".format(symbol))


if __name__ == "__main__":
    main()
```

Comportamentul lui este asemănător utilitarului `nm`, ce putea fi utilizat aici astfel: `nm lyrics.elf | egrep " (t|T) " | wc -l`.

## 4 - Proveniența Simbolurilor 💁

- `lyrics`, din zona de date, reprezintă o variabilă globală inițializată. Ca tip, era un vector de șiruri constante de caractere.
- `puts`, simbol nedefinit, este folosit la *runtime*, după ce *linkarea* dinamică a `libc` se produce.
- `main`, din zona de cod, reprezintă funcția principală a programului C.

## 5 - Automatizarea Analizei Dinamice cu `pwntools` 🏁

### Flag

`SI{CHECKING_THE_FLAG_BYTE_BY_BYTE}`

### Rezolvare

Simpla rulare a programului determina printarea unei erori ce specifică faptul că o librărie nu a fost găsită. Acest lucru se produce în ciuda faptului că librăria se află chiar în aceeași locație. Vom rula programul folosind prefixul `LD_LIBRARY_PATH=.`.

Se observă faptul că executabilul afișează numai acea porțiune din șirul de caractere dat ca parametru ce corespunde cu *flag*-ul. Modul de rezolvare constă în efectuarea unui atac de tip *brute-force*, caracter cu caracter.

Se începe cu primul caracter, testându-se toate posibilitățile. La încercarea la care programul afișează un caracter, atunci îl putem seta ca primul caracter din *flag*-ul construit progresiv și putem trece la următorul până când caracterul `}` (terminatorul de *flag*) apare.

O implementare este oferită mai jos.

```python
#!/usr/bin/env python3

import string

from pwn import log, context, process

FILENAME = "flag-checker.elf"
ENVIRONMENT = {'LD_LIBRARY_PATH': '.'}
CHARSET = string.ascii_uppercase + '_{}'
MAX_FLAG_LENGTH = 50
FLAG_END_CHAR = "}"


def main() -> None:
    # Dezactivează mesajele de jurnalizare ale pwntools
    context.log_level = "error"

    current_flag = ""
    for iteration in range(MAX_FLAG_LENGTH):
        for char in CHARSET:
            # Lansează un proces nou
            p = process([FILENAME, current_flag + char], env=ENVIRONMENT)

            # Preia ieșirea și verifică dacă ea produce vreo schimbare
            output = p.recvall()
            if len(output) > len(current_flag):
                current_flag = output.decode("utf-8")

                break

        if (FLAG_END_CHAR in current_flag):
            # Reactivează mesajele de jurnalizare ale pwntools
            context.log_level = "info"

            # Cum programul printează și alte caractere care nu sunt de interes,
            # printăm numai prima linie
            current_flag = current_flag.split("\n")[0]
            log.success("Flag-ul este {}.".format(current_flag))

            break


if __name__ == "__main__":
    main()
```

## 6 - Librării Dinamice 💁

Rulând comanda `ldd flag-checker.elf` observăm faptul că executabilul folosește o librărie dinamică numită `libcheckflag.so`.

Pentru a identifica modul în care se apelează funcții din ea, rulăm comanda `objdump --disassemble=main -M intel flag-checker.elf`, ce dezasamblează codul funcției `main` (argumentul `--disassemble`) în sintaxa specifică Intel (argumentul `-M`). Astfel, se ajunge la concluzia că libraria este încărcată în memorie prin apelul funcției `dlopen` și funcția din ea, `check_flag`, este referențiată printr-un apel `dlsym`.

## 7 - Dezasamblarea Programelor 💁

Cum *flag*-ul nu poate fi găsit în `strings`, putem rula comanda `objdump --disassemble=check_flag -M intel libcheckflag.so` pentru a decompila funcția `check_flag`. Observăm șiruri de octeți ce sunt mutate în regiștrii (de exemplu, `movabs rax,0x2a222429221a2832`) și care sunt transformate ulterior prin `xor`-are cu `0x61` pentru a obține caracterele cu care se face compararea intrării furnizate de utilizator.

În același timp, Ghidra reușește să ușureze vizualizarea operațiunilor efectuate, prin modul său de decompilare:

```
[..]
local_38 = 0x2a222429221a2832;
local_30 = 0x3e2429353e262f28;
local_28 = 0x3538233e26202d27;
local_20 = 0x3538233e38233e24;
local_18 = 0x3224;
local_16 = 0x1c;
local_3c = 0;
[..]
bVar1 = *(byte *)((long)&local_38 + (long)(int)local_3c) ^ 0x61;
if (bVar1 != *(byte *)(param_1 + (int)local_3c)) {
[..]
```

## 8 - Apeluri de Sistem 💁

Verificând ieșirea comenzii `strace python3 -m http.server 8080`, observăm secvența de apeluri de sistem prezentă mai jos:

```
socket(AF_INET, SOCK_STREAM|SOCK_CLOEXEC, IPPROTO_IP) = 3
[..]
bind(3, {sa_family=AF_INET, sin_port=htons(8080), sin_addr=inet_addr("0.0.0.0")}, 16) = 0
[..]
listen(3, 5)
```

## 9 - Conexiuni 💁

Rulându-se comanda `netstat -tlp`, se poate identifica rapid *socket*-ul TCP (opțiunea `-t`) în modul *listening* (opțiunea `-l`). Opțiunea `-p` este adăugată pentru a afișa și datele de identificare ale procesului (PID și executabil).

```
Proto Recv-Q Send-Q Local Address           Foreign Address         State       PID/Program name    
[..]
tcp        0      0 0.0.0.0:http-alt        0.0.0.0:*               LISTEN      53639/python3
```