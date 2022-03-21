#include "decode.h"
#include "encode.h"
#include "bits.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void recoverCounter(Decoder *dec){
    FILE* file = fopen(dec->fileName, "rb");
    if (!file) exit(17); // no such file
    dec->file = file;

    // counter size contain a real count of blocks of symbols to read
    ShortBytes sb;
    for (int i = 0; i < 2; ++i)
        sb.asBytes[i] = (unsigned char) fgetc(file);
    dec->counterSize = sb.asShort;

    // each block of encoded file represents 5 bytes
    // 1st - ascii code of coding byte; 2-5th - freq of this code
    LongBytes lb;
    for (int i = 0; i < dec->counterSize; ++i) {
        int asciiCode = fgetc(file);
        for (int j = 0; j < 4; ++j)
            lb.asBytes[j] = (unsigned char) fgetc(file);
        dec->counter[asciiCode] = lb.asLong;
    }

    // last 4 bytes contain unsigned long length of origin file
    for (int i = 0; i < 4; ++i) {
        lb.asBytes[i] = (unsigned char) fgetc(file);
    }
    dec->fileSize = lb.asLong;
}

int decodeByte(TreeNode * tree, unsigned char * dest, const unsigned char * src) {
    int len = 0;
    while (tree->left || tree->right)
        tree = src[len++] == '1' ? tree->right : tree->left;
    *dest = tree->symbol;
    return len;
}

void fillOutBuffer(Decoder * dec) {
    unsigned long tempLen = dec->fileSize > 4096 ? dec->fileSize : 4096,
        bufPos = 0, tempPos = 0;
    unsigned char *temp = malloc(tempLen * sizeof(unsigned char)), *buffer = dec->buffer;
    int eof = 0;
    while (!eof) {
        for (; tempPos + 8 < tempLen; tempPos += 8) {
            int byte = fgetc(dec->file);
            if (byte == EOF) { eof = 1; break; }
            convertByteString((unsigned char) byte, temp + tempPos);
        }
        unsigned long writenPos = 0;
        while (eof ? (bufPos < dec->fileSize) : (tempPos - writenPos >= MAX_CODE_LEN))
            writenPos += decodeByte(dec->tree, buffer + bufPos++, temp + writenPos);
        tempPos -= writenPos;
        memcpy(temp, temp + writenPos, tempPos);
    }
    fclose(dec->file);
}

void decode(Decoder *dec) {
    recoverCounter(dec);
    Queue q = createPriorityQueue(dec->counter);
    dec->tree = makeTree(&q);
    dec->buffer = malloc(dec->fileSize * sizeof(unsigned char));
    fillOutBuffer(dec);

    FILE *out = fopen(dec->outName, "wb");
    fwrite(dec->buffer, 1, dec->fileSize, out);
    fclose(out);
}

void deleteDecoder(Decoder *dec) {
    deleteTree(dec->tree);
    free(dec->buffer);
}