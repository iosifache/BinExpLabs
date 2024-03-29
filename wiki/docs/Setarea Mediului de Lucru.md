---
slug: /setup
sidebar_position: 1
---

# Setarea Mediului de Lucru

## Sistem de Operare Linux

Asigurați-vă că aveți la îndemână un **sistem de operare bazat pe Linux** pe care să lucrați laboratoarele. Acesta poate fi sistemul dumneavoastră de bază sau o mașină virtuală.

Pentru acest set de laboratoare, recomandăm distribuțiile următoare, recomandări ce sunt acompaniate de *link*-uri de descărcare:

- [Kali Linux](https://www.kali.org/get-kali); și
- [Ubuntu Desktop](https://ubuntu.com/download/desktop).

## Asamblorul NASM

NASM este un asamblor pe care îl folosim la translatarea codului de asamblare în limbaj mașină. Instalarea lui poate fi efectuată cu comanda de mai jos.

```bash
sudo apt-get install nasm
```

## Python 3 și Pachetul `pwntools`

Python 3 este un limbaj interpretat, de uz generic. Va fi util pentru **a automatiza anumite sarcini** ce, în mod uzual, ar fi fost efectuate cu ajutorul utilitarelor dedicate (care, de multe ori, nu oferă API-uri).

Suplimentar, vom folosi și pachetul `pwntools` pentru a ușura **scrierea și rularea de *exploit*-uri**.

```bash
$ sudo apt-get install python3 python3-pip python3-dev git libssl-dev libffi-dev build-essential
python3 -m pip install --upgrade pip
python3 -m pip install --upgrade pwntools
```

## Ghidra

Ghidra este un program pe care îl vom folosi la **ingineria inversă a programelor** cu ajutorul unor metode pur statice. Pentru a-l instala pe sistemul de operare Linux, urmați pașii de mai jos:

```bash
sudo apt-get install default-jdk
wget -O /tmp/ghidra.zip https://github.com/NationalSecurityAgency/ghidra/releases/download/Ghidra_10.2_build/ghidra_10.2_PUBLIC_20221101.zip
unzip /tmp/ghidra.zip -d /opt
mv /opt/ghidra_10.2_PUBLIC /opt/ghidra
```

Programul poate fi rulat cu ajutorul comenzilor:

```bash
cd /opt/ghidra
./ghidraRun
```

## PEDA

PEDA este un *wrapper* pentru `gdb`. Vom folosi combinația celor două pentru **a analiza dinamic executabile**.

Instalarea este efectuată prin rularea comenzilor de mai jos:

```bash
git clone https://github.com/longld/peda.git ~/peda
echo "source ~/peda/peda.py" >> ~/.gdbinit
```

## AFL++ cu Suport QEMU

AFL++ este un *fuzzer* de tip blackbox, cu suport de testare a executabilelor (fără a avea acces la codul sursă) prin intermediul QEMU.

Pentru rularea comenzilor de mai jos, asigurați-vă că Docker este instalat.

```bash
docker pull aflplusplus/aflplusplus
docker run -ti -v <source_folder>:/src aflplusplus/aflplusplus
```

După rularea ultimei comenzi, o sesiune de terminal se va deschide. Ea permite rularea următoarelor comenzi înăuntrul *container*-ului:

```bash
make
cd qemu_mode
./build_qemu_support.sh
```
