#ifndef CONTAR_CARACTERES_H
#define CONTAR_CARACTERES_H

#include "queue.h"

typedef struct characterASCII TCharASCII;
struct characterASCII
{
    int idTipo;         	/* Se idTipo = 0, está sendo representado um nó de árvore (soma de frequências), já com idTipo = 1, um nó de fila. */
    char charASCII;     	/* Caractere representado pela estrutura. */
    int frequencia;     	/* Frequência do caractere em um arquivo. */
    int *codigo_prefixo;    /* Vetor do código de prefixo gerado na Árvore de Huffman. */
    int size_codigo;        /* Tamanho do vetor do código de prefixo. */
};

void atribuirZeros(int *vetorASCII);
TQueue* criarFilaASCII(char *nomeArquivo);
int compararFrequencia(TCharASCII *elem1, TCharASCII *elem2);
void printElementoASCII(TCharASCII *elem);
void freeElementoASCII(TCharASCII *elem);

#endif
