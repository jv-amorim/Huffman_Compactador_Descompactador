#include <stdio.h>
#include <stdlib.h>
#include "compactacao.h"
#include "descompactacao.h"

int main(int argc, char* argv[])
{
    char modo;
    char* arquivo_input;
    char* arquivo_output;
    FILE* arquivo_check;

    printf("ALGORITMO DE COMPACTACAO E DESCOMPACTACAO\n\n");

    if (argc != 4)
    {
        printf("Parâmetros incorretos. Uso correto: %s <modo (C ou D)> <arquivo input> <arquivo output>\n", argv[0]);
        return 1;
    }

    modo = argv[1][0];
    arquivo_input = argv[2];
    arquivo_output = argv[3];

    arquivo_check = fopen(arquivo_input, "r");
    if (arquivo_check == NULL)
    {
        printf("O arquivo de entrada '%s' não foi encontrado.\n", arquivo_input);
        return 1;
    }
    fclose(arquivo_check);

    if (modo == 'C' || modo == 'c')
    {
        compactar_arquivo(arquivo_input, arquivo_output);
        return 0;
    }

    if (modo == 'D' || modo == 'd')
    {
        descompactar_arquivo(arquivo_input, arquivo_output);
        return 0;
    }
    
    printf("Modo inválido. Use 'C' para compactar e 'D' para descompactar.\n");
    return 1;
}
