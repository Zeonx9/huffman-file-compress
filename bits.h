#ifndef HUFFMAN_FILES_BITS_H
#define HUFFMAN_FILES_BITS_H

/// struct used to encode binary-string to bit sequence
typedef struct char_bit_ {
    union {
        unsigned char ch;
        struct {
            unsigned char  b1: 1;
            unsigned char  b2: 1;
            unsigned char  b3: 1;
            unsigned char  b4: 1;
            unsigned char  b5: 1;
            unsigned char  b6: 1;
            unsigned char  b7: 1;
            unsigned char  b8: 1;
        } bits;
    };
} CharBit;

/// convert memory between unsigned long and bytes which represent it
typedef union long_bytes_ {
    unsigned long asLong;
    unsigned char asBytes[4];
} LongBytes;

/// convert memory between  and bytes which represent it
typedef union short_bytes_ {
    short asShort;
    unsigned char asBytes[2];
} ShortBytes;

/// receive string of 8-length '0' and '1' sequence and return char with such code
unsigned char convertStringByte(const unsigned char seq[8]);
void convertByteString(unsigned char *buff, unsigned char byte);
#endif //HUFFMAN_FILES_BITS_H
