// Programa em que le os dados do arquivo loremipsum.txt  
// e imprime a quantidade media das letras em cada palavra do arquivo

#include <stdio.h>

int main() {
    FILE *entrada;
    float letras, espacos;
    int c;

    letras = 0;
    espacos = 0;

    entrada = fopen("./lab1/loremipsum.txt", "r");
    if (!entrada) {
        printf("Arquivo não pode ser aberto para leitura\n");
        return 1;
    }

    c = fgetc(entrada);
    while (c != EOF) {
        if (c == ' ') {
            espacos++;
        } else {
            letras++;
        }
        c = fgetc(entrada);
    }

    printf("Media das letras por palavra: %.1f", letras/(espacos+1));

    fclose(entrada);
    return 0;
}