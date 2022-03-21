#include "bits.h"

unsigned char convertStringByte(const unsigned char seq[8]) {
    CharBit converter = {};
    converter.bits.b1 = seq[0] == '1';
    converter.bits.b2 = seq[1] == '1';
    converter.bits.b3 = seq[2] == '1';
    converter.bits.b4 = seq[3] == '1';
    converter.bits.b5 = seq[4] == '1';
    converter.bits.b6 = seq[5] == '1';
    converter.bits.b7 = seq[6] == '1';
    converter.bits.b8 = seq[7] == '1';
    return converter.ch;
}

void convertByteString(unsigned char byte, unsigned char *buf) {
    CharBit converter = {byte};
    buf[0] = converter.bits.b1 ? '1' : '0';
    buf[1] = converter.bits.b2 ? '1' : '0';
    buf[2] = converter.bits.b3 ? '1' : '0';
    buf[3] = converter.bits.b4 ? '1' : '0';
    buf[4] = converter.bits.b5 ? '1' : '0';
    buf[5] = converter.bits.b6 ? '1' : '0';
    buf[6] = converter.bits.b7 ? '1' : '0';
    buf[7] = converter.bits.b8 ? '1' : '0';
}

