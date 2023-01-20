#!/usr/bin/env python3

import string

from pwn import log, ELF

FILENAME = "lyrics.elf"
TEXT_SECTION = ".text"
EXECUTABLE_FLAG = 1


def get_symbols(filename: str) -> list:
    elf = ELF(filename, checksec=False)

    # Preia secțiunea .text
    text_section = [
        section for section in elf.sections if section.name == TEXT_SECTION
    ][0]

    # Preia segmentele executabile
    exe_segments = [
        segment for segment in elf.segments
        if segment.header.p_flags & EXECUTABLE_FLAG
    ]

    # Verifică dacă segmentele executabile gasite se află în sectiunea .text
    text_exe_segments = [
        segment for segment in exe_segments
        if segment.section_in_segment(text_section)
    ]

    symbols = []
    for segment in text_exe_segments:
        # Preia adresele de start și de început ale segmentului curent
        start_address = segment.header['p_vaddr']
        end_address = start_address + segment.header['p_filesz']

        # Preia simbolurile care se află în acest segment
        for key in elf.symbols.keys():
            address = elf.symbols[key]

            if (address >= start_address and address < end_address):
                symbols.append(key)

    return symbols


def main() -> None:
    all_symbols = get_symbols(FILENAME)

    # Printează câte au fost găsite
    log.info("Număr de simboluri gasite este {}.".format(len(all_symbols)))

    # Printează simbolurile
    log.info("Simbolurile găsite sunt:")
    for symbol in all_symbols:
        print("\t- {}".format(symbol))


if __name__ == "__main__":
    main()
