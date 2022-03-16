#ifndef HUFFMAN_FILES_DECODE_H
#define HUFFMAN_FILES_DECODE_H
#include <stdio.h>

typedef struct decoder{
    char fileName[100];
    unsigned long counter[256];
    unsigned short int counterSize;
    unsigned long int inpFileSize;
    FILE *file;
}Decoder;

void recoverCounter(Decoder *dec);

unsigned char *byteAsString(unsigned char *buffer, unsigned char byte);

void decode(Decoder * dec);

#endif //HUFFMAN_FILES_DECODE_H
