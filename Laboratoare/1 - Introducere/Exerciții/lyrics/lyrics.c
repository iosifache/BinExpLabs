#include <stdio.h>
#include <unistd.h>

const char *lyrics[] = {
    "Un paso me voy para siempre",
    "Un paso fuerte",
    "Un paso hacia adelante",
    "Dos pasos, me voy sin mirarte",
    "Tan lejos pisé",
    "Dos pasos y ya te olvidé",
    "Tres pasos ya soy hacia al este",
    "El sur, el oeste",
    "Tres pasos creo mucho, me parece",
    "¿Y cuándo volverás?",
    "Je ne reviendrai pas",
    "¿Cuándo volverás?",
    "Je suis si loin déjà",
    "¿Y cuándo volverás?",
    "Un dia o jamás",
    "¿Y cuándo volverás?",
    "J'ai fait le premier pas",
    "¿Cuando volverás?",
    "Surtout ne m'attends pas",
    "¿Cuándo volverás?",
    "Un día o jamás",
    "Quatro pasos quiero acordarme",
    "Quatro pasos ya sé",
    "Tu me quisiste, yo te quise",
    "Cinco pasos ya sin perderme",
    "Tanto me alejé",
    "Cinco pasos y te perdoné",
    "Seis pasos ya, son casi siete",
    "Contar más no sé",
    "Mil pasos y más, me quedo de pie...",
    "¿Y cuándo volverás?",
    "Je ne reviendrai pas",
    "¿Cuándo volverás?",
    "Je suis si loin déjà",
    "¿Y cuándo volverás?",
    "Un dia o jamás",
    "¿Y cuándo volverás?",
    "Surtout ne m'attends pas",
    "¿Cuando volverás?",
    "J'ai fait le premier pas",
    "¿Cuando volverás?",
    "Un día o jamás",
    "Un paso, dos pasos, tres pasos, cuatro pasos, cinco pasos...",
    "Mil pasos...",
    "¿Y cuándo volverás?",
    "Je ne reviendrai pas",
    "¿Cuándo volverás?",
    "Je suis si loin déjà",
    "¿Y cuándo volverás?",
    "Un dia o jamás",
    "¿Y cuándo volverás?",
    "Surtout ne m'attends pas",
    "¿Cuando volverás?",
    "J'ai fait les mille pas",
    "¿Cuando volverás?",
    "Un día o jamás",
    "¿Y cuándo volverás?",
    "Surtout ne m'attends pas",
    "¿Cuando volverás?",
    "J'ai fait mes mille pas",
    "¿Cuando volverás?",
    "Un día o jamás",
    NULL
};

int main() {

    int i = 0;

    while (lyrics[i]) {
        printf("%s\n", lyrics[i]);
        sleep(i);

        i++;
    }

    return 0;

}