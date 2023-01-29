---
slug: /solve-protections
sidebar_position: 3
---

# Mecanisme de Protecție

## 1 - Verificarea Activării unor Mecanisme de Securitate 💁

Prima sarcină poate fi rezolvată cu utilitarul `nm`. Se observă faptul că al doilea executabil nu are niciun simbol, ceea ce indică utilizarea după compilare a `strip`.

```bash
$ nm fortress.elf | wc -l
41
```

```bash
$ nm fortress.stripped.elf | wc -l 
nm: fortress.stripped.elf: no symbols
0
```

Pentru următorul set de executabile, dimensiunea `fortress.packed.elf` este cu mult mai mică decât a celuilalt executabil (care a fost compilat static, de unde și dimensiunea mare).

```bash
$ ls -sh fortress.static.elf fortress.packed.elf
304K fortress.packed.elf  696K fortress.static.elf
```

Împreună cu o observație referitoare la tipul de șiruri de caractere găsite în primul executabil menționat (de tipul `UPX!`, `?OTHT` și `tdx~x{`), putem să deducem împachetarea programului. Concluzia poate fi verificată suplimentar cu utilitarul `upx`.

```bash
$ upx -t fortress.packed.elf 
[...]
testing fortress.packed.elf [OK]
[...]
```

Mecanismele de securitate ale executabilului `fortress.elf` se pot verifica prin comanda `checksec`, ce este oferită de librăria Python 3 deja instalată `pwntools`. Se observă în ieșire că mecanismele de protecție a stivei, cu canarii, și NX sunt activate.

```bash
$ checksec fortress.elf 
[*] 'fortress.elf'
    Arch:     i386-32-little
    RELRO:    Partial RELRO
    Stack:    Canary found
    NX:       NX enabled
    PIE:      No PIE (0x8048000)
```

Suplimentar, din Ghidra, se pot extrage informații despre modalitatea în care se efectuează verificarea canariilor. Decompilarea funcției `main` arată faptul că pe stivă este plasată o valoare (variabila `iVar1`), populată cu `gs:0x14` și verificată la sfârșit.

```c
undefined4 main(void)

{
    int iVar1;
    undefined4 uVar2;
    int in_GS_OFFSET;

    iVar1 = *(int *)(in_GS_OFFSET + 0x14);

    [...]

    if (iVar1 != *(int *)(in_GS_OFFSET + 0x14)) {
        uVar2 = __stack_chk_fail_local();
    }

    return uVar2;
}
```

După verificarea secțiunilor, se constată faptul că niciuna nu are drepturi de execuție și scriere în același timp.

```bash
$ readelf --sections fortress.elf
There are 31 section headers, starting at offset 0x387c:

Section Headers:
  [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al
  [ 0]                   NULL            00000000 000000 000000 00      0   0  0
  [ 1] .interp           PROGBITS        080481b4 0001b4 000013 00   A  0   0  1
[...]
```

Pentru completarea ultimei sarcini, prin verificarea conținutului fișierului `/proc/sys/kernel/randomize_va_space` se obține un număr ce, dacă este nenul, indică activarea mecanismului ASLR.
