# BinExpLabs 💥

## Descriere 🖼️

**BinExpLabs** este un *repository* ce găzduiește materialele folosite pentru cele patru laboratoarele axate pe exploatarea programelor de pe sistemele de operare Linux, din cadrul materiei "*Securitatea Informației*". Aceasta este predată în anul IV, în Academia Tehnică Militară "*Ferdinand I*" București.

## Setarea Mediului de Lucru 🧑‍🔧

Înainte de a începe parcurgerea laboratoarelor, asigurați-vă că aveți îndeplinite cerințele menționate în fișierul [`SETUP.md`](SETUP.md).

## Structura Laboratoarelor 🧩

Fiecare laborator este compus dintr-un **suport**, adică o prezentare LaTeX în care sunt prezentate noțiunile teoretice folosite în cadrul laboratorului, și o **serie de exerciții**.

Fiecare exercițiu poate avea una sau mai multe cerințe de mai multe tipuri:
- *Cu un rezultat fix*: Sunt marcate cu 🏁, iar rezultatul scontat este un *flag* ce trebuie introdus în platforma de CTF pentru a demonstra rezolvarea.
- *De discuție*: Marcate cu 💁, exercițiile de acest tip implică numai observarea sau deducerea anumitor aspecte, ce vor fi discutate în cadrul laborator.

## Subiecte Abordate 🗃️

1. **Introducere**
    - Motivație
    - Cerințe
    - Formatul de fișiere ELF
    - Coduri de operații
    - Apeluri de sistem
    - Structura stivei unui proces
    - Instrumente generale folosite
    - Vectori de atac
2. **Suprascrierea Stivei. *Shellcodes* I**
    - Suprascrierea stivei
        - Modificarea variabilelor locale
        - Suprascrierea valorii de retur
    - *Shellcodes*
        - Crearea și testarea unui *shellcode*
3. ***Shellcodes* II. Șiruri de Caractere de Formatare**
    - *Shellcodes*
        - Folosirea apelului de sistem `execve` pentru obținerea unui execuții de cod la distanță
    - Șiruri de caractere de formatare
        - Funcții specifice din limbajul C
        - Declanșarea unui *leak* de informații
        - Suprascrierea adrese de retur
4. **Metode de Prevenție**
    - Eliminarea simbolurilor
    - *Address Space Layout Randomization*
    - *Data Execution Prevention*
    - *Stack canaries*