#include <stdio.h>
#include <stdlib.h>
#include "contar_caracteres_ASCII.h"
#include "queue.h"

#define SIZE_ASCII 127

/* Função que recebe um vetor ASCII (vetor de inteiros com tamanho 127) e atribui 0 a todas as suas posições. */
void atribuirZeros(int *vetorASCII)
{
    int i;

    for(i = 0; i <= SIZE_ASCII; i++)
    {
        vetorASCII[i] = 0;
    }
}

/* Função que lê um arquivo texto e conta a frequência de cada char da tabela ASCII nele, gravando em um vetor ASCII. */
void lerArquivo(int *vetorASCII, char* nomeArquivo)
{
    char c;
    FILE *arq = fopen(nomeArquivo,"r");

    if(arq)
    {
        while( fscanf(arq,"%c",&c) > 0 )
        {
            vetorASCII[(int)c]++;
        }

        fclose(arq);
    }
}

/* Função responsável por criar um vetor ASCII (vetor de int com tamanho 127), chamar a função atribuirZeros e lerArquivo. */
int* criarVetorASCII(char *nomeArquivo)
{
    int *vetorASCII;

    vetorASCII = (int*)malloc(sizeof(int)*(SIZE_ASCII+1));

    atribuirZeros(vetorASCII);

    lerArquivo(vetorASCII,nomeArquivo);

    return vetorASCII;
}

/* Exibe completamente o vetor ASCII passado como parâmetro. */
void printVetorASCII(int *vetorASCII)
{
    int i;
    for(i = 0; i<=SIZE_ASCII; i++)
    {
        printf("%i = %i\n",i,vetorASCII[i]);
    }
}

/* Exibe um elemento TCharASCII (struct com um caractere e sua frequência em um arquivo texto). */
void printElementoASCII(TCharASCII *elem)
{
    if(elem->idTipo == 1)
    {
        printf("%c = %i\n", elem->charASCII, elem->frequencia);
    }
    else
    {
        printf("NodeSoma = %i\n", elem->frequencia);
    }
}

/* Desaloca um elemento TCharASCII. */
void freeElementoASCII(TCharASCII *elem)
{
    free(elem->codigo_prefixo);
    free(elem);
}

/* Compara a frequência entre dois elementos TCharASCII. */
int compararFrequencia(TCharASCII *elem1, TCharASCII *elem2)
{
    if(elem1->frequencia < elem2->frequencia)
        return 1;
    return 0;
}

/* Cria uma fila de prioridades de elementos TCharASCII a partir do arquivo cujo nome é passado como parâmetro. */
TQueue* criarFilaASCII(char *nomeArquivo)
{
    TQueue *newQueue;
    TCharASCII *elementoASCII;
    int *vetorASCII;
    int contador;

    newQueue = build_queue();
    vetorASCII = criarVetorASCII(nomeArquivo);

    for(contador = 0; contador <= SIZE_ASCII; contador++)
    {
        if(vetorASCII[contador] != 0)
        {
            elementoASCII = (TCharASCII*)malloc(sizeof(TCharASCII));
            elementoASCII->idTipo = 1;
            elementoASCII->charASCII = (char)contador;
            elementoASCII->frequencia = vetorASCII[contador];

            enqueue(newQueue,elementoASCII,&compararFrequencia);
        }
    }

    free(vetorASCII);

    return newQueue;
}
