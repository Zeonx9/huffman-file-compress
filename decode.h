#ifndef HUFFMAN_FILES_DECODE_H
#define HUFFMAN_FILES_DECODE_H

typedef struct decoder{
    char fileName[100];
    unsigned long counter[256];
    unsigned short int counterSize;
}Decoder;

void rebuildCounter(Decoder *decoder_);

#endif //HUFFMAN_FILES_DECODE_H
