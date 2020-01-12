#ifndef MANIPULACAO_BYTES_H
#define MANIPULACAO_BYTES_H

typedef struct byte TByte;
struct byte
{
    unsigned b0:1;
    unsigned b1:1;
    unsigned b2:1;
    unsigned b3:1;
    unsigned b4:1;
    unsigned b5:1;
    unsigned b6:1;
    unsigned b7:1;
};

typedef struct byteMap TByteMap;
struct byteMap
{
	unsigned int max_size;
	unsigned int length;
	TByte *contents;
};

TByteMap *byteInit (unsigned int max_size);
void printByte( TByte b);
void printByteMap( TByteMap *b);

#endif
