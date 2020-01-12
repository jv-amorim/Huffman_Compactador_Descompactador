#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

TQueue* build_queue()
{
    TQueue *aux = (TQueue*)malloc(sizeof(TQueue));
    aux->size = 0;
    aux->head = NULL;
    aux->tail = NULL;

    return aux;
}

int queue_empty(TQueue *q)
{
    if(!q->head)
        return 1;
    return 0;
}

void enqueue(TQueue *q, void *elem, int (*cmp)())
{
    TNode *newNode, *nodeActual = q->head, *nodePrev = NULL;
	
	newNode = (TNode*)malloc(sizeof(TNode));
    newNode->elem = elem;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;

    if(queue_empty(q))
    {
        newNode->next = NULL;
        q->head = newNode;
        q->tail = newNode;
    }
    else
    {
        while(nodeActual)
        {
            if(cmp(elem, nodeActual->elem))
            {
                if(!nodePrev)   /* Caso o elemento tenha de ser inserido na primeira posição. */
                {
                    newNode->next = nodeActual;
                    q->head = newNode;
                    q->size++;
                    return;
                }
                else    /* Inserção entre os nós. */
                {
                    nodePrev->next = newNode;
                    newNode->next = nodeActual;
                    q->size++;
                    return;
                }
            }
            nodePrev = nodeActual;
            nodeActual = nodeActual->next;
        }

        /* Inserção após o último nó. Só acontece se nenhuma inserção for feita entre os outros nós. */
        nodePrev->next = newNode;
        newNode->next = NULL;
        q->size++;
    }
}

/* O enqueue utilizado na construção da Árvore de Huffman é um pouco diferente do enqueue normal. */
void enqueue_huffman(TQueue *q, TNode *newNode, int (*cmp)())
{
    TNode *nodeActual = q->head;
    TNode *nodePrev = NULL;

    if(queue_empty(q))
    {
        newNode->next = NULL;
        q->head = newNode;
        q->tail = newNode;
    }
    else
    {
        while(nodeActual)
        {
            if(cmp(newNode->elem, nodeActual->elem))
            {
                if(!nodePrev)   /* Caso o elemento tenha de ser inserido na primeira posição. */
                {
                    newNode->next = nodeActual;
                    q->head = newNode;
                    q->size++;
                    return;
                }
                else    /* Inserção entre os nós. */
                {
                    nodePrev->next = newNode;
                    newNode->next = nodeActual;
                    q->size++;
                    return;
                }
            }
            nodePrev = nodeActual;
            nodeActual = nodeActual->next;
        }

        /* Inserção após o último nó. Só acontece se nenhuma inserção for feita entre os outros nós. */
        nodePrev->next = newNode;
        newNode->next = NULL;
        q->size++;
    }
}

void* dequeue(TQueue *q)
{
    if(!queue_empty(q))
    {
        void *aux = q->head->elem;
        TNode *nodeAux = q->head->next;
        free(q->head);
        q->head = nodeAux;
        q->size--;

        return aux;
    }

    printf("The queue is empty.\n");
    return NULL;
}

/* O dequeue utilizado na construção da Árvore de Huffman é um pouco diferente do dequeue normal. */
TNode* dequeue_huffman(TQueue *q)
{
    if(!queue_empty(q))
    {
        TNode *nodeReturn = q->head;
        TNode *nodeAux = q->head->next;
        q->head = nodeAux;
        q->size--;

        return nodeReturn;
    }

    printf("The queue is empty.\n");
    return NULL;
}

void print_queue(TQueue *q, void (*print_elem)())
{
    TNode *nodeActual = q->head;

    while(nodeActual)
    {
        print_elem(nodeActual->elem);
        nodeActual = nodeActual->next;
    }
}

void free_queue(TQueue *q, void (*free_elem)())
{
    TNode *aux;

    while(q->head)
    {
        aux = q->head->next;
        free_elem(q->head->elem);
        free(q->head);
        q->head = aux;
    }

    free(q);
}
