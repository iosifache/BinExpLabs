# Probleme Uzuale

## Eroare "*No such file or directory*" la Rularea Programului

**Problemă**: Rularea executabilului cu `./executable` returnează "*bash: ./executable: No such file or directory*".

**Soluție**: Verificați dacă interpretorul folosit de executabil (eventual și `gcc-multilib`) este instalat pe sistemul de operare.

## Erori Prefixate cu "*ERROR: ld.so*" la Rularea Programului

**Problemă**: Rularea executabilului eșuează, fiind returnate mai multe erori prefixate cu *ERROR: ld.so*.

**Soluție**: Verificați dacă interpretorul folosit de executabil (eventual și `gcc-multilib`) este instalat pe sistemul de operare.

## Eroare "*not a dynamic executable*" la Rularea `ldd`

**Problemă**: Rularea `ldd` pe executabil returnează "*not a dynamic executable*".

**Soluție**: Executabilul este compilat pentru 32 de biți, iar sistemul pe care se încearcă rularea este pe 64. Instalați `gcc-multilib`.

## Setarea `JDK_HOME`

**Problemă**: JDK-ul nu este detectat de diverse soluții software (de exemplu, Ghidra).

**Soluție**: Setați (pentru persistență, în `~/.profile`) variabile de mediu de mai jos. `JAVA_PATH` reprezintă calea unde este instalat JDK (calea returnată de `which java`).

```
export JDK_HOME=JAVA_PATH
export JAVA_HOME=${JDK_HOME}
export PATH=$PATH:${JAVA_HOME}/bin
```

## Eroare "*~/peda/peda.py:8: Error in sourced command file*" la Rularea PEDA

**Problemă**: La rularea `gdb`, PEDA nu rulează corespunzător. Apare eroarea de mai jos:

```
[...]
~/peda/peda.py:8: Error in sourced command file:
Undefined command: "from". Try "help"
[...]
```

**Soluție**: Întrucât versiunea actuală a depanatorului nu suportă Python 3, actualizați pachetul `gdb`.