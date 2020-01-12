#ifndef DESCOMPACTACAO_H
#define DESCOMPACTACAO_H

typedef struct conteudo_binario TConteudoBinario;
struct conteudo_binario
{
	int *vetor_conteudo;
	int tamanho_vetor;
};

void descompactar_arquivo(char* nome_arquivo_input, char* nome_arquivo_output);

#endif
