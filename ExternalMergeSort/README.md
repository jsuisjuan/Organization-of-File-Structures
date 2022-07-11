# External Merge Sort
Este programa foi dedicado a implementação do External Merge Sort em um determinado arquivo .dat.
Para utilizar o programa, basta:
- descompactar o arquivo 'cepDat'; 
- abrir a linha de comando;
- executar o comando: 'gcc -o externalMergeSortExecuta externalMergeSort.c';
- executar o comando: './externalMergeSort'.

OBS.: Caso deseje alterar a quantidade de blocos, basta alterar o '#define BLOCOS 8' por um valor par desejado. Ex.: #define BLOCOS 16.

Assim que os comandos forem executados, o arquivo 'cep.dat' será separado em blocos, ordenado e intercalado; gerando o arquivo 'cep_ordenado.dat'.