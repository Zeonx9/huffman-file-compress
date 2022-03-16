#include "decode.h"
#include <stdio.h>
#include <stdlib.h>
#include "bits.h"

void recoverCounter(Decoder *dec){
    FILE* file = fopen(dec->fileName, "rb");
    if (!file) exit(17); // no such file

    // size contain a real count of blocks of symbols to read
    ShortBytes sb;
    for (int i = 0; i < 2; ++i)
        sb.asBytes[i] = (unsigned char) fgetc(file);
    dec->counterSize = sb.asShort;

    LongBytes lb;
    for (int i = 0; i < dec->counterSize; ++i) {
        int asciiCode = fgetc(file);
        for (int j = 0; j < 4; ++j)
            lb.asBytes[j] = (unsigned char) fgetc(file);
        dec->counter[asciiCode] = lb.asLong;
    }
}