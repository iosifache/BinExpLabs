# 1 - Număr de Șiruri de Caractere Printabile 🏁

## Flag

`44`

## Rezolvare

Vezi fișierul [`strings.py`](strings.py). Odată rulat cu comanda, va afișa *flag*-ul. Comportamentul lui este asemănător utilitarului `strings`, ce putea fi utilizat aici astfel: `strings lyrics.elf -n 15 | wc -l`.

# 2 - Tipuri de Șiruri de Caractere Printabile 💁

## Rezolvare

- Numele unor librării dinamice folosite în procesul de *linking*: `libc.so.6`
- Numele unor funcții importate: `sleep`
- Șiruri de caractere definite în program: `Cinco pasos y te perdon`
- Detalii despre procesul de compilare: `GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0`
- Numele unor simboluri definite în program: `main` (funcție), `lyrics` (variabilă), `.text` (secțiune)

# 3 - Număr de Simboluri 🏁

## Flag

`16`

## Rezolvare

Vezi fișierul [`symbols.py`](symbols.py). Odată rulat cu comanda, va afișa *flag*-ul.

# 4 - Proveniența Simbolurilor 💁

## Rezolvare

- `lyrics`, din zona de date, reprezintă o variabilă globală inițializată. Ca tip, era un vector de șiruri constante de caractere.
- `puts`, simbol nedefinit, este folosit la *runtime*, după ce *linkarea* dinamică a `libc` se produce.
- `main`, din zona de cod, reprezintă funcția principală a programului C.

# 5 - Automatizarea Analizei Dinamice cu `pwntools` 🏁

## Flag

`SI{CHECKING_THE_FLAG_BYTE_BY_BYTE}`

## Rezolvare

Simpla rulare a programului determina printarea unei erori ce specifică faptul că o librărie nu a fost găsită. Acest lucru se produce în ciuda faptului că librăria se află chiar în aceeași locație. Vom rula programul folosind prefixul `LD_LIBRARY_PATH=.`.

Se observă faptul că executabilul afișează numai acea porțiune din șirul de caractere dat ca parametru ce corespunde cu *flag*-ul. Modul de rezolvare constă în efectuarea unui atac de tip *brute-force*, caracter cu caracter.

Se începe cu primul caracter, testându-se toate posibilitățile. La încercarea la care programul afișează un caracter, atunci îl putem seta ca primul caracter din *flag*-ul construit progresiv și putem trece la următorul până când caracterul `}` (terminatorul de *flag*) apare.

O implementare este oferită în fișierul [`flag-checker.py`](flag-checker.py).

# 6 - Librării Dinamice 💁

Rulând comanda `ldd flag-checker.elf` observăm faptul că executabilul folosește o librărie dinamică numită `libcheckflag.so`.

Pentru a identifica modul în care se apelează funcții din ea, rulăm comanda `objdump --disassemble=main -M intel flag-checker.elf`, ce dezasamblează codul funcției `main` (argumentul `--disassemble`) în sintaxa specifică Intel (argumentul `-M`). Astfel, se ajunge la concluzia că libraria este încărcată în memorie prin apelul funcției `dlopen` și funcția din ea, `check_flag`, este referențiată printr-un apel `dlsym`.

# 7 - Dezasamblarea Programelor 💁

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

# 8 - Apeluri de Sistem 💁

Verificând ieșirea comenzii `strace python3 -m http.server 8080`, observăm secvența de apeluri de sistem prezentă mai jos:

```
socket(AF_INET, SOCK_STREAM|SOCK_CLOEXEC, IPPROTO_IP) = 3
[..]
bind(3, {sa_family=AF_INET, sin_port=htons(8080), sin_addr=inet_addr("0.0.0.0")}, 16) = 0
[..]
listen(3, 5)
```

# 9 - Conexiuni 💁

Rulându-se comanda `netstat -tlp`, se poate identifica rapid *socket*-ul TCP (opțiunea `-t`) în modul *listening* (opțiunea `-l`). Opțiunea `-p` este adăugată pentru a afișa și datele de identificare ale procesului (PID și executabil).

```
Proto Recv-Q Send-Q Local Address           Foreign Address         State       PID/Program name    
[..]
tcp        0      0 0.0.0.0:http-alt        0.0.0.0:*               LISTEN      53639/python3
```