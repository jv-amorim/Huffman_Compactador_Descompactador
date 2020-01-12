all: huffman

huffman: main.o compactacao.o descompactacao.o contar_caracteres_ASCII.o funcoes_huffman.o manipulacao_bytes.o queue.o
	gcc -o huffman main.o compactacao.o descompactacao.o contar_caracteres_ASCII.o funcoes_huffman.o manipulacao_bytes.o queue.o -ansi -Wall -pedantic -g

main.o: main.c compactacao.h descompactacao.h
	gcc -o main.o -c main.c -ansi -Wall -pedantic -g

compactacao.o: compactacao.c contar_caracteres_ASCII.h funcoes_huffman.h manipulacao_bytes.h queue.h
	gcc -o compactacao.o -c compactacao.c -ansi -Wall -pedantic -g

descompactacao.o: descompactacao.c contar_caracteres_ASCII.h funcoes_huffman.h manipulacao_bytes.h queue.h
	gcc -o descompactacao.o -c descompactacao.c -ansi -Wall -pedantic -g

contar_caracteres_ASCII.o: contar_caracteres_ASCII.c queue.h
	gcc -o contar_caracteres_ASCII.o -c contar_caracteres_ASCII.c -ansi -Wall -pedantic -g

funcoes_huffman.o: funcoes_huffman.c contar_caracteres_ASCII.h manipulacao_bytes.h queue.h
	gcc -o funcoes_huffman.o -c funcoes_huffman.c -ansi -Wall -pedantic -g

manipulacao_bytes.o: manipulacao_bytes.c
	gcc -o manipulacao_bytes.o -c manipulacao_bytes.c -ansi -Wall -pedantic -g

queue.o: queue.c
	gcc -o queue.o -c queue.c -ansi -Wall -pedantic -g

clean:
	rm -rf *.o *~ huffman