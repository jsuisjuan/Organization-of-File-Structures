/*	<!-- BuscaUF -->
*	Este é um programa que cria arquivos organizados por UF
*/

/* <!-- Exemplo --> ./BuscaUF.exe 
*	cep_RJ.dat
*   cep_SP.dat
*/

#include <stdio.h>
#include <string.h>

typedef struct _Endereco Endereco;  // definindo struct _Endereco para 'Endereco'

struct _Endereco {                  // struct 'Endereco'
    char logradouro[72];            // string para nomear logradouro do Endereco
    char bairro[72];                // string para nomear bairro do Endereco
    char cidade[72];                // string para nomear cidade do Endereco
    char uf[72];                    // string para nomear uf/Estado do Endereco
    char sigla[2];                  // string para nomear sigla do Estado do Endereco
    char cep[8];                    // string para nomear o cep do Endereco
    char lixo[2];                   // espaço no final da linha + quebra de linha
};

int main() {
    FILE *entrada, *saida = NULL;   // declaração de duas variáveis do tipo FILE para apontar para dois arquivos
    Endereco e;                     // declaração de uma variável do tipo struct Endereco

    char ufAtual[2] = "";           // declaração de uma variável do tipo char que está vazia
    char nomeArquivo[12];           // declaração de uma variável do tipo char para armazenar o nome do arquivo novo
    int qt;                         // declaração de uma variável do tipo inteiro para armazenar a transferencia de bits

    entrada = fopen("cep.dat", "rb");   // abrir o arquivo 'cep.dat' no modo read binary

    qt = fread(&e,sizeof(Endereco),1,entrada);  // le um Endereco/Entidade por vez do arquivo entrada(cep.dat) e armazenar no registro em 'e' que é do tipo Endereco

    while(qt > 0) {
        if (strstr(ufAtual, e.sigla)) {                     // acredito que ele está função compara ufAtual com a sigla que está no endereço 'e'
            fwrite(&e,sizeof(Endereco),qt,saida);           // escreve um Endereco/Entidade por vez no arquivo saida e armazena no registro em 'e' que é do tipo Endereco
        } else {
            if (saida != NULL) {                            // se ufAtual não for igual a e.sigla, e se o arquivo saida ainda estiver vazio
                fclose(saida);                              // fecha o arquivo saida
            }
            strncpy(ufAtual,e.sigla,2);                     // função que copia de e.sigla para ufAtual

            sprintf(nomeArquivo, "cep_%.2s.dat", e.sigla);  // criar um arquivo com o nome 'cep_***.dat'
            saida = fopen(nomeArquivo, "ab");               // o arquivo novo é aberto no modo ab e alocado no ponteiro saida
            fwrite(&e,sizeof(Endereco),qt,saida);           // escreve um Endereco/Entidade por vez no arquivo saida e armazena no registro em 'e' que é do tipo Endereco
        }
        qt = fread(&e,sizeof(Endereco),1,entrada);
    }
    fclose(entrada);    // fecha arquivo entrada
    fclose(saida);      // fecha arquivo saida
    return 0;
}