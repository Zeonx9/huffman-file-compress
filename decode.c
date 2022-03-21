#include "decode.h"
#include <string.h>
#include "bits.h"
#include "encode.h"

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
    for (int i = 0; i < 4; ++i)
        lb.asBytes[i] = (unsigned char) fgetc(file);
    dec->fileSize = lb.asLong;
}


int decodeByte(TreeNode *tree, unsigned char *dest, const unsigned char *src){
    int len = 0;
    // while node has subtrees continue decoding turn left on '0' and right on '1'
    while (tree->left || tree->right)
        tree = src[len++] == '0' ? tree->left : tree->right;
    *dest = tree->symbol; // get ascii code of sequence
    return len;
}

void writeDataToBuff(Decoder *dec){
    unsigned long tempSize = dec->fileSize > 4096 ? dec->fileSize : 4096,
            tempPos = 0, buffPos = 0;
    unsigned char *tempBuff = (unsigned char*) malloc(tempSize * sizeof(unsigned char));
    int eof = 0;
    while (!eof){
        // fill temp buffer with sequences of 0&1 from encoded bytes, len of such sequence is divisible by 8
        while (tempPos + 8 <= tempSize) {
            int byte = fgetc(dec->file);
            if (byte == EOF) { eof = 1; break; } // end of reading if eof encouraged
            convertByteString(tempBuff + tempPos, byte);
            tempPos += 8;
        }
        // decode all bytes from given 1&0 sequence, if eof reached then decode til the end else
        // decode until possible max len of 1 code sequence cannot be fully contained in temp
        unsigned long writenPos = 0;
        while (eof ? (buffPos < dec->fileSize) : (tempPos - writenPos >= MAX_CODE_LEN))
             writenPos += decodeByte(dec->tree, dec->outBuff + buffPos++, tempBuff + writenPos);
        tempPos -= writenPos;
        memcpy(tempBuff, tempBuff + writenPos, tempPos); // copy undecoded tail of temp to its start
    }
    free(tempBuff);
}


void decode(Decoder *dec){
    dec->file = fopen(dec->fileName, "rb");
    if (!dec->file) exit(17); // no such file

    recoverCounter(dec);
    Queue q = createPriorityQueue(dec->counter);
    dec->tree = makeTree(&q);

    dec->outBuff = (unsigned char*) malloc(dec->fileSize * sizeof(unsigned char));
    writeDataToBuff(dec);

    FILE *outputFile = fopen(dec->outName, "wb");
    if (!outputFile) exit(82); // cannot open out file
    fwrite(dec->outBuff, 1, dec->fileSize, outputFile);
    fclose(outputFile);
}

void deleteDecoder(Decoder * dec){
    deleteTree(dec->tree);
    free(dec->outBuff);
}