#ifndef QUEUE_H
#define QUEUE_H

typedef struct node TNode;
struct node
{
    void *elem;
    TNode *next;
    TNode *parent;
    TNode *left;
    TNode *right;
};

typedef struct queue TQueue;
struct queue
{
    int size;
    TNode *head;
    TNode *tail;
};

TQueue* build_queue();
int queue_empty(TQueue *q);
void enqueue(TQueue *q, void *elem, int (*cmp)());
void enqueue_huffman(TQueue *q, TNode *newNode, int (*cmp)());
void* dequeue(TQueue *q);
TNode* dequeue_huffman(TQueue *q);
void print_queue(TQueue *q, void (*print_elem)());
void free_queue(TQueue *q, void (*free_elem)());

#endif
