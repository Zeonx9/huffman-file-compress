#include "decode.h"
#include <stdio.h>
#include <stdlib.h>
#include "bits.h"

void recoverCounter(Decoder *dec){
    FILE* file = fopen(dec->fileName, "rb");
    if (!file) exit(17); // no such file

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