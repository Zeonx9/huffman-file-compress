#ifndef HUFFMAN_FILES_DECODE_H
#define HUFFMAN_FILES_DECODE_H
#include <stdio.h>
#include "encode.h"

typedef struct decoder{
    char fileName[100];
    unsigned long counter[256];
    short counterSize;
    unsigned long inpFileSize;
    unsigned char *outBuff;
    FILE *file;
    TreeNode *tree;
}Decoder;

void decode(Decoder * dec);

#endif //HUFFMAN_FILES_DECODE_H
