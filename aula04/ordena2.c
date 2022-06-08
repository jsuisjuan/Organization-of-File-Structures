/*	<Ordena 2>
*	programa dedicado a ordenar um arquivo e criar dois outros arquivos dividos pelo metade
*/

#include <stdio.h>		// declaração da biblioteca stdio.h
#include <stdlib.h>		// declaração da biblioteca stdlib.h
#include <string.h>		// declaração da biblioteca string.h

typedef struct _Endereco Endereco;	// declaração da struct _Endereco como 'Endereco'	

struct _Endereco			// struct 'Endereco'	
{
	char logradouro[72];	// string para nomear logradouro do Endereco
	char bairro[72];		// string para nomear bairro do Endereco	
	char cidade[72];		// string para nomear cidade do Endereco
	char uf[72];			// string para nomear uf/Estado do Endereco
	char sigla[2];			// string para nomear sigla do Estado do Endereco
	char cep[8];			// string para nomear cep do Endereco
	char lixo[2];			// espaço + quebra linha
};

int compara(const void *e1, const void *e2)							// função compara com dois ceps como parametro
{
	return strncmp(((Endereco*)e1)->cep,((Endereco*)e2)->cep,8);	// função strncmp() para comparar os dois ceps se é igual, menor ou maior
}

int main(int argc, char**argv)	// função main com os parametros argc e argv
{
	FILE *f, *saida;			// declaração de uma variável do tipo FILE para ser um ponteiro para um arquivo f e saida
	Endereco *e;				// declaração de uma variável do tipo struct Endereco 'e'
	long posicao, qtd, metade;	// declaração de variáveis do tipo long posicao, qtd e metade

	f = fopen("cep.dat","rb");	// abrir o arquivo 'cep.dat' no modo read binary e alocar em 'f'
	fseek(f,0,SEEK_END);		
	posicao = ftell(f);
	qtd = posicao/sizeof(Endereco);
	metade = qtd/2;
	e = (Endereco*) malloc(metade*sizeof(Endereco));
	rewind(f);
	if(fread(e,sizeof(Endereco),metade,f) == metade)
	{
		printf("Lido = OK\n");
	}
	qsort(e,metade,sizeof(Endereco),compara);
	printf("Ordenado = OK\n");
	saida = fopen("cep_a.dat","wb");
	fwrite(e,sizeof(Endereco),metade,saida);
	fclose(saida);
	printf("Escrito = OK\n");
	free(e);

	e = (Endereco*) malloc((qtd-metade)*sizeof(Endereco));
	if(fread(e,sizeof(Endereco),qtd-metade,f) == qtd-metade)
	{
		printf("Lido = OK\n");
	}
	qsort(e,qtd-metade,sizeof(Endereco),compara);
	printf("Ordenado = OK\n");
	saida = fopen("cep_b.dat","wb");
	fwrite(e,sizeof(Endereco),qtd-metade,saida);
	fclose(saida);
	printf("Escrito = OK\n");
	free(e);

	fclose(f);
}

