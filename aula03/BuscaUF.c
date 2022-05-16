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

int main() {
    FILE *entrada, *saida = NULL;
    Endereco e;

    char ufAtual[2] = "";
    char nomeArquivo[12];
    int qt;

    entrada = fopen("cep.dat", "rb");

    qt = fread(&e,sizeof(Endereco),1,entrada);

    while(qt > 0) {
        if (strstr(ufAtual, e.sigla)) {
            fwrite(&e,sizeof(Endereco),qt,saida);
        } else {
            if (saida != NULL) {
                fclose(saida);
            }
            strncpy(ufAtual,e.sigla,2);

            sprintf(nomeArquivo, "cep_%.2s.dat", e.sigla);
            saida = fopen(nomeArquivo, "ab");
            fwrite(&e,sizeof(Endereco),qt,saida);
        }
        qt = fread(&e,sizeof(Endereco),1,entrada);
    }
    fclose(entrada);
    fclose(saida);
    return 0;
}