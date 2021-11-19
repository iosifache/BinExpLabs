# 1 - Suprascrierea Stivei 🏁

## Flag

`SI{A_BALANCED_DIET_IS_A_COOKIE_IN_EACH_HAND}`

## Rezolvare

În urma unei analize statice, se poate observa faptul că programul, odată rulat, va aștepta conexiuni pe `0.0.0.0`, pe un port dat ca argument. Atunci când un client se conectează, se va aștepta un text, lungimea maximă fiind mai mare decât lungimea *buffer*-ului alocat pe stivă. Astfel, o tehnică de exploatare poate fi *buffer overflow*.

Pe stiva funcției `serve_new_member`, se salvează următoarele variabile:
- *Buffer*-ul textului utilizatorului; și
- O protecție a stivei, numită *stack cookie*, ce este o valoare calculata prin formula:

```
srand(time(0));
cookie = rand() % time(0);
```

- Un *pointer* către o funcție cu un parametru de tip întreg, ce va fi apelată dacă verificarea *stack cookie*-ului va fi trecuta.

Astfel, structura stivei la apelarea funcției `serve_new_member` este următoarea:

```
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

Tot prin analiză statică, putem vedea că funcția `send_flag` are același prototip ca `send_fail`, putând să ne folosim de adresa ei pentru a suprascrie *pointer*-ul salvat pe stivă. Structura payload-ului va fi astfel:

```
+---------------------+----------------------------------+---------------------------------+
|                     |                                  |                                 |
| 28 bytes of garbage | 4 bytes of computed stack cookie | 4 bytes of pointer to send_flag |
|                     |                                  |                                 |
+---------------------+----------------------------------+---------------------------------+
```

In script-ul [`exploit.py`](cookie_lover/exploit.py), s-a folosit Python 3 (împreună cu modulul `pwntools`) și un program separat, scris în C, `random.c`, utilizat pentru calcularea valorii *stack cookie*-ului.

```
./exploit.py
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

# 2 - Crearea și Testarea unui *Shellcode* 💁

Funcționalitatea codului în limbaj de asamblare din fișierul dat este următoarea:

```
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

Pentru fișierul [`execution_from_stack.c`](../Exerciții/shellcode/execution_from_stack.c), este relevantă opțiunea cu care este compilat programul, și anume `-z execstack`. Acesta face ca stiva să fie executabilă (conform cu rezultatul din `gdb`, prezentat mai jos) și ca acel apel către codul salvat în variabila `shellcode` să fie efectuat corect. Este de menționat aici faptul că permisiunile de scriere și execuție nu se găsesc împreună pe sistemele moderne, datorită Data Execution Prevention (abreviat DEP), însă aici marcăm explicit stiva ca fiind executabilă în scop pur didactic, pentru a demonstra execuția *shellcode*-ului.

```
gdb ./execution_from_stack.elf
[...]
gdb-peda$ break main
[...]
gdb-peda$ run
[...]
gdb-peda$ vmmap
[...]
0xfffdc000 0xffffe000 rwxp	[stack]
```

Pe de altă parte, fișierul [`execution_with_mprotect.c`](../Exerciții/shellcode/execution_with_mprotect.c) folosește un mecanism diferit. Se mapează în memorie codul mașină (apelurile `mmap` și `memcpy`), iar zona alocată este marcată ca având toate permisiunile (apel către `mprotect`, cu parametrul `PROT_READ | PROT_WRITE | PROT_EXEC`). Acest lucru permite execuția codului în ciuda DEP.

```
strace ./execution_with_mprotect.elf
[...]
mmap2(NULL, 1, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0) = 0xf7f76000
mprotect(0xf7f76000, 1, PROT_READ|PROT_WRITE|PROT_EXEC) = 0
```