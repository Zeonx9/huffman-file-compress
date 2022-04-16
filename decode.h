#ifndef HUFFMAN_FILES_DECODE_H
#define HUFFMAN_FILES_DECODE_H
#include <stdio.h>
#include "tree_queue.h"

typedef struct decoder {
    // initial data
    char fileName[100];
    char outName[100];
    FILE *file;
    FILE *outfile;
    // recovered from meta
    short counterSize;
    unsigned long counter[256];
    unsigned long fileSize;
    // evaluated while decoder work
    TreeNode *tree;
    unsigned char *outBuff;
} Decoder;

void decode(Decoder * dec);

void deleteDecoder(Decoder * dec);

#endif //HUFFMAN_FILES_DECODE_H
