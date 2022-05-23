#include <stdio.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco {
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2];
};

void buscaBinaria(long fim, FILE* entrada, char* procurar) {
    long inicio = 0;
    int quantidade;
    Endereco e;

    while (inicio <= fim) {
        int meio = (inicio + fim)/2;

        fseek(entrada, meio*300, SEEK_SET);
        quantidade = fread(&e, sizeof(Endereco), 1, entrada);

        if (strncmp(procurar, e.cep, 8) == 0) {
            printf("%.8s\n", e.cep);
            break;
        } if (strncmp(procurar, e.cep, 8) < 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }
}

int main(int argc, char** argv) {
    FILE* entrada;
    Endereco e;
    long tamBytes, tamRegistro;

    if (argc != 2) {
        fprintf(stderr, "USO: %s [CEP]", argv[0]);
        return 1;
    }

    entrada = fopen("cep_ordenado.dat", "rb");
    fseek(entrada, 0, SEEK_END);

    tamBytes = ftell(entrada);
    tamRegistro = tamBytes/sizeof(Endereco);

    printf("Tamanho do arquivo em bytes: %ld\n", tamBytes);
    printf("Tamanho do arquivo em registros: %ld\n", tamRegistro);

    long fim = tamRegistro - 1;

    buscaBinaria(fim, entrada, argv[1]);

    fclose(entrada);
    return 0;
}