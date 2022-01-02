#include <stdio.h>
#include <stdlib.h>

#define BUFFER_LENGTH 1024

void helper() {
    asm("call %esp; ret");
}

int check_essay(char *filename, int desired_length) {
    FILE *file;
    char text[BUFFER_LENGTH];
    int paragraphs_count = 0, length, i;

    // Get the file size the file content
    file = fopen(filename, "rb");
    fseek(file, 0, SEEK_END);
    length = ftell(file);

    // Get the file content
    fseek(file, 0, SEEK_SET);
    fread(text, 1, length, file);

    // Count the occurances of the new line character
    for (i = 1; i < BUFFER_LENGTH; i++) {
        if (text[i] == '\n' && text[i - 1] != '\n') paragraphs_count++;
    }

    // Output the conclusion
    if (paragraphs_count >= desired_length) {
        printf("Horaaay, you finish your essay!\n");

        return 0;
    } else {
        printf("Patience is bitter, but its fruit is sweet. - Aristotle\n");

        return 1;
    }
}

int main(int argc, char *argv[]) {
    int desired_length, ret_val;;

    // Check the number of arguments and convert them
    if (argc != 3) {
        printf("Usage: %s ESSAY_TXT_FILENAME PARAGRAPH_COUNT\n", argv[0]);

        exit(1);
    }
    desired_length = atoi(argv[2]);

    ret_val = check_essay(argv[1], desired_length);

    return ret_val;
}