#ifndef HUFFMAN_FILES_DECODE_H
#define HUFFMAN_FILES_DECODE_H

#include <stdio.h>
#include "tree_queue.h"

typedef struct decoder_ {
    char fileName[100];
    char outName[100];
    unsigned long fileSize;
    FILE * file;
    unsigned long counter[256];
    short counterSize;
    TreeNode * tree;
    unsigned char * buffer;
} Decoder;

void decode(Decoder *dec);

void deleteDecoder(Decoder *dec);

#endif //HUFFMAN_FILES_DECODE_H
