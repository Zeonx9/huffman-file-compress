#include "bits.h"

unsigned char convertStringByte(const char seq[8]) {
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

