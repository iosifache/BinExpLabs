---
slug: /solve-vuln
sidebar_position: 1
---

# Tehnici de Descoperire a Vulnerabilităților

### 1 - Fuzzing cu AFL++ 💁

După crearea *container*-ului cu AFL++ (conform cu ghidului de setare a mediului de lucru), putem rula un terminal în interiorul acestuia cu ajutorul comenzilor `docker container ls --all` (pentru identificarea numelui *container*-ului, notat `<container_name>`) și `docker exec --interactive --tty <container_name> /bin/bash`. În cazul în care stația de lucru a fost repornită de la setarea mediului de lucru până în acest moment, ultima comandă trebuie precedată de una de pornire a *container*-ului, mai exact `docker start <container_name>`.

Primul pas indicat în enunț este de a afla o intrare validă (ce nu produce un *crash*) a programului. Cel din urmă este rulat pentru a identifica ce parametrii necesită:

```bash
$ /src/essay-checker.elf
Usage: /src/essay-checker.elf ESSAY_TXT_FILENAME PARAGRAPH_COUNT
```

Sarcina este astfel directă, fiind nevoie numai de crearea unui fișier `input.txt`, cu un conținut de dimensiune mică (de exemplu, "*a*").

```bash
$ /src/essay-checker.elf /tmp/inputs/input.txt 2
Patience is bitter, but its fruit is sweet. - Aristotle
$ /src/essay-checker.elf /tmp/inputs/input.txt 1
Horaaay, you finish your essay!
```

Înainte de pornirea campaniei de *fuzzing*, anumite condiții trebuiesc îndeplinite. Acestea sunt impuse implicit de argumentele necesare execuției:
- `-i <input_folder>`: `<input_folder>` este un director cu intrări valide ale programului. Sunt suficiente crearea unui folder nou (notat cu `<input_folder>`) și mutarea fișierului generat anterior, `input.txt`, în acesta.
- `-o <output_folder>`: `<output_folder>` este un folder nou creat în care vor fi plasate automat rezultatele campaniei de *fuzzing*.
- `-Q`: *Flag*-ul activează emularea cu QEMU.

Pentru începerea campaniei, comanda este `afl-fuzz -i <input_folder> -o <output_folder> -Q -- <executable> @@ 1`. `@@` joacă rol de *placeholder* pentru numele fișierului, fiind înlocuit automat de AFL++ în timpul sesiunii de *fuzzing* cu numele fișierului generat.

```bash
   american fuzzy lop ++4.05a {default} (/src/essay-checker.elf) [fast]
┌─ process timing ────────────────────────────────────┬─ overall results ────┐
│        run time : 0 days, 0 hrs, 0 min, 2 sec       │  cycles done : 0     │
│   last new find : 0 days, 0 hrs, 0 min, 0 sec       │ corpus count : 7     │
│last saved crash : 0 days, 0 hrs, 0 min, 0 sec       │saved crashes : 0     │
│ last saved hang : none seen yet                     │  saved hangs : 0     │
├─ cycle progress ─────────────────────┬─ map coverage┴──────────────────────┤
│  now processing : 0.1 (0.0%)         │    map density : 0.07% / 0.08%      │
│  runs timed out : 0 (0.00%)          │ count coverage : 1.22 bits/tuple    │
├─ stage progress ─────────────────────┼─ findings in depth ─────────────────┤
│  now trying : havoc                  │ favored items : 1 (14.29%)          │
│ stage execs : 3775/16.4k (23.04%)    │  new edges on : 3 (42.86%)          │
│ total execs : 3824                   │ total crashes : 0 (0 saved)         │
│  exec speed : 1029/sec               │  total tmouts : 0 (0 saved)         │
├─ fuzzing strategy yields ────────────┴─────────────┬─ item geometry ───────┤
│   bit flips : disabled (default, enable with -D)   │    levels : 2         │
│  byte flips : disabled (default, enable with -D)   │   pending : 7         │
│ arithmetics : disabled (default, enable with -D)   │  pend fav : 1         │
│  known ints : disabled (default, enable with -D)   │ own finds : 6         │
│  dictionary : n/a                                  │  imported : 0         │
│havoc/splice : 0/0, 0/0                             │ stability : 100.00%   │
│py/custom/rq : unused, unused, unused, unused       ├───────────────────────┘
│    trim/eff : n/a, disabled                        │          [cpu003:250%]
└────────────────────────────────────────────────────┘
```

Lăsând AFL++ să ruleze suficient de mult, acesta va începe să găsească *crash*-uri. Acest lucru se poate observa în dreptul câmpului "*total crashes*". Numărul de acolo va fi nenul, dar mai mare decât cel din paranteză ("*saved*"). Motivul este că *fuzzer*-ul va salva pe disc numai acele *crash*-uri pe care le consideră unice (de exemplu, provocate la adrese diferite de memorie).

```bash
[afl++ c3196bff9e66] /AFLplusplus # ls /tmp/output/default/crashes/
README.txt  id:000000,sig:06,src:000000,time:105,execs:79,op:havoc,rep:8
```

Putem valida *crash*-ul oferindu-l ca intrare programului:

```
/src/essay-checker.elf /tmp/output/default/crashes/id\:000000\,sig\:06\,src\:000000\,time\:105\,execs\:79\,op\:havoc\,rep\:8  1
Patience is bitter, but its fruit is sweet. - Aristotle
Segmentation fault
```

Acesta poate fi analizat în continuare (de exemplu, cu `gdb`) pentru a afla cauza *crash*-ului și pentru a dezvolta un *exploit* cu un impact mai mare decât cel actual (doar de întrerupere a funcționalității programului.)

### 2 - Code Review 💁

#### `line-appender.c`

Două argumente sunt necesare pentru rularea programului: un nume de fișier sursă și unul destinație. Acestea sunt transmise în funcția `main` către funcția `append_files`. Acolo fișierele sunt deschise, iar [prima linie (sau maxim primii 100 de octeți)](https://linux.die.net/man/3/fgets) este citită și adăugată fișierului destinație.

Un atacator poate folosi lipsa sanitizării intrărilor oferite ([CWE-22: Improper Limitation of a Pathname to a Restricted Directory](https://cwe.mitre.org/data/definitions/22.html)) pentru a naviga sistemul de fișiere. Un exemplu de astfel de atac ar consta în folosirea `../../../../etc/passwd` ca fișier destinație, caz în care am putea adăuga un utilizator nou. Condiția necesară aici este ca programul să aibă drepturile necesare scrierii (de exemplu, fiind deținut de `root` și având bitul SUID setat).

#### `ping-google-dns.c`

Programul ajută la apelarea comenzii `ping`, argumentele fiind `1` pentru numărul de pachete ICMP trimise și o adresă IP provenită de la utilizator. Cea din urmă este verificată cu ajutorul unui mecanism de *whitelisting*, implementarea fiind făcută prin două apeluri succesive către `strncmp`.

Din cauza verificării numai a primelor 8 caractere ([CWE-78: Improper Neutralization of Special Elements used in an OS Command](https://cwe.mitre.org/data/definitions/78.html)), un atacator va putea trimite un *payload* cu o adresă validă, dar concatenată cu `;` și o altă comandă ce va fi automat executată.

```bash
$ ./ping-google-dns              
[+] Google DNS IP you want to ping is: 8.8.8.8;date
[+] Ping output is:

PING 8.8.8.8 (8.8.8.8) 56(84) bytes of data.
64 bytes from 8.8.8.8: icmp_seq=1 ttl=128 time=56.0 ms

--- 8.8.8.8 ping statistics ---
1 packets transmitted, 1 received, 0% packet loss, time 0ms
rtt min/avg/max/mdev = 56.040/56.040/56.040/0.000 ms
Sun Jan 29 08:01:47 AM EET 2023
```

#### `santa-letters.c`

Inspectând fișierul, putem vedea în funcția `main` o salvare pe stivă a unei referințe către o variabilă globală, împreună cu o verificare a numărului de argumente. Pentru a permite execuția, cea din urmă necesită un argument, adnotat cu `FULL_NAME`.

Argumentul este pasat ulterior funcției `print_letter`. Comportamentul acesteia este, în mare parte, neinfluențat de intrarea oferită de utilizator, mai puțin linia `printf(name)`. Astfel, se poate deduce că vulnerabilitatea este [CWE-134: Use of Externally-Controlled Format String](https://cwe.mitre.org/data/definitions/134.html), primul argument putând conține și secvențe de caractere pentru formatare, de tipul `%d`, `%x`, `%s` și `%n`.

Exploatarea se poate efectua astfel:
- Întreruperea execuției programului: Este de ajuns să punem o secvență scurtă de `%s` pentru ca programul să încerce să dereferențieze o adresă nemapată corespunzător. Acest lucru va produce închiderea procesului.
- Citirea de informații din memoria procesului: Folosind ca intrare o secvență de `%08x`, putem inspecta tot conținutul stivei procesului.
- Suprascrierea informațiilor în memoria procesului: Suprascrierea se poate efectua prin folosirea `%n`, care scrie la o adresă de memorie numărul de caractere care au fost printate. Astfel, putem scrie în memorie la orice adresă. Pentru moment, să presupunem numai că dorim să suprascriem valoarea salvată la simbolul `gifts_count` (mai multe cadouri de Crăciun pentru atacator 🤷). Cum adresa este salvată în cadrul funcției `main`, trebuie numai să ducem cursorul funcției `printf` până acolo. Un payload funcțional ar fi astfel `14 * "%0100x " + "%n"`.