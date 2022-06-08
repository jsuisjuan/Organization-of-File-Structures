/*	<!-- BuscaBinaria -->
*	Este é um programa que faz a busca por um determinado CEP através 
*	da busca binária, caso ele exista. Basta colocar o CEP desejado como
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

#include <stdio.h>      // declaração da biblioteca stdio.h
#include <string.h>     // declaração da biblioteca string.h

typedef struct _Endereco Endereco;  // definição da struct _Endereco como 'Endereco'

struct _Endereco {                  // struct 'Endereco'
    char logradouro[72];            // string para nomear logradouro no Endereco
    char bairro[72];                // string para nomear bairro no Endereco
    char cidade[72];                // string para nomear cidade no Endereco
    char uf[72];                    // string para nomear uf/Estado no Endereco
    char sigla[2];                  // string para nomear sigla do Estado no Endereco
    char cep[8];                    // string para nomear cep no Endereco
    char lixo[2];                   // espaço + quebra linha
};

void buscaBinaria(long fim, FILE* entrada, char* procurar) {    // função que executa a busca binária com os paramentro: ultimo registro do arquivo, o arquivo de entrada, o CEP desejado
    long inicio = 0;        // definição do inicio do arquivo, ou seja, no registro 0
    int quantidade, i;      // declaração da variaável quantidade para calcular a quantidade e i para calcular a quantidade de buscas feitas
    Endereco e;             // declaração da struct Endereco 'e'

    while (inicio <= fim) {                                     // enquanto inicio for menor ou igual ao fim
        int meio = (inicio + fim)/2;                            // declaração da variável meio 
        i++;                                    
        fseek(entrada, meio*300, SEEK_SET);                     // função fseek() para percorrer os bytes do arquivo entrada, (endereço/registro por endereco/registro)
        quantidade = fread(&e, sizeof(Endereco), 1, entrada);   // le um Endereco/Entidade por vez do arquivo entrada e armazenar no registro em 'e' que é do tipo Endereco

        if (strncmp(procurar, e.cep, 8) == 0) {                 // se o CEP desejado for igual ao CEP procurado/percorrido
            printf("%.8s\n", e.cep);                            // imprimir o CEP
            break;
        } if (strncmp(procurar, e.cep, 8) < 0) {                // se CEP desejado for menor do que o CEP procurado/percorrido
            fim = meio - 1;
        } else {                                                // se CEP desejado for maior do que o CEP procurado/percorrido
            inicio = meio + 1;
        }
    }

    printf("Foram %d interacoes para encontrar o CEP", i);      // imprimir a quantidade de buscas feitas até encontrar o CEP desejado
}

int main(int argc, char** argv) {                       // inicia a função main com a argc e argv
    FILE* entrada;                                      // declaração da variável do tipo FILE para apontar para um arquivo
    Endereco e;                                         // declaração da variável do tipo struct Endereco 'e'
    long tamBytes, tamRegistro;                         // declaração da variável do tipo long para armazenar tamanho em bytes e registro

    if (argc != 2) {                                    // se o programa não apresentar 2 argumentos, imprimir erro
        fprintf(stderr, "USO: %s [CEP]", argv[0]);
        return 1;
    }

    entrada = fopen("cep_ordenado.dat", "rb");          // utilizar entrada para apontar e abrir o arquivo 'cep_ordenado.dat' no modo read binary
    fseek(entrada, 0, SEEK_END);                        // função fseek() para percorrer os bytes do arquivo de entrada até o final

    tamBytes = ftell(entrada);                          // utilizar a função ftell() no arquivo entrada para amostrar o tamanho em bytes e armazenar em tamBytes
    tamRegistro = tamBytes/sizeof(Endereco);            // utiliza a variável tamBytes e divide pelo tamanho de Endereco(300) e achando o tamanho em registros e armazenando em tamRegistro

    printf("Tamanho do arquivo em bytes: %ld\n", tamBytes);         // imprime tamanho do arquivo em bytes
    printf("Tamanho do arquivo em registros: %ld\n", tamRegistro);  // imprime tamnho do arquivo em registro

    long fim = tamRegistro - 1;             // definindo o ultimo registro (removendo o '/0') um valor real e alucando na variável 'fim'

    buscaBinaria(fim, entrada, argv[1]);    // função que aponta para a execução da busca binária

    fclose(entrada);                        // fecha o arquivo entrada
    return 0;                               // finaliza o programa com retorno 0 para definir sucesso na execução
}