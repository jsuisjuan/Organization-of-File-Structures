#include <stdio.h>	// biblioteca em que apresenta as funções padrões do C (stdio = standard input ouput)

// stdout, stdin, stderr
// argv[] = {copia1, A, B}
int main(int argc, char** argv)	// os parametros argc(quantidade de argumentos) e argv(pontoeiro para os argumentos)
{
	FILE *entrada, *saida;	// ponteiro para arquivo A (entrada) e B(saída)
	int c;					// variável de armazenamento de dados

	if(argc != 3)			// verificar se a quantidade de argumentos é igual a 3
	{
		fprintf(stderr,"Erro na chamada do comando.\n");							// stderr: utilizado para indicar erro
		fprintf(stderr,"Uso: %s [ARQUIVO ORIGEM] [ARQUIVO DESTINO].\n", argv[0]);	// %s = tipo char *
		return 1;	// valores != 0: indica erro no programa
	}

	entrada = fopen(argv[1],"rb");	// fopen: abrir arquivo r(read) e b(binary) A para copiar
	if(!entrada)
	{
		fprintf(stderr,"Arquivo %s não pode ser aberto para leitura\n", argv[1]);
		return 1;
	}

	saida = fopen(argv[2],"wb");	// abrir o arquivo w(write) e b(binary) B para colar
	if(!saida)
	{
		fclose(entrada);	// fclose: fechar arquivo
		fprintf(stderr,"Arquivo %s não pode ser aberto para escrita\n", argv[2]);
		return 1;
	}

	c = fgetc(entrada);	// fgetc: pegar os dados (bite por bite) do arquivo A 
	while(c != EOF)		// EOF stands for End of File. The function getc() returns EOF, on success..
	{
		fputc(c, saida);	// fputc: enviar os dados (bite por bite) da variável c para B
		c = fgetc(entrada);
	}

	fclose(entrada);	
	fclose(saida);
	return 0;
}

