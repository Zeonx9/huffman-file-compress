#ifndef HUFFMAN_FILES_ENCODE_H
#define HUFFMAN_FILES_ENCODE_H
#include "tree_queue.h"

/// container for new string-code of
typedef struct char_code_ {
    char *code;
    int len;
}CharCode;

/// main object of encode interface contain all data to compress file
typedef struct encoder_ {
    // initial data
    char fileName[100];
    char outName[100];
    unsigned long fileSize;
    // counted by according methods
    unsigned long * counter;
    short counterLen;
    CharCode * codeTable;
    // needed to create output file
    unsigned char * buffer;
    unsigned long bufPos;
} Encoder;

/// method to encode all file (just combine all steps together)
void encode(Encoder * en);

/// open given file count frequency of each character and return queue where frequency is a priority
Queue createPriorityQueue(const unsigned long counter[256]);

/// method to extract codes from tree and store them in table
void fillCodeTable(CharCode *table, const TreeNode *tree, char *prefix, int prefixLen);

/// method to free spaces taken by encoder
void deleteEncoder(Encoder * en);
#endif //HUFFMAN_FILES_ENCODE_H
