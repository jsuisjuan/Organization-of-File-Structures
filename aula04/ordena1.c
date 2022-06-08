/*	<Ordena 1>
*	programa dedicado a ordenar um arquivo e criar outro arquivo ordenado
*/

#include <stdio.h>		// declaração da biblioteca stdio.h
#include <stdlib.h>		// declaração da biblioteca stdlib.h
#include <string.h>		// declaração da biblioteca string.h

typedef struct _Endereco Endereco;	// declaração da struct _Endereco como 'Endereco'

struct _Endereco					// struct 'Endereco'
{
	char logradouro[72];			// string para nomear logradouro do Endereco
	char bairro[72];				// string para nomear bairro do Endereco
	char cidade[72];				// string para nomear cidade do Endereco
	char uf[72];					// string para nomear uf/Estado do Endereco
	char sigla[2];					// string para nomear sigla do Estado do Endereco
	char cep[8];					// string para nomear cep do Endereco
	char lixo[2];					// espaço + quebra linha
};

int compara(const void *e1, const void *e2)							// função para comparar os CEPs
{
	return strncmp(((Endereco*)e1)->cep,((Endereco*)e2)->cep,8);	// strncmp para comparar se o cep é igual, menor ou maior 
}																	// para a função qsort funcionar

int main(int argc, char**argv)			// função main com os parametros argc e argv
{
	FILE *f;							// declaração da variável do tipo FILE para apontar para o arquivo
	Endereco *e;						// declaração da variável do tipo struct Endereco 'e'
	long posicao, qtd;					// declaração da variável do tipo long para indicar a posição e quantidade

	f = fopen("cep.dat","rb");			// abrir o arquivo 'cep.dat' no modo read binary e armazenar em 'f'
	fseek(f,0,SEEK_END);				// função fseek() para percorrer pelos bytes do arquivo 'f' do registro 0 até o fim
	posicao = ftell(f);					// função ftell() para imprimir o tamanho em bytes do arquivo 'f' e alocar em posição
	qtd = posicao/sizeof(Endereco);		// calcula o tamanho do arquivo em registros e alocar em 'qtd'
	e = (Endereco*) malloc(posicao);	// cria um registro/alocar memória do tipo Endereco do tamanho de um Endereco 
	if(e == NULL) {
		printf("Erro: Nao consegui alocar a memoria\n");	// se 'e' for vazio, imprimir erro
		fclose(f);											// fechar o arquivo 'f'
		return -1;											// retornar -1 para indicar erro
	}
	rewind(f); 												// vai para o inicio do arquivo 'f'
	if(fread(e,sizeof(Endereco),qtd,f) == qtd) {			// se (le um Endereco/Entidade por registro do arquivo 'f' e armazenar no registro em 'e') for igual 'qtd' imprime lido
		printf("Lido = OK\n");
	}
	fclose(f);												// fechar arquivo 'f'
	qsort(e,qtd,sizeof(Endereco),compara);					// declaração da função qsort() para ordenar o arquivo
	printf("Ordenado = OK\n");								// imprimir que foi ordenado caso a função funcione
	f = fopen("cep_ordenado2.dat","wb");					// abrir/criar um arquivo chamado 'cep_ordenado2.dat' no modo write binary
	fwrite(e,sizeof(Endereco),qtd,f);						// escrever um Endereco/Entidade por registro do arquivo 'f' e armazenar no registro em 'e'
	fclose(f);												// fechar o arquivo 'f'
	printf("Escrito = OK\n");								
	free(e);												// liberar/fechar a memoria alocada
}

