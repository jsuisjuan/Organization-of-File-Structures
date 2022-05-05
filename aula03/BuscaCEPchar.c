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

int main(int argc, char**argv) {
    FILE *entrada;
    Endereco endereco;
    int quantidade;
    int c;

    if (argc != 2) {
        fprintf(stderr, "USO: %s [CEP]", argv[0]);
        return 1;
    }

    c = 0;
    printf("Tamanho da Estrutura: %ld\n\n", sizeof(Endereco));
    entrada = fopen("cep.dat", "r");
    quantidade = fread(&endereco,sizeof(Endereco),1,entrada);
    while (quantidade > 0) {
        c++;
        endereco.logradouro[71] = '\0';
        if (strstr(endereco.logradouro, argv[1])) {
            printf("%.72s\n", endereco.logradouro);
        }
        quantidade = fread(&endereco,sizeof(Endereco),1,entrada);
    }
    printf("Total Lido: %d\n", c);
    fclose(entrada);

    return 0;
}