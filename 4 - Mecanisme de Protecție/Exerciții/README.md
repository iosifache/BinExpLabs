# 1 - Verificarea Activării unor Mecanisme de Securitate 💁

Folosiți instrumente disponibile în sistemul dumneavoastră de operare pentru a efectua următoarele sarcini:
- Comparați numărul de simboluri ale [`fortress.elf`](fortress/fortress.elf) și [`fortress.stripped.elf`](fortress/fortress.stripped.elf). Ce observați?
- Identificați dimensiunea și numărul de șiruri de caractere din [`fortress.static.elf`](fortress/fortress.static.elf) și [`fortress.packed.elf`](fortress/fortress.packed.elf). Ce observați?
- Verificați existența următoarelor mecanisme de securitate în [`fortress.elf`](fortress/fortress.elf):
    - Canarii; și
    - NX.
- Identificați modalitatea prin care este efectuată verificarea canariilor în [`fortress.elf`](fortress/fortress.elf).
- Verificați existența unor secțiuni cu drepturi de scriere și execuție în [`fortress.elf`](fortress/fortress.elf).
- Verificați activarea mecanismului ASLR.