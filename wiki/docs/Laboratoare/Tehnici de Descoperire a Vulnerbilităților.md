---
slug: /vuln
sidebar_position: 1
---

# Tehnici de Descoperire a Vulnerbilităților

## Suport

<a href="https://github.com/iosifache/BinExpLabs/blob/main/labs/vuln/support/export.pdf">
    <img src="https://raw.githubusercontent.com/iosifache/BinExpLabs/main/labs/vuln/support/preview.png" width="400px" alt="Preview"/>
</a>

## Exerciții

<a href="https://github.com/iosifache/BinExpLabs/releases/download/v1.2/vuln.zip">
    <img src="https://img.shields.io/badge/Release%20cu%20Fișierele%20Necesare-Descarcă-blue?style=for-the-badge&logo=github"/>
</a>

### 1 - Fuzzing cu AFL++ 💁

Plecând de la executabilul `essay-checker.elf`, identificați o intrare validă. Folosiți această intrare ca punct de plecare pentru fuzzing-ul cu AFL++. Scopul este de a obține un *crash*, pe care să îl analizați ulterior.

În cazul în care niciun crash nu este identificat în timp util, scădeți lungimea buffer-ului (constanta `BUFFER_LENGTH`), recompilați și relansați AFL++.

### 2 - Code Review 💁

Parcurgeți fiecare fișier sursă C din folder-ul `code-review` și identificați vulnerabilitatea fiecăruia. Opțional, validați presupunerile pe care le faceți rulând programul și oferind o intrare malițioasă acestuia.