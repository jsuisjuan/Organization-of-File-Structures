#ifndef __HEAP_H__
#define __HEAP_H__

#define N 2000

struct Heap
{
	int elementos[N];
	int qt;
};

Heap* criaHeap();
void destroiHeap(Heap* h);
void insere(Heap* h, int x);
int remove(Heap* h);
void imprimeHeap(Heap* h);

#endif


