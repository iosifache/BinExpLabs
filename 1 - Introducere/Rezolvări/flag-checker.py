#/usr/bin/env python3

import string

from pwnlib.tubes.process import process

FILENAME = "../Executabile/flag-checker/flag-checker"
ENVIRONMENT = {'LD_LIBRARY_PATH': '../Executabile/flag-checker'}
CHARSET = string.ascii_uppercase + '_{}'
MAX_FLAG_LENGTH = 50
FLAG_END_CHAR = "}"


def main():
    current_flag = ""
    for iteration in range(MAX_FLAG_LENGTH):
        for char in CHARSET:
            # Lanseaza un proces nou
            p = process([FILENAME, current_flag + char], env=ENVIRONMENT)

            # Preia iesirea si verifica daca ea produce vreo schimbare
            output = p.recvall()
            if len(output) > len(current_flag):
                current_flag = output.decode("utf-8")

                break

        if (FLAG_END_CHAR in current_flag):
            # Cum programul printeaza si alte caractere care nu sunt de interes,
            # printam numai prima linie
            current_flag = current_flag.split("\n")[0]
            print("[+] Flag-ul este: {}".format(current_flag))

            break


if __name__ == "__main__":
    main()