#!/usr/bin/env python3

import string

from pwn import log

FILENAME = "../Exerciții/lyrics/lyrics.elf"
MIN_LENGTH = 15


def get_printable_transformation() -> str:
    # Creează un vector de 256 de elemente
    chars = 256 * ['\0']

    # Plasează elementele de interes
    for i in range(32, 127):
        chars[i] = chr(i)
    chars[ord('\n')] = "\n"
    chars[ord('\t')] = "\t"

    return "".join(chars).encode("utf-8")


def get_strings(filename: str, min_length: int) -> list:
    # Citește conținutul fișierului
    content = open(filename, "rb").read()

    # Transformă caracterele neprintabile în NULL, obținand astfel o listă
    all_strings = content.translate(
        get_printable_transformation()).split(b'\0')

    # Filtrează lista astfel încat să conțina numai șiruri de caractere cu
    # lungimea minimă
    all_strings = [
        string.decode("utf-8") for string in all_strings
        if len(string) >= min_length
    ]

    return all_strings


def main() -> None:
    # Obține șirurile de caractere printabile
    all_strings = get_strings(FILENAME, MIN_LENGTH)

    # Printează câte au fost găsite
    log.info("Numărul de șiruri de caractere printabile este {}.".format(
        len(all_strings)))

    # Printează șirurile de caractere
    log.info("Șirurile de caractere găsite sunt:")
    for string in all_strings:
        print("\t- {}".format(string))


if __name__ == "__main__":
    main()