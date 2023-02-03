#include <stdio.h>
#include <string.h>

#define ASCII_START 32
#define ASCII_END 126
#define KEY_SIZE 37

char key[KEY_SIZE] = {0};
int is_master = 0;

void generate_new_key() {
    int i;

    for(i = 0; i < KEY_SIZE; i++) {
        key[i] = (char)(rand() % (ASCII_END - ASCII_START)) + ASCII_START;
    }
    key[KEY_SIZE] = '\0';
}

void get_master_flag(){
    char master_key[] = {
        0x3a, 0x21, 0x2a, 0x21, 0x4e, 0x5e, 0x5f, 0x40, 0x5f, 0x5c, 0x40, 0x5c,
        0x5e, 0x5c, 0x58, 0x4e, 0x43, 0x4e, 0x2a, 0x1c, 0x01, 0x1e, 0x1e, 0x07,
        0x00, 0x09, 0x4e, 0x1a, 0x06, 0x0b, 0x4e, 0x00, 0x1b, 0x05, 0x0b, 0x1d
    };
    char enc_key = 'n';
    int i;

    for (i = 0; i < sizeof(master_key); i++) {
        key[i] = master_key[i] ^ enc_key;
    }
    key[KEY_SIZE] = '\0';
}

char *execute_request(char *query) {
    char local_query[64];
    void (*called)() = generate_new_key;

    strcpy(local_query, query);

    called();

    return &key;
}