# 1 - Suprascrierea Stivei 🏁

Analizați fișierul executabil [`cookie_lover.elf`](cookie_lover/cookie_lover.elf) pentru a identifica funcționalitatea ce permite suprascrierea stivei și a o exploata pentru obținerea *flag*-ului.

# 2 - Crearea și Testarea unui *Shellcode* 💁

> Pentru completarea acestei sarcini, este necesară rularea comenzii `sudo apt-get install nasm` pentru instalarea asamblorului NASM.

Rolul acestei sarcini este de a observa modul în care un *shellcode* este creat, compilat și rulat într-un mediu controlat (spre deosebire de execuția lui în cadrului unui *exploit*), cu ajutorul a două metode. Efectuați pașii de mai jos:
1. Vizualizați conținutul fișierului [`shellcode.S`](shellcode/shellcode.S). Care este funcționalitatea lui?
2. Rulați comanda `make get_shellcode`. Ce reprezintă octeții returnați?
3. Plasați șirul de octeți obținut anterior în fișierul [`execution_from_stack.c`](shellcode/execution_from_stack.c). Rulați comanda `make execution_from_stack.elf` și, ulterior, executați programul. Folosiți instrumentele prezentate în primul laborator pentru a înțelege cum se rulează *shellcode*-ul.
4. Plasați șirul de octeți obținut anterior în fișierul [`execution_with_mprotect.c`](shellcode/execution_with_mprotect.c). Rulați comanda `make execution_with_mprotect.elf` și, ulterior, executați programul. Folosiți instrumentele prezentate în primul laborator pentru a înțelege cum se rulează *shellcode*-ul.