#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define FLAG_FILE "./flag.txt"
#define FLAG_SIZE 30
#define CHARS_PER_ROW 12
#define ROWS_PER_NUMBER 7
#define CAPTCHA_DIGITS_COUNT 3
#define TIME_TO_SLEEP 1
#define BUFFER_SIZE 30

char flag[FLAG_SIZE] = {0};
const unsigned char digits[10][ROWS_PER_NUMBER][CHARS_PER_ROW] = {
    {   "  #####     ", " ##   ##    ", "##     ##   ", "##     ##   ",
        "##     ##   ", " ##   ##    ", "  #####     "
    },
    {   "    ##      ", "  ####      ", "    ##      ", "    ##      ",
        "    ##      ", "    ##      ", "  ######    "
    },
    {   "  #######   ", " ##     ##  ", "        ##  ", "  #######   ",
        " ##         ", " ##         ", " #########  "
    },
    {   "  #######   ", " ##     ##  ", "        ##  ", "  #######   ",
        "        ##  ", " ##     ##  ", "  #######   "
    },
    {   "  ##        ", "  ##    ##  ", "  ##    ##  ", "  ##    ##  ",
        "  ######### ", "        ##  ", "        ##  "
    },
    {   "  ########  ", "  ##        ", "  ##        ", "  #######   ",
        "        ##  ", "  ##    ##  ", "   ######   "
    },
    {   "   #######  ", "  ##     ## ", "  ##        ", "  ########  ",
        "  ##     ## ", "  ##     ## ", "   #######  "
    },
    {   "   ######## ", "   ##    ## ", "       ##   ", "      ##    ",
        "     ##     ", "     ##     ", "     ##     "
    },
    {   "    ####### ", "   ##     ##", "   ##     ##", "    ####### ",
        "   ##     ##", "   ##     ##", "    ####### "
    },
    {   "    ####### ", "  ##     ## ", "  ##     ## ", "   ######## ",
        "         ## ", "  ##     ## ", "   #######  "
    }
};

void load_flag() {
    FILE *flag_file;

    // Citește flag-ul în variabila globală cu același nume
    flag_file = fopen(FLAG_FILE, "r");
    fread(flag, FLAG_SIZE - 1, 1, flag_file);
    fclose(flag_file);

}

void print_three_digit_captcha(unsigned int number) {
    unsigned number_digits[CAPTCHA_DIGITS_COUNT] = {
        (number / 100) % 10,
        (number / 10) % 10,
        number % 10
    };
    int i, j, k;

    // Afișează caracterele codului CAPTCHA
    for (i = 0; i < ROWS_PER_NUMBER; i++) {
        for (j = 0; j < CAPTCHA_DIGITS_COUNT; j++) {
            for (k = 0; k < CHARS_PER_ROW; k++) {
                putchar(digits[number_digits[j]][i][k]);
            }
        }
        printf("\n");
    }
}

void *kill(void *data) {
    // Omoară procesul după un număr fixat de secunde
    sleep(TIME_TO_SLEEP);
    exit(1);
};

int main() {
    FILE *urandom_file;
    pthread_t kamikaze_thread;
    char flag_to_check[BUFFER_SIZE];
    unsigned int random_number, guessed_number;
    int i;

    load_flag();

    // Generează un număr aleator
    urandom_file = fopen("/dev/urandom", "rb");
    fread(((char *)&random_number), 4, 1, urandom_file);
    fclose(urandom_file);

    // Testează utilizatorul prin CAPTCHA
    printf("Demonstrează că nu ești om prin rezolvarea acestui CAPTCHA:\n\n");
    print_three_digit_captcha(random_number);
    printf("\nIntrodu numărul de mai sus: ");
    pthread_create(&kamikaze_thread, NULL, kill, NULL);
    scanf("%u", &guessed_number);
    if (guessed_number != random_number % 1000) {
        exit(1);
    }

    // Verifică flag-ul de la utilizator
    printf("\nIntrodu flag-ul pe care vrei să îl verifici: ");
    scanf("%s", flag_to_check);
    for (i = 0; i < FLAG_SIZE; i++) {
        if (flag[i] != flag_to_check[i]) {
            printf("Din păcate, flag-ul este incorect. Îți pot spune că până la poziția %d caracterele sunt corecte.\n", i);

            exit(1);
        }
    }
    printf("Felicitări, ai descoperit flag-ul!\n");

    return 0;
}