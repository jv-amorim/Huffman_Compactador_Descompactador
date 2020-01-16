# Algoritmo de Compactação e Descompactação de Arquivos Texto por Árvores de Huffman

- Criado por: João Vitor Amorim
- Linguagem utilizada: C
- Disponibilizado no GitHub: 12/01/2020


### Descrição:

O algoritmo realiza a compactação e descompactação de arquivos texto através da técnica de Árvores de Huffman.

### Como utilizar:

Antes de realizar a compilação do algoritmo, configure as seguintes variáveis no arquivo main.c:
 - arquivo_input_compactar : endereço e nome do arquivo texto que deseja compactar.
 - arquivo_output_compactar : endereço e nome do arquivo binário de saída. Trata-se do texto compactado.
 - arquivo_input_descompactar : endereço e nome do arquivo binário que deseja descompactar.
 - arquivo_output_descompactar : ndereço e nome do arquivo texto de saída. Trata-se do texto descompactado.
 (Caso os arquivos estejam na mesma pasta do código fonte, basta digitar os nomes dos arquivos (com a extensão .txt).)

Após realizar a configuração das variáveis acima, basta compilar e depois iniciar o executável gerado. Com o executável iniciado, digite C caso o desejado seja realizar uma compactação ou D, caso o desejado seja realizar uma descompactação. O último passo é só aguardar o algoritmo rodar e realizar o processo de compactação ou descompactação.

Há dois arquivos incluídos no projetos que podem ser utilizados como testes: "texto_original_1.txt" e "texto_original_2.txt".

### Observações:

- O algoritmo compacta e descompacta qualquer arquivo texto que possua caracteres entre 0 e 127 na tabela ASCII, sendo facilmente modificável para incluir os caracteres extendidos (127 a 256 na tabela ASCII).

- A compactação é realizada rapidamente mesmo para arquivos com tamanho acima de 1MB de arquivo. Lembre-se que um char ocupa 1 byte.

- A descompactação infelizmente demora muito tempo para ser concluída em arquivos muito grandes (acima de 40 kB já demora alguns minutos). Isso acontece devido ao método utilizado para identificar qual caractere está sendo lido no arquivo binário, onde é chamada uma função recursiva que lê bit por bit do arquivo para percorrer a Árvore de Huffman, parando ao encontrar o nó folha que contém o caractere correto a ser gravado.
Há otimizações que podem ser feitas, tornando possível um descompactação muito mais rápida, mas decidi não implementá-las, devido à prioridade de outros projetos que estou realizando na data da postagem desse algoritmo. 
Caso deseje implementar essas otimizações, basta seguir a mesma ideia que alguns usuários do Stack Overflow implementaram:
<https://stackoverflow.com/questions/2235208/how-to-decode-huffman-code-quickly>
<https://stackoverflow.com/questions/29890348/how-to-efficiently-decompress-huffman-coded-file>
<https://stackoverflow.com/questions/13804629/huffman-code-with-lookup-table>
