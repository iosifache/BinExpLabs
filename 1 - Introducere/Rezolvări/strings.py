#/usr/bin/env python3

import string

FILENAME = "../Executabile/lyrics/lyrics"
MIN_LENGTH = 15


def get_printable_transformation():
    # Creeaza un vector de 256 de elemente
    chars = 256 * ['\0']

    # Plaseaza elementele de interes
    for i in range(32, 127):
        chars[i] = chr(i)
    chars[ord('\n')] = "\n"
    chars[ord('\t')] = "\t"

    return "".join(chars).encode("utf-8")


def get_strings(filename: str, min_length: int):
    # Citeste continutul fisiereului
    content = open(filename, "rb").read()

    # Transforma caracterele neprintabile in NULL, obtinand astfel o lista
    all_strings = content.translate(
        get_printable_transformation()).split(b'\0')

    # Filtreaza lista astfel incat sa contina numai caractere siruri de
    # caractere cu lungimea minima
    all_strings = [
        string.decode("utf-8") for string in all_strings
        if len(string) >= min_length
    ]

    return all_strings


def main():
    # Obtine sirurile de caractere printabile
    all_strings = get_strings(FILENAME, MIN_LENGTH)

    # Printeaza cate au fost gasite
    print("[+] Numar de siruri de caractere printabile: {}".format(
        len(all_strings)))

    # Printeaza sirurile de caractere
    print("[+] Sirurile de caractere gasite sunt:")
    for string in all_strings:
        print("\t- {}".format(string))


if __name__ == "__main__":
    main()