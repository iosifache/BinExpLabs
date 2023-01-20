#!/usr/bin/env python3

import string

from pwn import log, context, process

FILENAME = "flag-checker.elf"
ENVIRONMENT = {'LD_LIBRARY_PATH': '.'}
CHARSET = string.ascii_uppercase + '_{}'
MAX_FLAG_LENGTH = 50
FLAG_END_CHAR = "}"


def main() -> None:
    # Dezactivează mesajele de jurnalizare ale pwntools
    context.log_level = "error"

    current_flag = ""
    for iteration in range(MAX_FLAG_LENGTH):
        for char in CHARSET:
            # Lansează un proces nou
            p = process([FILENAME, current_flag + char], env=ENVIRONMENT)

            # Preia ieșirea și verifică dacă ea produce vreo schimbare
            output = p.recvall()
            if len(output) > len(current_flag):
                current_flag = output.decode("utf-8")

                break

        if (FLAG_END_CHAR in current_flag):
            # Reactivează mesajele de jurnalizare ale pwntools
            context.log_level = "info"

            # Cum programul printează și alte caractere care nu sunt de interes,
            # printăm numai prima linie
            current_flag = current_flag.split("\n")[0]
            log.success("Flag-ul este {}.".format(current_flag))

            break


if __name__ == "__main__":
    main()