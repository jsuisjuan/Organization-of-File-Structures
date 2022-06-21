#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _sinasc sinasc;

struct _sinasc {
    char CODMUNNASC[6]; /* Código do Município de Nascimento */
    char CODESTAB[7]; /* Código do Estabelecimento */
    char CODMUNRES[6]; /* Código do Município de Residência */
    char DTNASC[8]; /* Data de Nascimento no formato DDMMAAAA */
    char SEMAGESTAC[2]; /* Número de Semanas de Gestação */
    char SEXO[1]; /* Sexo 0 não informado, 1 Masculino ou 2 Feminino */
    char PESO[4]; /* Peso em gramas */
    char DTNASCMAE[8]; /* Data de Nascimento no formato DDMMAAAA */
};

int compara (const void *e1, const void *e2) {
    return strncmp(((sinasc*)e1)->CODMUNNASC,((sinasc*)e2)->CODMUNNASC,6);
}

int main (int argc, char** argv) {
    FILE *f;
    sinasc *s;
    long tamBytes, tamRegistros;

    f = fopen("sinasc-sp-2018.dat","r");
    fseek(f,0,SEEK_END);
    tamBytes = ftell(f);
    tamRegistros = tamBytes/sizeof(sinasc);
    s = (sinasc*) malloc(tamRegistros);
    if (s == NULL) {
        printf("Erro: nao consegui alocar a memoria\n");
        fclose(f);
        return 1;
    }
    rewind(f);
    if (fread(s,sizeof(sinasc),tamRegistros,f) == tamRegistros) {
        printf("Lido = OK\n");
    }
    fclose(f);
    qsort(s,tamRegistros,sizeof(sinasc),compara);
    printf("Ordenado = OK\n");
    f = fopen("sinasc-sp-2018-ordenado.dat","w");
    fwrite(s,sizeof(sinasc),tamRegistros,f);
    fclose(f);
    printf("Escrito = OK\n");
    free(s);
    return 0;
}