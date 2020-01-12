#include <stdio.h>
#include <stdlib.h>
#include "compactacao.h"
#include "queue.h"
#include "contar_caracteres_ASCII.h"
#include "manipulacao_bytes.h"
#include "funcoes_huffman.h"

#define BYTE 8
#define SIZE_ASCII 127

/* A funcao recebe um char e retorna o seu elemento TCharASCII presente na tabela (fila) de prefixos. */
TCharASCII *procurar_char_na_tabela(char char_procurado, TQueue* tabela_prefixos)
{
   	TNode* node_atual = tabela_prefixos->head;
    TCharASCII *elemento_atual = node_atual->elem;
    char char_atual = elemento_atual->charASCII;

    while (char_atual != char_procurado)
    {
        node_atual = node_atual->next;
        elemento_atual = node_atual->elem;
        char_atual = elemento_atual->charASCII;
    }

    return elemento_atual;
}

void inserir_bits(TByteMap *map, int *bits, int quantidade_bits)
{
    int i, byte_atual, bit_atual;
	
    if(map->length < map->max_size)
    {
		for(i = 0; i < quantidade_bits && map->length < map->max_size; i++)
        {
            byte_atual = map->length/BYTE;
            bit_atual = map->length - byte_atual*BYTE;
			
            switch(bit_atual)
            {
                case 0:
                    map->contents[byte_atual].b0 = bits[i];
                    break;
                case 1:
                    map->contents[byte_atual].b1 = bits[i];
                    break;
                case 2:
                    map->contents[byte_atual].b2 = bits[i];
                    break;
                case 3:
                    map->contents[byte_atual].b3 = bits[i];
                    break;
                case 4:
                    map->contents[byte_atual].b4 = bits[i];
                    break;
                case 5:
                    map->contents[byte_atual].b5 = bits[i];
                    break;
                case 6:
                    map->contents[byte_atual].b6 = bits[i];
                    break;
                case 7:
                    map->contents[byte_atual].b7 = bits[i];
                    break;
                default:
                    printf("Erro no calculo do bit atual.\n(bit_atual = %i)\n",bit_atual);
                    break;
            }

            map->length++;
        }
    }
}

void deslocar_bits_para_esquerda(TByteMap *map, int num_bytes)
{
    int i = 0;

    for(i = 0; i < num_bytes; i++)
    {
        map->contents[i].b0 = map->contents[i+1].b0;
        map->contents[i].b1 = map->contents[i+1].b1;
        map->contents[i].b2 = map->contents[i+1].b2;
        map->contents[i].b3 = map->contents[i+1].b3;
        map->contents[i].b4 = map->contents[i+1].b4;
        map->contents[i].b5 = map->contents[i+1].b5;
        map->contents[i].b6 = map->contents[i+1].b6;
        map->contents[i].b7 = map->contents[i+1].b7;
    }
}

void gravar_tabela_arquivo(char* nome_arquivo_output, TQueue *tabela_prefixos)
{
    FILE *arq_bin;
    int i, counter = 0, tamanho_bytes_tabela = 0, quantidade_bytes, *vetor_tabela_aux;
	char conversor;
    TNode *node_atual;
    TCharASCII *element_atual;

    /* O vetor abaixo recebe cada caractere e sua frequencia. */
    vetor_tabela_aux = (int*)malloc(sizeof(int) * (tabela_prefixos->size + 1) * 2);

    node_atual = tabela_prefixos->head;

    while(node_atual->next)
    {
        element_atual = node_atual->elem;

        if(element_atual->idTipo == 1)
        {
			vetor_tabela_aux[counter++] = (int)element_atual->charASCII;
            vetor_tabela_aux[counter++] = element_atual->frequencia;
			tamanho_bytes_tabela += 5;
        }

        node_atual = node_atual->next;
    }

    arq_bin = fopen(nome_arquivo_output,"wb");

    fwrite(&tamanho_bytes_tabela, sizeof(int), 1, arq_bin);

    for(i = 0; i < counter; )
    {
        conversor = (char)vetor_tabela_aux[i];
		fwrite(&conversor, sizeof(char), 1, arq_bin);
		i++;
		
        fwrite(&vetor_tabela_aux[i], sizeof(int), 1, arq_bin);
		i++;
    }

    /* Gravando este inteiro que sera substituido posteriormente pela quantidade de bytes que foram gravados no arquivo. */
    quantidade_bytes = 0;
    fwrite(&quantidade_bytes, sizeof(int), 1, arq_bin);

    fclose(arq_bin);
    free(vetor_tabela_aux);
}

void compactacao(char* nome_arquivo_input, char* nome_arquivo_output, TQueue* tabela_prefixos)
{
    FILE *arq_txt, *arq_bin;
    char char_lido;
    int i, quantidade_bytes_lidos, quantidade_bytes_gravados = 0, bits_sobrando = 0;
    TCharASCII *elem;
    TByteMap *mapa_de_bits = byteInit(256);

    arq_txt = fopen(nome_arquivo_input,"r");

    if(arq_txt && fscanf(arq_txt,"%c",&char_lido) > 0)
    {
        rewind(arq_txt);
        
        gravar_tabela_arquivo(nome_arquivo_output, tabela_prefixos);

        arq_bin = fopen(nome_arquivo_output,"ab");

        /* Gravando estes inteiros que ser�o substitu�dos posteriormente pela quantidade de bytes gravados no
           arquivo e pela quantidade de bits 0 sobrando no final, utilizados para preencher o �ltimo byte. */
        fwrite(&quantidade_bytes_gravados, sizeof(int), 1, arq_bin);
        fwrite(&bits_sobrando, sizeof(int), 1, arq_bin);

        while( fscanf(arq_txt,"%c",&char_lido) > 0 )
        {	
			elem = procurar_char_na_tabela(char_lido, tabela_prefixos);
			
            inserir_bits(mapa_de_bits, elem->codigo_prefixo, elem->size_codigo);

            quantidade_bytes_lidos = mapa_de_bits->length/BYTE;
			
            for(i = 0; i < quantidade_bytes_lidos; i++)
            {
                /* Gravando com sizeof = 1, pois a necessidade é de gravar exatamente 1 byte. Caso fosse gravado com sizeof de
                   TByte, seriam gravados 4 bytes em vez de 1 byte, por se tratar de uma struct. */
                fwrite(&mapa_de_bits->contents[0], 1, 1, arq_bin);

                quantidade_bytes_gravados++;

                deslocar_bits_para_esquerda(mapa_de_bits, quantidade_bytes_lidos);
                mapa_de_bits->length -= BYTE;
            }
        }

        fwrite(&mapa_de_bits->contents[0], 1, 1, arq_bin);
        quantidade_bytes_gravados++;

        fclose(arq_bin);

        arq_bin = fopen(nome_arquivo_output,"rb+");

        bits_sobrando = BYTE - mapa_de_bits->length;

        fread(&i, sizeof(int), 1, arq_bin);
        fseek(arq_bin, i, SEEK_CUR);

        fwrite(&quantidade_bytes_gravados, sizeof(int), 1, arq_bin);
        fwrite(&bits_sobrando, sizeof(int), 1, arq_bin);

        fclose(arq_bin);
    }
    else
    {
        printf("Nao foi possivel realizar a compactacao. Possiveis causas de erro: \n");
        printf("1. O arquivo nao existe;\n");
        printf("2. O arquivo esta vazio.\n");
        printf("3. O diretorio esta incorreto;\n\n");
    }

    free(mapa_de_bits->contents);
    free(mapa_de_bits);
    fclose(arq_txt);
}

void compactar_arquivo(char* nomeArquivoInput, char* nomeArquivoOutput)
{
    TQueue *filaASCII, *tabela_prefixos;
    TNode *tree;

    printf("\nCompactacao inicializada...\n");

    filaASCII = criarFilaASCII(nomeArquivoInput);

    /* Cópia da fila de prioridades criada acima. Embora possua os mesmos elementos, será
       mais prático usar essa durante a criação dos códigos de prefixo. */
    tabela_prefixos = build_queue();
    tabela_prefixos->head = filaASCII->head;
    tabela_prefixos->tail = filaASCII->tail;
    tabela_prefixos->size = filaASCII->size;

    tree = huffman_build_tree(filaASCII);
	
    criar_codigos_prefixo(tree);
	
    compactacao(nomeArquivoInput, nomeArquivoOutput, tabela_prefixos);
	
    free_queue(filaASCII, &freeElementoASCII);
    free_queue(tabela_prefixos, &freeElementoASCII);

    printf("\nCOMPACTACAO CONCLUIDA!\n\n");
}
