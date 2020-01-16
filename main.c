#include <stdio.h>
#include <stdlib.h>
#include "compactacao.h"
#include "descompactacao.h"

int main()
{
    char arquivo_input_compactar[] = "texto_original_1.txt";
    char arquivo_output_compactar[] = "texto_compactado.jva";

    char arquivo_input_descompactar[] = "texto_compactado.jva";
    char arquivo_output_descompactar[] = "texto_descompactado.txt";

    char resposta;
    printf("ALGORITMO DE COMPACTACAO E DESCOMPACTACAO\n\n");
    printf("Deseja compactar ou descompactar? Digite C para compactar e D para descompactar: \n");
    printf("Sua escolha: ");
    scanf("%c", &resposta);
    fflush(stdin);

    if(resposta == 'C' || resposta == 'c')
    {
        compactar_arquivo(arquivo_input_compactar, arquivo_output_compactar);
    }
    else if(resposta == 'D' || resposta == 'd')
    {	
	descompactar_arquivo(arquivo_input_descompactar, arquivo_output_descompactar);
    }

    return 0;
}
