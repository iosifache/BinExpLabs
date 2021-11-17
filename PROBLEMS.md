# Probleme Uzuale

## Eroare "*No such file or directory*" la Rularea Programului

**Problemă**: Rularea executabilului cu `./executable` returnează "*bash: ./executable: No such file or directory*".

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