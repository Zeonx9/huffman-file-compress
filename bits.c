#include "bits.h"

unsigned char convertStringByte(const unsigned char seq[8]) {
    CharBit converter = {};
    converter.bits.b1 = seq[0] - '0';
    converter.bits.b2 = seq[1] - '0';
    converter.bits.b3 = seq[2] - '0';
    converter.bits.b4 = seq[3] - '0';
    converter.bits.b5 = seq[4] - '0';
    converter.bits.b6 = seq[5] - '0';
    converter.bits.b7 = seq[6] - '0';
    converter.bits.b8 = seq[7] - '0';
    return converter.ch;
}

void convertByteString(unsigned char *buff, const unsigned char byte){
    CharBit converter = {byte};
    buff[0] = converter.bits.b1 + '0';
    buff[1] = converter.bits.b2 + '0';
    buff[2] = converter.bits.b3 + '0';
    buff[3] = converter.bits.b4 + '0';
    buff[4] = converter.bits.b5 + '0';
    buff[5] = converter.bits.b6 + '0';
    buff[6] = converter.bits.b7 + '0';
    buff[7] = converter.bits.b8 + '0';
}

