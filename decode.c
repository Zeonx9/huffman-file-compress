#include "decode.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bits.h"


void recoverCounter(Decoder *dec){
    FILE *file = dec->file;
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
    dec->inpFileSize = lb.asLong;
}


int decodeByte(TreeNode *tree, unsigned char *dest, const unsigned char *src){
    int i = 0;
    while (tree->left || tree->right){
        tree = src[i++] == '0' ? tree->left : tree->right;
    }
    *dest = tree->symbol;
    return i;
}

void writeDataToBuff(Decoder *dec){
    FILE *file = dec->file;
    unsigned long tempPos = 0, buffPos = 0, tempSize = dec->inpFileSize > 4096 ? dec->inpFileSize : 4096;
    unsigned char *tempBuff = (unsigned char*) malloc(tempSize * sizeof(unsigned char));
    int eof = 0;
    while (!eof){
        while (tempPos + 8 <= tempSize) {
            int byte = fgetc(file);
            if (byte == EOF) {
                eof = 1;
                break;
            }
            convertByteString(tempBuff + tempPos, byte);
            tempPos += 8;
        }

        unsigned long writenPos = 0;
        while (eof ? (buffPos < dec->inpFileSize) : (tempPos - writenPos >= MAX_CODE_LEN)){
             writenPos += decodeByte(dec->tree, dec->outBuff + buffPos++, tempBuff + writenPos);
        }

        tempPos -= writenPos;
        memcpy(tempBuff, tempBuff + writenPos, tempPos);
    }
    free(tempBuff);
}


void decode(Decoder *dec){
    dec->file = fopen(dec->fileName, "rb");
    if (!dec->file) exit(17); // no such file
    recoverCounter(dec);
    unsigned long *counter = dec->counter;
    Queue priorityQueue = createPriorityQueue(counter);
    dec->tree = makeTree(&priorityQueue);
    dec->outBuff = (unsigned char*) malloc(dec->inpFileSize * sizeof(unsigned char));
    writeDataToBuff(dec);
    FILE *outputFile = fopen("decoded.txt", "wb");
    if (!outputFile){
        exit(82);
    }
    fwrite(dec->outBuff, 1, dec->inpFileSize, outputFile);
    fclose(outputFile);
    free(dec->outBuff);
}