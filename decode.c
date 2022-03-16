#include "decode.h"
#include <stdio.h>
#include <stdlib.h>
#include "bits.h"
#include "encode.h"
#include "tree_queue.h"


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

void writeDataToBuff(Decoder *dec){
    FILE *file = dec->file;
    char byte;
    while ((byte = (char) fgetc(file)) != EOF){

    }

}


void decode(Decoder *dec){
    dec->file = fopen(dec->fileName, "rb");
    if (!dec->file) exit(17); // no such file
    recoverCounter(dec);
    unsigned long *counter = dec->counter;
    Queue priorityQueue = createPriorityQueue(counter);
    TreeNode *tree = makeTree(&priorityQueue);

}