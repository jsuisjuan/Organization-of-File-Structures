#include "heap.h"
#include <iostream>

using namespace std;

Heap* criaHeap()
{
	Heap *h = new Heap;
	h->qt = 0;
	return h;
}

void destroiHeap(Heap* h)
{
	delete h;
}

void insere(Heap* h, int x)
{
	int pai, filho, aux;

	h->elementos[h->qt] = x; // coloca novo no final do array
	filho = h->qt; // indice do filho
	h->qt++;

	while(filho > 0)
	{
		pai = ((filho+1)/2)-1;
		if(h->elementos[pai]<h->elementos[filho])
		{
			aux = h->elementos[pai];
			h->elementos[pai] = h->elementos[filho];
			h->elementos[filho] = aux;
			filho = pai;
		}
		else
		{
			break;
		}
	}
}

int remove(Heap* h)
{
	int resposta, pai, filho1, filho2, maiorFilho, aux;

	resposta = h->elementos[0];
	h->elementos[0] = h->elementos[h->qt-1];
	h->elementos[h->qt-1] = resposta;
	h->qt--;

	pai = 0;
	filho1 = 2*(pai+1)-1;
	filho2 = filho1+1;
	while(filho1<h->qt)
	{
		if(filho2<h->qt)
		{
			if(h->elementos[filho1]>h->elementos[filho2])
			{
				maiorFilho = filho1;
			}
			else
			{
				maiorFilho = filho2;
			}
		}
		else
		{
			maiorFilho = filho1;
		}
		if(h->elementos[pai]<h->elementos[maiorFilho])
		{
			aux = h->elementos[pai];
			h->elementos[pai] = h->elementos[maiorFilho];
			h->elementos[maiorFilho] = aux;
			pai = maiorFilho;
			filho1 = 2*(pai+1)-1;
			filho2 = filho1+1;
		}
		else
		{
			break;
		}
	}

	return resposta;
}

void imprimeHeap(Heap *h)
{
	int i;
	for(i=0; i<h->qt; i++)
	{
		cout << h->elementos[i] << ", ";
	}
	cout << endl;

}

