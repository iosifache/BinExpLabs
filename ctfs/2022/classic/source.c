#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 64
#define MAX_NAME_SIZE 256

void greet() {
    char name[BUFFER_SIZE];

    memset(name, 0, BUFFER_SIZE);
    puts("Să facem cunoștință. Care este numele tău?");
    fgets(name, MAX_NAME_SIZE, stdin);
    printf("Îmi pare bine, %s", name);

}

int main() {
    puts("Salutare!");
    greet();

    return 0;
}