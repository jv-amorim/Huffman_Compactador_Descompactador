#ifndef FUNCOES_HUFFMAN_H
#define FUNCOES_HUFFMAN_H

#include "queue.h"

TNode *huffman_build_tree(TQueue *q);
void criar_codigos_prefixo(TNode *t);
void print_codigos_prefixo(TQueue *tabela_prefixos);
void comprimir_arquivo(char* nome_arquivo_txt, TQueue* tabela_prefixos);
void descomprimir_arquivo(char* nome_arquivo_bin);

#endif
