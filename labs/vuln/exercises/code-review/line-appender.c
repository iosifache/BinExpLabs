#include <stdio.h>

void append_files(char source_filename[], char destination_filename[]){
    FILE *source, *destination;
    char buf[100];

    source = fopen(source_filename, "r");
    destination = fopen(destination_filename, "a+");

    if (!source && !destination) {
        printf("[!] Files cannot be accessed.\n");

        return;
    }
    else{
        printf("[!] Appending the content of %s to %s.", source_filename, destination_filename);
    }

    fprintf(destination, "\n");

    fgets(buf, sizeof(buf), source);
    fprintf(destination, "%s", buf);
}

int main(int argc, char *argv[]){
    char *source, *destination;

    if (argc != 3){
        printf("[!] Source and destination files were not provided.\n");

        return -1;
    }
    source = argv[1];
    destination = argv[2];

    append_files(source, destination);

    return 0;
}