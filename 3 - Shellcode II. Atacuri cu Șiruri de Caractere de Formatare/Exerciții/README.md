# 1 - Folosirea Apelului de Sistem `execve` în *Shellcode* 💁

Identificați vulnerabilitatea executabilului [`essay-checker.elf`](essay-checker/essay-checker.elf) și căutați un *shellcode* pe *website*-ul [shell-storm.org](http://shell-storm.org/shellcode/) care să lanseze în execuție programele `/bin/bash` sau `/bin/sh`, dar care să fie compatibil cu arhitectura pe care executabilul rulează. Combinând aceste două informații și utilizând simbolul `helper`, creați un *payload* care să exploateze executabilul pentru lansarea în execuție a unui *shell*.

# 2 - Exploatări ale Șirurilor de Caractere de Formatare 💁

Pe baza executabilului [`santa-letters.elf`](santa-letters/santa-letters.elf), răspundeți la următoarele întrebări:
- Care este vulnerabilitatea programului și din ce cauză apare?
- Cum poate fi exploatată vulnerabilitatea pentru a efectua aspecte de mai jos?
    - Întreruperea execuției programului
    - Citirea de informații din memoria procesului
    - Suprascrierea informațiilor (folosiți adresa variabilei globale `gifts_count`, ce este salvată în cadrul funcției `main`) în memoria procesului