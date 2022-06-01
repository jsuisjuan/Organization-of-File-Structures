#include <stdio.h>
#include <stdlib.h>

#define N 1000000

int particiona(int *vet, int inicio, int fim)
{
	int i, aux, pivo, temp;
	aux = inicio-1;
	pivo = vet[fim];
	for(i=inicio; i<=fim; i++)
	{
		if(vet[i] <= pivo)
		{
			aux++;
			temp = vet[i];
			vet[i] = vet[aux];
			vet[aux] = temp;
		}
	}
	return aux;
}

void quick(int *vet, int inicio, int fim)	// função do quicksort
{
	int p;
	if(inicio < fim)
	{
		p = particiona(vet,inicio,fim); // N
		quick(vet,inicio,p-1);
		quick(vet,p+1,fim);
	}
}

void sel(int *vet, int inicio, int fim)		// função do selectionsort
{
	int i, maior, temp;
	while(inicio < fim)
	{
		maior = fim;
		for(i = inicio; i < fim; i++)
		{
			if(vet[i] > vet[maior])
			{
				maior = i;
			}
		}
		if(maior != fim)
		{
			temp = vet[maior];
			vet[maior] = vet[fim];
			vet[fim] = temp;
		}
		fim--;
	}
}

int main(int argc, char** argv)
{
  int vet[N], i;	// declared variables
  for(i=0; i<N; i++)
  {
      vet[i] = random() % 100000;	// generate random 100000 numbers 
  }
  for(i=0; i<N; i++)
  {
       printf("%d ",vet[i]); 	
  }
  printf("\n");
  quick(vet,0,N);
  for(i=0; i<N; i++)
  {
       printf("%d ",vet[i]);
  }
  printf("\n");
  return 0;
}


