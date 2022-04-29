// Programa em que calcula a quantidade de linhas em um arquivo texto
#include <stdio.h>

int main() {
    FILE *arquivo;
    int c, i = 1;

    arquivo = fopen("teste-linha.txt", "rb");
    if (!arquivo) {
        printf("Arquivo nao esta abrindo.");
        return 1;
    }

    c = fgetc(arquivo);
    while (c != EOF) {
        if (c == '\n') {
            i++;
        }
        c = fgetc(arquivo);
    }

    printf("Quantidade de Linhas: %d", i);
    fclose(arquivo);

    return 0;
}