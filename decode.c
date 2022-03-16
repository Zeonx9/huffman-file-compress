#include "decode.h"
#include <stdio.h>
#include <stdlib.h>
#include "bits.h"
#include <string.h>

void rebuildCounter(Decoder *decoder_){
    if (!decoder_->fileName){
        // No such file or directory
        exit(17);
    }

    FILE* file = fopen(decoder_->fileName, "r");
    unsigned char counterSize[2] = {0};
    for (int i = 0; i < 2; ++i) {
        counterSize[i] = fgetc(file);
    }
    ShortBytes sb;
    memcpy(sb.asBytes, counterSize, 2);
    unsigned short size = sb.asShort;
    // size contain a real count of blocks of symbols to read
    decoder_->counterSize = size;

    int asciiCode;
    unsigned char freq[4];
    LongBytes lb;
    for (int i = 0; i < size; ++i) {
        asciiCode = fgetc(file);
        for (int j = 0; j < 4; ++j) {
            freq[j] = fgetc(file);
        }

        memcpy(lb.asBytes, freq, 4);
        decoder_->counter[asciiCode] = lb.asLong;
    }
}