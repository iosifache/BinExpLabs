#include <stdio.h>
#include <stdlib.h>

int gifts_count = 32;

void print_letter(char *name) {

    // Print the letter
    printf("\033[31mDear Santa Claus,\n\n");
    printf("My name is:\n\n\t");
    printf(name);
    printf("\n\nI swear I was a good kid, doing all my homework and getting good "
           "grades on all my tests. The only mistake I made this year was "
           "omitting the printf(%%s) usage class :(. As a "
           "result, I think I am deserving of %d gifts.\n\n", gifts_count);
    printf("Hope to see you on Christmas!\n\033[0m");
}

int main(int argc, char *argv[]) {
    int helper = &gifts_count;

    // Check the number of arguments
    if (argc != 2) {
        printf("Usage: %s FULL_NAME\n", argv[0]);

        exit(1);
    }

    print_letter(argv[1]);
}