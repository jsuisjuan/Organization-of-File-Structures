/*	<!-- BuscaCEP -->
*	Este é um programa que busca por um determinado CEP
*	caso ele exista. Basta colocar o CEP desejado como
*	argumento: gcc -o teste buscaCEP.c 24431690
*/

/* <!-- Exemplo --> ./BuscaCEP.exe 24431690
*	Rua Jose Saly   -> logradouro
*	Porto Novo		-> bairro
*	São Gonçalo		-> cidade
*	Rio de Janeiro	-> uf
*	RJ				-> sigla
* 	24431690		-> cep
*/

#include <stdio.h>	// inclue a biblioteca stdio.h
#include <string.h>	// inclue a biblioteca string.h

typedef struct _Endereco Endereco;	// atribui o nome da struct como 'Endereco'


struct _Endereco					// struct 'Endereco'	
{
	char logradouro[72];			// string para nomear logradouro
	char bairro[72];				// string para nomear o bairro
	char cidade[72];				// string para nomear a cidade
	char uf[72];					// string para nomear a uf/Estado
	char sigla[2];					// string para nomear a sigla do Estado
	char cep[8];					// string para nomear o CEP
	char lixo[2]; 					// Ao Espaço no final da linha + quebra de linha
};

int main(int argc, char**argv)		// função main incluindo a quantidade de argumentos e o ponteiro para eles
{
	FILE *f;		// variável do tipo FILE que será um ponteiro para um arquivo
	Endereco e;		// variável do tipo struct Endereco
	int qt;			// variável do tipo inteiro para armazenar a transferencia de bits
	int c;			// variável do tipo inteiro para armazenar a quantidade de endereços lidos até encontrar o CEP desejado

	if(argc != 2)									// se não entrar 2 argumentos na função (programa + CEP)
	{												// imprimir uma mensagem de erro e returnar erro
		fprintf(stderr, "USO: %s [CEP]", argv[0]);
		return 1;
	}

	c = 0;
	printf("Tamanho da Estrutura: %ld\n\n", sizeof(Endereco));	// sizeof: soma o tamanho dos items da struct: 300
	f = fopen("cep.dat","r"); 									// abre o arquivo 'cep.dat' no mode 'read'
	qt = fread(&e,sizeof(Endereco),1,f);						// le um Endereco/Entidade por vez do arquivo f(cep.dat) e armazenar no registro em 'e' que é do tipo Endereco

	while(qt > 0)	// em quanto 								
	{
		c++;
		// argv[1] < e.cep  => strcmp(argv[1],e.cep) < 0
		// argv[1] > e.cep  => strcmp(argv[1],e.cep) > 0
		// argv[1] == e.cep  => strcmp(argv[1],e.cep) == 0
		e.logradouro[71] = '\0';
		// pode usar o strstr
		if(strncmp(argv[1],e.cep,8)==0)		// se o CEP buscado for igual ao CEP desejado, imprime todas as informações desse lugar
		{
			printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
			break;
		}
		qt = fread(&e,sizeof(Endereco),1,f);		
	}
	printf("Total Lido: %d\n", c);		// imprimir a quantidade de endereços lidos até achar o CEP desejado
	fclose(f);							// fechar o arquivo 'cep.dat'

	return 0;							// retornar 0 para dizer que o programa funcionou com sucesso
}

