#include <stdio.h>

#define BUFFER_SIZE 16
#define INPUT_SIZE 32

void demo() {
    char buffer[BUFFER_SIZE];

    printf("Pentru ați demonstra acest lucru, am un buffer pe care poți să îl suprascrii printr-un payload:\n");
    fread(buffer, 64, 1, stdin);
}

int main() {

    printf("Acest program este protejat cu mai multe mecanisme de protecție.");

    demo();

    return 0;
}