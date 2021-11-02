# Setarea Mediului de Lucru

## Sistem de Operare Linux

Asigurați-vă că aveți la îndemână un **sistem de operare bazat pe Linux** pe care să lucrați laboratoarele. Acesta poate fi sistemul dumneavoastră de bază sau o mașină virtuală.

Pentru acest set de laboratoare, recomandăm distribuțiile următoare, recomandări ce sunt acompaniate de *link*-uri de descărcare:
- [Kali Linux](https://www.kali.org/get-kali); și
- [Ubuntu Desktop](https://ubuntu.com/download/desktop).

## Ghidra

Ghidra este un program pe care îl vom folosi la **ingineria inversă a programelor** cu ajutorul unor metode pur statice. Pentru a-l instala pe sistemul de operare Linux, urmați pașii de mai jos:

```
sudo apt-get install default-jdk
wget -O /tmp/ghidra.zip https://github.com/NationalSecurityAgency/ghidra/releases/download/Ghidra_10.0.4_build/ghidra_10.0.4_PUBLIC_20210928.zip
unzip /tmp/ghidra.zip -d /opt/ghidra
```

Programul poate fi rulat cu ajutorul comenzilor:

```
cd /opt/ghidra
./ghidraRun
```

## PEDA

PEDA este un *wrapper* pentru `gdb`. Vom folosi combinația celor două pentru **a analiza dinamic executabile**.

Instalarea este efectuată prin rularea comenzilor de mai jos:

```
git clone https://github.com/longld/peda.git ~/peda
echo "source ~/peda/peda.py" >> ~/.gdbinit
```

## Resurse

- [Ghid Oficial de Instalare a Ghidra](https://ghidra-sre.org/InstallationGuide.html)
- [Repository PEDA](https://github.com/longld/peda)