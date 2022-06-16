#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BATCHES 8

typedef struct _Endereco Endereco;

struct _Endereco {
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

int compara(const void *e1, const void *e2) {
	return strncmp(((Endereco*)e1)->cep,((Endereco*)e2)->cep,8);
}

void writeSortedBatch(int batch_size, int batch_idx, FILE* f) {
	FILE* output; 
	Endereco* e; // buffer
	char filename[13];

	e = (Endereco*) malloc(batch_size * sizeof(Endereco));
	fread(e, sizeof(Endereco), batch_size, f);
	qsort(e, batch_size, sizeof(Endereco), compara);

	sprintf(filename, "batch_%d.dat", batch_idx);
	output = fopen(filename, "wb");
	fwrite(e, sizeof(Endereco), batch_size, output);
	fclose(output);
	free(e);
}

void writeBatches(long totalRegisters, FILE* f) {
	long batch_size, total_written = 0;

	for(int i = 0; i < BATCHES; i++) {
		if (i == BATCHES - 1) {
			batch_size = totalRegisters - total_written;
		} else {
			batch_size = totalRegisters / BATCHES;
		}
		writeSortedBatch(batch_size, i, f);
		total_written += batch_size;
	}
}

void mergeSortedBatches(int* left_batch_idx, int* right_batch_idx, int* next_idx_merged, int* pair_idx) {
	printf("\nProcessing:\n");
	printf("left batch: %d\n", *left_batch_idx);
	printf("right batch: %d\n", *right_batch_idx);
	printf("Pair batches index: %d\n", *pair_idx);
	printf("Batch to be merged: %d\n", *next_idx_merged);

	FILE *file_a, *file_b, *file_c;
	char a_filename[13], b_filename[13], c_filename[13];
	// len("batch_10.dat\0") = 13 (12 DOES NOT WORKS)

	sprintf(a_filename, "batch_%d.dat", *left_batch_idx);
	sprintf(b_filename, "batch_%d.dat", *right_batch_idx);
	sprintf(c_filename, "batch_%d.dat", *next_idx_merged);

	file_a = fopen(a_filename, "rb");
	file_b = fopen(b_filename, "rb");
	file_c = fopen(c_filename, "wb");

	Endereco *address_a, *address_b, *address_c;

	address_a = (Endereco*) malloc(1 * sizeof(Endereco));
	address_b = (Endereco*) malloc(1 * sizeof(Endereco));

	fread(address_a, sizeof(Endereco), 1, file_a);
	fread(address_b, sizeof(Endereco), 1, file_b);
	while(!feof(file_a) && !feof(file_b)) {
		if(compara(address_a, address_b) <= 0) {
			fwrite(address_a, sizeof(Endereco), 1, file_c);
			fread(address_a, sizeof(Endereco), 1, file_a);
		} else {
			fwrite(address_b, sizeof(Endereco), 1, file_c);
			fread(address_b, sizeof(Endereco), 1, file_b);
		}
	}

	while(!feof(file_a)) {
		fwrite(address_a, sizeof(Endereco), 1, file_c);
		fread(address_a, sizeof(Endereco), 1, file_a);
	}

	while(!feof(file_b)) {
		fwrite(address_b, sizeof(Endereco), 1, file_c);
		fread(address_b, sizeof(Endereco), 1, file_b);
	}

	*left_batch_idx = (*left_batch_idx) + 2;

	if(*pair_idx == BATCHES - 1)
		*right_batch_idx = (*right_batch_idx) + 1;
	else
		*right_batch_idx = (*right_batch_idx) + 2;

	*next_idx_merged = (*next_idx_merged) + 1;

	free(address_a);
	free(address_b);

	fclose(file_a);
	fclose(file_b);
	fclose(file_c);
}

int main(int argc, char**argv) {
	FILE *f;
	long qtd, batch_size, posicao;

	f = fopen("../datasets/cep.dat","rb");

	fseek(f, 0, SEEK_END);
	posicao = ftell(f);
	qtd = posicao / sizeof(Endereco);   // tamanho de cep.dat em registros
	rewind(f);

	writeBatches(qtd, f);   // roda a função com o tamanho total em registros e o arquivo cep.dat

	fclose(f);

	printf("Sorted data written in %d batches\n", BATCHES);

    // até aqui ja tem os 8 arquivos ordenados

	int left_batch_idx = 0;
	int right_batch_idx = left_batch_idx + 1;
	int next_idx_merged = BATCHES;
	int pair_idx = 1;

	while(pair_idx < BATCHES) {
		mergeSortedBatches(&left_batch_idx, &right_batch_idx, &next_idx_merged, &pair_idx);
		pair_idx += 1;
	}

	printf("Sorted data merged\n");
}