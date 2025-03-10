#include <stdio.h>
#include <stdlib.h>
#include "descompactacao.h"
#include "queue.h"
#include "contar_caracteres_ASCII.h"
#include "manipulacao_bytes.h"
#include "funcoes_huffman.h"

#define BYTE 8
#define SIZE_ASCII 127

TQueue* ler_tabela_arquivo(char* nome_arquivo_bin)
{
    FILE *arq_bin;
    TQueue *newQueue;
    TCharASCII *elementoASCII;
    int *vetorASCII, quant_elem_tabela, contador = 0, elemFreq;
    char elemChar;

    newQueue = build_queue();

    vetorASCII = (int*)malloc(sizeof(int)*(SIZE_ASCII+1));
    atribuirZeros(vetorASCII);

    arq_bin = fopen(nome_arquivo_bin,"rb");

    fread(&quant_elem_tabela, sizeof(int), 1, arq_bin);

    while(contador < quant_elem_tabela)
    {
        fread(&elemChar, sizeof(char), 1, arq_bin);
        fread(&elemFreq, sizeof(int), 1, arq_bin);

        vetorASCII[(int)elemChar] = elemFreq;
        contador += 5;
    }

    fclose(arq_bin);

    for(contador = 0; contador <= SIZE_ASCII; contador++)
    {
        if(vetorASCII[contador] > 0)
        {
            elementoASCII = (TCharASCII*)malloc(sizeof(TCharASCII));
            elementoASCII->idTipo = 1;
            elementoASCII->charASCII = (char)contador;
            elementoASCII->frequencia = vetorASCII[contador];

            enqueue(newQueue, elementoASCII, &compararFrequencia);
        }
    }

    free(vetorASCII);

    return newQueue;
}

int transferir_para_vetor_de_conteudo(int *v, int ultima_posicao, TByte byte)
{
    v[ultima_posicao++] = byte.b0;
    v[ultima_posicao++] = byte.b1;
    v[ultima_posicao++] = byte.b2;
    v[ultima_posicao++] = byte.b3;
    v[ultima_posicao++] = byte.b4;
    v[ultima_posicao++] = byte.b5;
    v[ultima_posicao++] = byte.b6;
    v[ultima_posicao++] = byte.b7;

    return ultima_posicao;
}

void bits_nao_preenchidos_vetor(int *conteudo_do_arquivo, int ultima_posicao, int bits_nao_preenchidos, TByte byte)
{
    switch(bits_nao_preenchidos)
    {
        case 0:
            ultima_posicao = transferir_para_vetor_de_conteudo(conteudo_do_arquivo, ultima_posicao, byte);
            break;
        case 1:
            conteudo_do_arquivo[ultima_posicao++] = byte.b0;
            conteudo_do_arquivo[ultima_posicao++] = byte.b1;
            conteudo_do_arquivo[ultima_posicao++] = byte.b2;
            conteudo_do_arquivo[ultima_posicao++] = byte.b3;
            conteudo_do_arquivo[ultima_posicao++] = byte.b4;
            conteudo_do_arquivo[ultima_posicao++] = byte.b5;
            conteudo_do_arquivo[ultima_posicao++] = byte.b6;
            break;
        case 2:
            conteudo_do_arquivo[ultima_posicao++] = byte.b0;
            conteudo_do_arquivo[ultima_posicao++] = byte.b1;
            conteudo_do_arquivo[ultima_posicao++] = byte.b2;
            conteudo_do_arquivo[ultima_posicao++] = byte.b3;
            conteudo_do_arquivo[ultima_posicao++] = byte.b4;
            conteudo_do_arquivo[ultima_posicao++] = byte.b5;
            break;
        case 3:
            conteudo_do_arquivo[ultima_posicao++] = byte.b0;
            conteudo_do_arquivo[ultima_posicao++] = byte.b1;
            conteudo_do_arquivo[ultima_posicao++] = byte.b2;
            conteudo_do_arquivo[ultima_posicao++] = byte.b3;
            conteudo_do_arquivo[ultima_posicao++] = byte.b4;
            break;
        case 4:
            conteudo_do_arquivo[ultima_posicao++] = byte.b0;
            conteudo_do_arquivo[ultima_posicao++] = byte.b1;
            conteudo_do_arquivo[ultima_posicao++] = byte.b2;
            conteudo_do_arquivo[ultima_posicao++] = byte.b3;
            break;
        case 5:
            conteudo_do_arquivo[ultima_posicao++] = byte.b0;
            conteudo_do_arquivo[ultima_posicao++] = byte.b1;
            conteudo_do_arquivo[ultima_posicao++] = byte.b2;
            break;
        case 6:
            conteudo_do_arquivo[ultima_posicao++] = byte.b0;
            conteudo_do_arquivo[ultima_posicao++] = byte.b1;
            break;
        case 7:
            conteudo_do_arquivo[ultima_posicao++] = byte.b0;
            break;
    }
}

/* Função que lê completamente o arquivo binário compactado, transfere para um vetor de inteiros e retorna o tamanho deste vetor. */
TConteudoBinario* ler_caracteres_arquivo(char* nome_arquivo_input)
{
    FILE *arq_bin = fopen(nome_arquivo_input,"rb");
    TByteMap *leitor;
	TConteudoBinario *conteudo_do_arquivo = (TConteudoBinario*)malloc(sizeof(TConteudoBinario));
    int size_tabela_int, quant_bytes, bits_nao_preenchidos, i, ultima_posicao = 0, size_vetor, *vetor_conteudo;

    /* Lendo o primeiro char do arquivo, que representa a quantidade de bytes que a tabela de frequência está ocupando no file. */
    fread(&size_tabela_int, sizeof(int), 1, arq_bin);

    /* Movendo o cursor para depois da tabela. */
    fseek(arq_bin, size_tabela_int, SEEK_CUR);

    /* Lendo a quantidade de bytes que está gravada no arquivo e quantos bits do último byte não estão preenchidos. */
    fread(&quant_bytes, sizeof(int), 1, arq_bin);
    fread(&bits_nao_preenchidos, sizeof(int), 1, arq_bin);
	
    /* Pulando um byte de marcação que há antes do conteúdo do texto propriamente dito. */
    fseek(arq_bin, sizeof(int), SEEK_CUR);

    size_vetor = quant_bytes*8 - bits_nao_preenchidos;
    vetor_conteudo = (int*)malloc(sizeof(int)*size_vetor);

    leitor = byteInit(8);
    for(i = 0; i < quant_bytes - 1; i++)
    {
        fread(&leitor->contents[0], 1,  1,  arq_bin);
        leitor->length = 8;
        ultima_posicao = transferir_para_vetor_de_conteudo(vetor_conteudo, ultima_posicao, leitor->contents[0]);
    }

    fread(&leitor->contents[0], 1,  1,  arq_bin);
    leitor->length = 8;
    bits_nao_preenchidos_vetor(vetor_conteudo, ultima_posicao, bits_nao_preenchidos, leitor->contents[0]);
	
	conteudo_do_arquivo->vetor_conteudo = vetor_conteudo;
	conteudo_do_arquivo->tamanho_vetor = size_vetor;

	fclose(arq_bin);
	free(leitor->contents);
	free(leitor);
	
	return conteudo_do_arquivo;
}

int encontrar_caracteres_huffman(TNode *raiz, TNode *vertice_atual, int *conteudo_do_arquivo, int posicao_atual_vetor, char *nome_arquivo_output)
{
	FILE *arq_txt;
	TCharASCII *elemento;
	
	if(!vertice_atual->left && !vertice_atual->right)
	{
		elemento = vertice_atual->elem;
		
		arq_txt = fopen(nome_arquivo_output, "a");
		fprintf(arq_txt, "%c", elemento->charASCII);
		fclose(arq_txt);
	}
	else if(conteudo_do_arquivo[posicao_atual_vetor] == 0)
	{
		posicao_atual_vetor = encontrar_caracteres_huffman(raiz, vertice_atual->left, conteudo_do_arquivo, posicao_atual_vetor + 1, nome_arquivo_output);
	}
	else if(conteudo_do_arquivo[posicao_atual_vetor] == 1)
	{
		posicao_atual_vetor = encontrar_caracteres_huffman(raiz, vertice_atual->right, conteudo_do_arquivo, posicao_atual_vetor + 1, nome_arquivo_output);
	}

    return posicao_atual_vetor;
}

void calcular_progresso(long posicao_atual, long tamanho_total)
{
    float progresso = ((float)posicao_atual / tamanho_total) * 100;
    printf("Progresso: %.2f%%\r", progresso);
    fflush(stdout);
}

void descompactar_arquivo(char* nome_arquivo_input, char* nome_arquivo_output)
{
    FILE *arq_bin, *arq_txt;
    TQueue *filaASCII, *tabela_prefixos;
    TNode *tree;
	TConteudoBinario *conteudo_do_arquivo;
	int posicao_atual_vetor = 0;

    arq_bin = fopen(nome_arquivo_input,"rb");

    if(arq_bin)
    {
        fclose(arq_bin);

        printf("Descompactacao inicializada...\n");

        filaASCII = ler_tabela_arquivo(nome_arquivo_input);

        tabela_prefixos = build_queue();
        tabela_prefixos->head = filaASCII->head;
        tabela_prefixos->tail = filaASCII->tail;
        tabela_prefixos->size = filaASCII->size;

        tree = huffman_build_tree(filaASCII);
        criar_codigos_prefixo(tree);

        conteudo_do_arquivo = ler_caracteres_arquivo(nome_arquivo_input);
		
		arq_txt = fopen(nome_arquivo_output,"w");
		fclose(arq_txt);
		
		while(posicao_atual_vetor < conteudo_do_arquivo->tamanho_vetor)
		{
			posicao_atual_vetor = encontrar_caracteres_huffman(tree, tree, conteudo_do_arquivo->vetor_conteudo, posicao_atual_vetor, nome_arquivo_output);
            calcular_progresso(posicao_atual_vetor, conteudo_do_arquivo->tamanho_vetor);
		}
		
        printf("\nDESCOMPACTACAO CONCLUIDA!\n\n");
		
		free(conteudo_do_arquivo->vetor_conteudo);
		free(conteudo_do_arquivo);
		free_queue(filaASCII, &freeElementoASCII);
    	free_queue(tabela_prefixos, &freeElementoASCII);
    }
    else
    {
        printf("O arquivo nao existe ou esta no diretorio incorreto.\n");
    } 
}
