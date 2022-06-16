/*  <Intercala>
*   programa dedicado a implementação da ordenação por intercalação dos arquivos
*/

#include <stdio.h>
#include <stdlib.h>
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

int compara(const void *adress_a, const void *adress_b)							// função para comparar os CEPs
{
	return strncmp(((Endereco*)adress_a)->cep,((Endereco*)adress_b)->cep,8);	// strncmp para comparar se o cep é igual, menor ou maior 
}	

int main (int argc, char** argv) {
    FILE *file_a, *file_b, *file_c;     // declara as variaveis do tipo FILE para apontar para os arquivos
    Endereco *address_a, *address_b;    // declara as variaveis do tipo struct Endereco 
    long posicao, qtd;                  // declara posicao para salvar a o tamanho em bytes e qtd para tamanho de registros endereco

    file_a = fopen("cep_a.dat", "rb");  // abre arquivo cep_a.dat no modo read binary 
    file_b = fopen("cep_b.dat", "rb");  // abre arquivo cep_b.dat no modo read binary
    file_c = fopen("cep_c.dat", "wb");  // abre arquivo/cria cep_c.dat no modo write binary
    
    fseek(file_a,0,SEEK_END);                               // fseek para percorrer todo o arquivo a
    posicao = ftell(file_a);	                            // achar o tamanho do arquivo em bytes
    qtd = posicao/sizeof(Endereco);					        // achar o tamanho do arquivo em registros de endereco
	address_a = (Endereco*) malloc(qtd*sizeof(Endereco));   // alocar memória do tamanho do arquivo a

    fseek(file_b,0,SEEK_END);                               // fseek para percorrer todo o arquivo b
    posicao = ftell(file_b);                                // achar o tamanho do arquivo em bytes
    qtd = posicao/sizeof(Endereco);	                        // achar o tamanho do arquivo em registros de endereco
    address_b = (Endereco*) malloc(qtd*sizeof(Endereco));   // alocar memória do tamanho do arquivo b

    fread(&address_a,sizeof(Endereco),qtd,file_a);   // ler endereco por endereco do arquivo file_a e aloca em address_a
    fread(&address_b,sizeof(Endereco),qtd,file_b);   // ler endereco por endereco do arquivo file_b e aloca em address_b

    while (!feof(file_a) && !feof(file_b)) {                // enquanto file_a e file_b não estiverem vazio
        if (compara(&address_a, &address_b) < 0) {
            fwrite(&address_a,sizeof(Endereco),qtd,file_c);    // escreve Endereco por Endereco que está na memória 'address_a' para o arquivo file_c
            fread(&address_a,sizeof(Endereco),qtd,file_a);
        } else {
            fwrite(&address_b,sizeof(Endereco),qtd,file_c);
            fread(&address_b,sizeof(Endereco),qtd,file_b);
        }
    }

    while (!feof(file_a)) {
        fwrite(&address_a,sizeof(Endereco),qtd,file_c);
        fread(&address_a,sizeof(Endereco),qtd,file_a);
    }

    while (!feof(file_b)) {
        fwrite(&address_b,sizeof(Endereco),qtd,file_c);
        fread(&address_b,sizeof(Endereco),qtd,file_b);
    }

    free(address_a);
    free(address_b);

    fclose(file_a);
    fclose(file_b);
    fclose(file_c);

    return 0;
}