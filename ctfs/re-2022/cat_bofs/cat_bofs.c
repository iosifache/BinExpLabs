#include <stdio.h>
#include <string.h>

#define EXTENSION ".bof"
#define BUFFER_LENGTH 16

void to_be_included_in_the_next_release() {
    char member_text[] = {
        0x43, 0x59, 0x6b, 0x43, 0x59, 0x5d, 0x40, 0x5c, 0x55, 0x4f, 0x52, 0x5f,
        0x56, 0x43, 0x4f, 0x51, 0x42, 0x55, 0x4f, 0x44, 0x5f, 0x5f, 0x4f, 0x55,
        0x51, 0x43, 0x49, 0x6d
    };
    char key = 0x10;
    int i;

    for (i = 0; i < sizeof(member_text); i++) {
        member_text[i] = member_text[i] ^ key;
    }

    printf("%s", member_text);
    fflush(stdout);
}

void process_file(char *filename, int filename_length) {
    char buffer[BUFFER_LENGTH];
    FILE *file;
    int content_size;

    file = fopen(filename, "rb");
    fread(&content_size, sizeof(int), 1, file);
    printf("%d\n", content_size);
    fread(&buffer, content_size, 1, file);
    buffer[content_size] = '\0';

    printf("%s\n", buffer);
}

int main(int argc, char *argv[]) {
    char *filename;
    int filename_length;

    // Check argc
    if (argc != 2) return 1;

    // Check the name of the file
    filename = argv[1];
    filename_length = strlen(filename);
    if (strcmp(filename + filename_length - strlen(EXTENSION), EXTENSION))
        return 1;

    // Process file
    process_file(filename, filename_length);
}
