#include <stdio.h>
#include <stdlib.h>
#include "funcoes_huffman.h"
#include "queue.h"
#include "contar_caracteres_ASCII.h"
#include "manipulacao_bytes.h"

#define BYTE 8
#define SIZE_ASCII 127

/* Função que transforma gradualmente a fila de prioridades (recebida como parâmetro) em uma Árvore de Huffman. */
TNode *huffman_build_tree(TQueue *q)
{
    int counter, sizeQueue = q->size;
    TNode *newNode, *menorElem, *menorElem2;
    TCharASCII *somaFrequencias, *menorFrequencia, *menorFrequencia2;

    for(counter = 1; counter <= sizeQueue; counter++)
    {
        newNode = (TNode*)malloc(sizeof(TNode));                       /* Alocação do novo nó da Árvore de Huffman. */
        somaFrequencias = (TCharASCII*)malloc(sizeof(TCharASCII));     /* Alocação do elemento que o novo nó receberá. */

        menorElem = dequeue_huffman(q);     /* Extração dos dois nós com menores elementos da fila de prioridades. */
        menorElem2 = dequeue_huffman(q);

        /* Nessas 2 linhas abaixo, os dois nós de fila são "transformados" em nós da árvore (note que as duas estruturas utilizam o mesmo tipo TNode de nó), já que
           elas passam a apontar para um nó pai. Detalhe: o filho da esquerda e o filho da direita desses dois nós já apontam para NULL. */
		menorElem->parent = newNode;    
        menorElem2->parent = newNode;                            

        menorFrequencia = menorElem->elem;
        menorFrequencia2 = menorElem2->elem;
        somaFrequencias->frequencia = menorFrequencia->frequencia + menorFrequencia2->frequencia;
		somaFrequencias->codigo_prefixo = NULL;		/* Inicializa o ponteiro como nulo. */
		somaFrequencias->charASCII = 0; 			/* Inicializa a variável com o char de controle 00 (NULL CHARACTER). */
        somaFrequencias->idTipo = 0;    			/* Um elemento com idTipo = 0 significa que ele não possui caracter, tratando-se apenas de um elemento de nó de soma. */
        
        newNode->left = menorElem;
        newNode->right = menorElem2;
        newNode->elem = somaFrequencias;
        newNode->parent = NULL;
        newNode->next = NULL;

        enqueue_huffman(q, newNode, &compararFrequencia);     /* Insere na fila o novo nó. */
    }

    return newNode;
}

/* Função recursiva que percorre toda a árvore e grava os códigos de prefixo nos elementos TCharASCII das folhas da árvore. */
void gerador_codigos_prefixo_huffman(TNode *tree, int *v, int ultima_posicao)
{
    int i;
	
	if(tree)
    {
        /* Se for folha, o código de prefixo atual é gravado. */
        if (!tree->left && !tree->right)
        {
            TCharASCII *elem = tree->elem;
            elem->size_codigo = ultima_posicao;
            elem->codigo_prefixo = (int*)malloc(sizeof(int)*ultima_posicao);

            for(i = 0; i < ultima_posicao; i++)   /* Transferindo o código de prefixo para o elemento. */
            {
                elem->codigo_prefixo[i] = v[i];
            }
        }

        /* Se for para a esquerda, a última posição do vetor recebe 0. */
        if (tree->left)
        {
            v[ultima_posicao] = 0;
            gerador_codigos_prefixo_huffman(tree->left, v, ultima_posicao + 1);
        }

        /* Se for para a direita, a última posição do vetor recebe 1. */
        if (tree->right)
        {
            v[ultima_posicao] = 1;
            gerador_codigos_prefixo_huffman(tree->right, v, ultima_posicao + 1);
        }
    }
}

/* Função cuja responsabilidade é apenas chamar a função recursiva que gera os códigos de prefixo, passando um vetor
   que é onde será gravado os códigos de prefixo temporariamente, enquanto a árvore é percorrida. */
void criar_codigos_prefixo(TNode *tree)
{
    int aux_prefixos[1000] = {0};

    gerador_codigos_prefixo_huffman(tree, aux_prefixos, 0);
}

/* Função que imprime os códigos de prefixo a partir de uma fila que já possua a tabela de prefixos preenchida. */
void print_codigos_prefixo(TQueue *tabela_prefixos)
{
    int i;
    TNode *nodeActual = tabela_prefixos->head;
    TCharASCII *charActual;

    while(nodeActual)
    {
        charActual = nodeActual->elem;

        if(charActual->idTipo != 0)
        {
            printf("\n%c = ", charActual->charASCII);

            for (i = 0; i < charActual->size_codigo; i++)
            {
                printf("%d", charActual->codigo_prefixo[i]);
            }
        }

        nodeActual = nodeActual->next;
    }

    printf("\n");
}
