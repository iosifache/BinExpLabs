---
slug: /protections
sidebar_position: 3
---

# Mecanisme de Protecție

## Suport

<a href="https://github.com/iosifache/BinExpLabs/blob/main/labs/protections/support/export.pdf">
    <img src="https://raw.githubusercontent.com/iosifache/BinExpLabs/main/labs/protections/support/preview.png" width="400px" alt="Preview"/>
</a>

## Exerciții

### 1 - Verificarea Activării unor Mecanisme de Securitate 💁

Folosiți instrumente disponibile în sistemul dumneavoastră de operare pentru a efectua următoarele sarcini:
- Comparați numărul de simboluri ale `fortress.elf` și `fortress.stripped.elf`. Ce observați?
- Identificați dimensiunea și numărul de șiruri de caractere din `fortress.static.elf` și `fortress.packed.elf`. Ce observați?
- Verificați existența următoarelor mecanisme de securitate în `fortress.elf`:
    - Canarii; și
    - NX.
- Identificați modalitatea prin care este efectuată verificarea canariilor în `fortress.elf`.
- Verificați existența unor secțiuni cu drepturi de scriere și execuție în `fortress.elf`.
- Verificați activarea mecanismului ASLR.