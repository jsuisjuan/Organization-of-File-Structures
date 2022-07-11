#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BLOCOS 8

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

int compara(const void*, const void*);
void intercala(char*, char*, char*);

int main(int argc, char** argv) {
    FILE *f;
    Endereco *e;
    long tam_bytes, tam_registros;
    int blocos, par_blocos, aux, c;
    char arq[13], arq1[13], arq2[13], arq_merge[13], saida[13];

    par_blocos = blocos = BLOCOS;
    aux = 0;
    c = 1;

    f = fopen("cep.dat","rb");
    fseek(f,0,SEEK_END);
    tam_bytes = ftell(f);
    tam_registros = tam_bytes/sizeof(Endereco);

    e = (Endereco *) malloc((tam_registros/BLOCOS)*sizeof(Endereco));
    rewind(f);

    for (int i=1;i<=BLOCOS;i++) {
        sprintf(arq,"cep%d.dat",i);
        FILE *saida = fopen(arq,"wb");
        fread(e,sizeof(Endereco),(tam_registros/BLOCOS),f);
        qsort(e,(tam_registros/BLOCOS),sizeof(Endereco),compara);
        fwrite(e,sizeof(Endereco),(tam_registros/BLOCOS),saida);
        fclose(saida);
    }

    free(e);
    fclose(f);

    while (par_blocos>=2) {
        aux=1;
        while (c<=blocos) {
            sprintf(arq1,"cep%d.dat",c);
            sprintf(arq2,"cep%d.dat",c+1);
            sprintf(saida,"cep%d.dat",aux+blocos);
            intercala(arq1,arq2,saida);
            remove(arq1);
            remove(arq2);
            aux++;
            c+=2;
        }
        par_blocos/=2;
        blocos+=par_blocos;
    }
	sprintf(arq_merge,"cep%d.dat",c);
	rename(arq_merge,"cep_ordenado.dat"); 
}

int compara(const void *e1, const void *e2) {
	return strncmp(((Endereco*)e1)->cep,((Endereco*)e2)->cep,8);
}

void intercala(char* arq1, char* arq2, char* saida) {
    FILE *a, *b, *c;
    Endereco ea, eb;

    a = fopen(arq1,"r");
    b = fopen(arq2,"r");
    c = fopen(saida,"wb");

    fread(&ea,sizeof(Endereco),1,a);
    fread(&eb,sizeof(Endereco),1,b);

    while(!feof(a) && !feof(b)) {
        if (compara(&ea,&eb) < 0) {
            fwrite(&ea,sizeof(Endereco),1,c);
            fread(&ea,sizeof(Endereco),1,a);
        } else {
            fwrite(&eb,sizeof(Endereco),1,c);
            fread(&eb,sizeof(Endereco),1,b);
        }
    }

    while (!feof(a)) {
		fwrite(&ea,sizeof(Endereco),1,c);
		fread(&ea,sizeof(Endereco),1,a);
	}
	while (!feof(b)) {
		fwrite(&eb,sizeof(Endereco),1,c);
		fread(&eb,sizeof(Endereco),1,b);
	}
    
	fclose(a);
	fclose(b);
	fclose(c);
}