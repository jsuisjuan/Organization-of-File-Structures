#include <stdio.h>

#define TAMANHO 4096	// tamanho dos bits

int main(int argc, char** argv)
{
	FILE *entrada, *saida;
	char buffer[TAMANHO];	// cria um buffer com espaço de 4096 bits
	int qtd;				// variavel para armazenar a quantidade 

	if(argc != 3)
	{
		fprintf(stderr,"Erro na chamada do comando.\n");
		fprintf(stderr,"Uso: %s [ARQUIVO ORIGEM] [ARQUIVO DESTINO].\n", argv[0]);
		return 1;
	}

	entrada = fopen(argv[1],"r");
	if(!entrada)
	{
		fprintf(stderr,"Arquivo %s não pode ser aberto para leitura\n", argv[1]);
		return 1;
	}

	saida = fopen(argv[2],"w");
	if(!saida)
	{
		fclose(entrada);
		fprintf(stderr,"Arquivo %s não pode ser aberto para escrita\n", argv[2]);
		return 1;
	}

	qtd = fread(buffer,1,TAMANHO,entrada);		// le 4096 bits (bits por bits == 1) do arquivo entrada e armazena no buffer
	while(qtd > 0)								// enquanto o buffer não estiver vazio, ele vai dar loop
	{
		fwrite(buffer,1,qtd,saida);  			// copia os dados que estavam no buffer para o arquivo de saída
		qtd = fread(buffer,1,TAMANHO,entrada);	// aloca mais bits do arquivo de entrada para o buffer
	}

	fclose(entrada);
	fclose(saida);
	return 0;
}

