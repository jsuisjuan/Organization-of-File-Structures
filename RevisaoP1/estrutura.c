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

int main(int argc, char** argv) {
    FILE *f /*saida*/;
    sinasc s;
    long tamBytes, tamRegistros;
    int qtd;

    f = fopen("sinasc-sp-2018.dat", "rb");
    fseek(f,0,SEEK_END);

    tamBytes = ftell(f);
    tamRegistros = tamBytes/sizeof(sinasc);

    printf("\tRevisao de Organizacao de Estrutura de Dados\n\n");
    printf("Questao 1: tamanho do arquivo em bytes: %ld\n", tamBytes);
    printf("Questao 1: tamanho de cada registro: %ld\n", sizeof(sinasc));
    printf("Questao 1: tamanho do arquivo em registros: %ld\n", tamRegistros);

    fclose(f);
    
    /*
    printf("Questao 4: gerando arquivo...\n");

    char codCapital[] = "355030";

    f = fopen("sinasc-sp-2018.dat", "rb");
    saida = fopen("sinasc-sp-capital-2018.dat", "ab");

    qtd = fread(&s,sizeof(sinasc),1,f);
    while (qtd > 0) {
        if (strncmp(s.CODMUNNASC,codCapital,6) == 0) {
            fwrite(&s,sizeof(sinasc),1,saida);
        }
        qtd = fread(&s,sizeof(sinasc),1,f);
    }

    fclose(f);
    fclose(saida);
    */

    /*
    printf("Questão 5:\n");

    char feminino[] = "2";
    char codCidade[] = "354850";
    int numNascMenina = 0;

    f = fopen("sinasc-sp-2018.dat","rb");
    qtd = fread(&s,sizeof(sinasc),1,f);
    while (qtd > 0) {
        if (strncmp(s.SEXO,feminino,1) == 0 && strncmp(s.CODMUNNASC,codCidade,6) == 0) {
            numNascMenina++;
        }
        qtd = fread(&s,sizeof(sinasc),1,f);
    }

    printf("Questao 5: numero de nascimento de meninas em Santos e %d\n", numNascMenina);

    fclose(f);
    */

    printf("Questao 6:\n");

    char abaixoPeso[] = "2500";
    char codCidade[] = "350950";
    int numNascimento = 0;

    f = fopen("sinasc-sp-2018.dat","rb");
    qtd = fread(&s,sizeof(sinasc),1,f);
    while (qtd > 0) {
        if (strncmp(s.CODMUNNASC,codCidade,6) == 0) {
            int peso = atoi(s.PESO);
            if (peso < 2500) {
                numNascimento++;
            }
        }
        qtd = fread(&s,sizeof(sinasc),1,f);
    }

    printf("Questao 6: numero de nascimento de meninas em Santos e %d\n", numNascimento);

    fclose(f);
    
    return 0;
}