#include "stdio.h"

int check_flag(char *provided_flag) {
    char flag[] = {
        0x32, 0x28, 0x1a, 0x22, 0x29, 0x24, 0x22, 0x2a, 0x28,
        0x2f, 0x26, 0x3e, 0x35, 0x29, 0x24, 0x3e, 0x27, 0x2d,
        0x20, 0x26, 0x3e, 0x23, 0x38, 0x35, 0x24, 0x3e, 0x23,
        0x38, 0x3e, 0x23, 0x38, 0x35, 0x24, 0x1c
    };
    char key = 'a', current_letter, provided_letter;
    int i;

    for (i = 0; i < sizeof(flag); i++) {
        current_letter = flag[i] ^ key;
        provided_letter = provided_flag[i];

        if (current_letter == provided_letter)
            // TODO: Debug only, will remove later
            printf("%c", current_letter);
        else
            return 0;
    }

    return 1;
}
