#include <stdio.h>
#include <string.h>
#include <sys/mman.h>

#define FLAG_FILE "./flag.txt"
#define FLAG_SIZE 48
#define BUFFER_SIZE 128
#define STR_IMPL_(x) #x
#define STR(x) STR_IMPL_(x)
#define BAD_CHARS { 'b', 'i', 'n', '/', 's', 'h', 0x44 }

char flag[FLAG_SIZE] = {0};

void load_flag() {
    FILE *flag_file;

    // Citește flag-ul în variabila globală cu același nume
    flag_file = fopen(FLAG_FILE, "r");
    fread(flag, FLAG_SIZE - 1, 1, flag_file);
    fclose(flag_file);

}

int check_shellcode(char *shellcode) {
    char bad_chars[] = BAD_CHARS;
    int i, j;

    // Verifică prezența caracterelor ilegale
    for (i = 0; i < BUFFER_SIZE; i++) {
        for (j = 0; j < sizeof(bad_chars); j++) {
            if (shellcode[i] == bad_chars[j]) {
                printf("\nNe pare rău, dar ShellcodeSandbox™ a marcat shellcode-ul "
                       "ca fiind malițios.\n");
                return 0;
            }
        }
    }

    return 1;
}

void run_shellcode(char *shellcode) {
    void *mem = mmap(0, sizeof(shellcode), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    memcpy(mem, shellcode, BUFFER_SIZE);
    mprotect(mem, sizeof(shellcode), PROT_READ | PROT_WRITE | PROT_EXEC);

    void (*function)();
    function = (void (*)())mem;
    (void)(*function)();

    munmap(mem, sizeof(shellcode));
}

int main() {
    char shellcode[BUFFER_SIZE];

    load_flag();

    // Printarea unui banner
    printf("ShellcodeSandbox™\n");
    printf("Tehnologia noastră revoluționară permite rularea în siguranță a "
           "shellcode-urilor, asigurându-ne că utilizatorii nu pot citi "
           "flag-ul acestei provocări.\n\n");
    printf("Pentru demonstrarea funcționalității, oferă un shellcode de "
           "lungime de " STR(BUFFER_SIZE) " de caractere:\n");

    // Citirea, sanitizare și, eventual, rularea shellcode-ului
    fgets(shellcode, BUFFER_SIZE, stdin);
    if (check_shellcode(shellcode)) {
        printf("\nShellcode-ul a fost marcat ca benign de ShellcodeSandbox™ și va "
               "fi executat!\n");

        run_shellcode(shellcode);
    };

    return 0;
}