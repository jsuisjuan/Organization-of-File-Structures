#include "heap.h"
#include <iostream>

using namespace std;

int main()
{
	Heap* h = criaHeap();

	insere(h,10);
	insere(h,20);
	insere(h,30);
	insere(h,1);
	insere(h,2);
	insere(h,3);

	imprimeHeap(h);

	cout << remove(h) << endl;	
	cout << remove(h) << endl;	
	cout << remove(h) << endl;	
	cout << remove(h) << endl;	
	cout << remove(h) << endl;	
	cout << remove(h) << endl;	

	for(int i=0; i<6; i++) {
		cout << h->elementos[i] << ",";
	}
	cout << endl;

	destroiHeap(h);
	return 0;
}