#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 16

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

int comparaCep(const void *e1, const void *e2)
{
	return strncmp(((Endereco*)e1)->cep,((Endereco*)e2)->cep,8);
}

void intercalaCep(char* arq1, char* arq2, char* resultado)
{
	FILE *a, *b, *saida;
	Endereco ea, eb;
	int sizereg = sizeof(Endereco);	
	
	a = fopen(arq1,"r");
	b = fopen(arq2,"r");
	saida = fopen(resultado,"w");
	
	fread(&ea,sizereg,1,a);
	fread(&eb,sizereg,1,b);
	
	while(!feof(a) && !feof(b))
	{
		if(comparaCep(&ea,&eb) < 0)
		{
			fwrite(&ea,sizereg,1,saida);
			fread(&ea,sizereg,1,a);	
		}
		else
		{
			fwrite(&eb,sizereg,1,saida);
			fread(&eb,sizereg,1,b);	
		}
	}
	
	while(!feof(a))
	{
		fwrite(&ea,sizereg,1,saida);
		fread(&ea,sizereg,1,a);				
	}
		
	while(!feof(b))
	{
		fwrite(&eb,sizereg,1,saida);
		fread(&eb,sizereg,1,b);			
	}

	fclose(a);
	fclose(b);
	fclose(saida);
}

int main()
{
	FILE *origem;
	Endereco *buffer, *buffer2;
	int tamarq, tamreg, registros, qtd, qtd_ultimo, n, controle, b, aux;
	char strcep[10], arq1[10], arq2[10], resultado[10];
	
	origem = fopen("cep.dat","r");
	fseek(origem,0,SEEK_END);
	tamarq = ftell(origem);
	tamreg = sizeof(Endereco);
	registros = tamarq / tamreg;
	printf("Registros: %d\n",registros);
	
	qtd = registros/N;
	qtd_ultimo = qtd + registros%N;
	printf("Qtd de registros de cada um dos %d blocos: %d\n",N-1,qtd);
	printf("Qtd de registros do %dº bloco: %d\n\n",N,qtd_ultimo);
	buffer = (Endereco*) malloc(qtd*tamreg);
	buffer2 = (Endereco*) malloc(qtd_ultimo*tamreg);
	rewind(origem);

	for(int i=1;i<=N;i++)
	{
		sprintf(strcep,"cep%d.dat",i);
		FILE *f = fopen(strcep,"w");
		if(i<N)
		{
			fread(buffer,tamreg,qtd,origem);
			qsort(buffer,qtd,tamreg,comparaCep);
			fwrite(buffer,tamreg,qtd,f);			
		}
		else
		{
			fread(buffer2,tamreg,qtd_ultimo,origem);
			qsort(buffer2,qtd_ultimo,tamreg,comparaCep);
			fwrite(buffer2,tamreg,qtd_ultimo,f);			
		}

		fclose(f);
	}
	
	/*- n é a quantidade de blocos por rodada. Ex.: 16,8,4...
			Ajuda a definir até quando o 1º while funcionará.
		- controle é a quantidade máxima de blocos que podem ser
			intercalados até uma determinada rodada.
			Ex.: 16,24,28...
		-	b é o inteiro que dá nome ao arquivo de cep.
			Ex.: 1,2,3,4...29,30,31
		- aux é uma variável auxiliar para dar nome ao arquivo
			do resultado de uma intercalação.*/ 
			
	n = controle = N;
	b = 1;
	while(n>=2)
	{
		aux = 1;
		while(b<=controle)
		{
			sprintf(arq1,"cep%d.dat",b);
			sprintf(arq2,"cep%d.dat",b+1);
			sprintf(resultado,"cep%d.dat",controle+aux);
			printf("Intercalando %s com %s e gerando %s\n",arq1,arq2,resultado);
			intercalaCep(arq1,arq2,resultado);
			remove(arq1);
			remove(arq2);
			aux++;
			b+=2;
		}
		n/=2;
		controle+=n;
	}
	
	char nome_antigo[10];
	sprintf(nome_antigo,"cep%d.dat",b);
	rename(nome_antigo,"cep_ordenado.dat");

	printf("\ncep_ordenado.dat criado por intercalação com %d blocos iniciais.\n\n",N);

	fclose(origem);
	return 0;
}