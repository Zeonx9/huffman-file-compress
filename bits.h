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

typedef union long_bytes_ {
    unsigned long asLong;
    unsigned char asBytes[4];
} LongBytes;

typedef union short_bytes_ {
    unsigned long asShort;
    unsigned char asBytes[2];
} ShortBytes;

/// receive string of 8-length '0' and '1' sequence and return char with such code
unsigned char convertStringByte(const char seq[8]);

#endif //HUFFMAN_FILES_BITS_H
