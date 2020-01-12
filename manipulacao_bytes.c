#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "manipulacao_bytes.h"

#define BYTE 8

TByteMap *byteInit (unsigned int max_size)
{
	unsigned int size;
	TByteMap * map = (TByteMap*)malloc(sizeof(TByteMap));

	if( max_size % BYTE != 0) 	/* Se não for múltiplo de 8, será alocado um byte a mais. */
	{
		size = (max_size / BYTE) + 1;
	}
	else
	{
		size = (max_size / BYTE);
	}
	map->length = 0;
	map->max_size = size * BYTE;
	map->contents = (TByte*)malloc(sizeof(TByte)*size);
	while( size > 0)
	{
		map->contents[size - 1].b0 = (unsigned)0;
		map->contents[size - 1].b1 = (unsigned)0;
		map->contents[size - 1].b2 = (unsigned)0;
		map->contents[size - 1].b3 = (unsigned)0;
		map->contents[size - 1].b4 = (unsigned)0;
		map->contents[size - 1].b5 = (unsigned)0;
		map->contents[size - 1].b6 = (unsigned)0;
		map->contents[size - 1].b7 = (unsigned)0;
		size = size - 1;
	}
	return map;
}

void printByte( TByte b)
{
		printf("%i", b.b0);
		printf("%i", b.b1);
		printf("%i", b.b2);
		printf("%i", b.b3);
		printf("%i", b.b4);
		printf("%i", b.b5);
		printf("%i", b.b6);
		printf("%i", b.b7);
		printf("\n");
}

void printByteMap( TByteMap *b)
{
	unsigned int i = 0, index = 0;

	while(index < b->length)
	{
		if( index < b->length)	{ printf("%i", b->contents[ i ].b0); index++;}
		if( index < b->length)	{ printf("%i", b->contents[ i ].b1); index++;}
		if( index < b->length)	{ printf("%i", b->contents[ i ].b2); index++;}
		if( index < b->length)	{ printf("%i", b->contents[ i ].b3); index++;}
		if( index < b->length)	{ printf("%i", b->contents[ i ].b4); index++;}
		if( index < b->length)	{ printf("%i", b->contents[ i ].b5); index++;}
		if( index < b->length)	{ printf("%i", b->contents[ i ].b6); index++;}
		if( index < b->length)	{ printf("%i", b->contents[ i ].b7); index++;}
		i++;
	}
	printf("\n");
}
