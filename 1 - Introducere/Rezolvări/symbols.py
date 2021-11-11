#/usr/bin/env python3

import string

from pwnlib.elf.elf import ELF

FILENAME = "../Executabile/lyrics/lyrics"
TEXT_SECTION = ".text"
EXECUTABLE_FLAG = 1


def get_symbols(filename: str):
    elf = ELF(filename)

    # Preia sectiunea .text
    text_section = [
        section for section in elf.sections if section.name == TEXT_SECTION
    ][0]

    # Preia segmentele executabile
    exe_segments = [
        segment for segment in elf.segments
        if segment.header.p_flags & EXECUTABLE_FLAG
    ]

    # Verifica daca segmentele executabile gasite se afla in sectiunea .text
    text_exe_segments = [
        segment for segment in exe_segments
        if segment.section_in_segment(text_section)
    ]

    symbols = []
    for segment in text_exe_segments:
        # Preia adresele de start si de inceput ale segmentului curent
        start_address = segment.header['p_vaddr']
        end_address = start_address + segment.header['p_filesz']

        # Preia simbolurile care se afla in acest segment
        for key in elf.symbols.keys():
            address = elf.symbols[key]

            if (address >= start_address and address < end_address):
                symbols.append(key)

    return symbols


def main():
    all_symbols = get_symbols(FILENAME)

    # Printeaza cate au fost gasite
    print("[+] Numar de simboluri gasite: {}".format(
        len(all_symbols)))

    # Printeaza sirurile de caractere
    print("[+] Simbolurile gasite sunt:")
    for symbol in all_symbols:
        print("\t- {}".format(symbol))


if __name__ == "__main__":
    main()