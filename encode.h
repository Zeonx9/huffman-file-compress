#ifndef HUFFMAN_FILES_ENCODE_H
#define HUFFMAN_FILES_ENCODE_H
#include "tree_queue.h"

// it's useless yet
typedef struct {
    char fileName[100];
    unsigned long fileSize;
    unsigned long * counter;
    Queue initialQueue;
    TreeNode * tree;
    char ** codeTable;
} Encoder;

/// method to encode all file (just combine all steps together)
void encode(Encoder * en);

/// open given file count frequency of each character and return queue where frequency is a priority
Queue createPriorityQueueFromFile(Encoder *en);

/// by given Huffman tree fill table of new shorter code which satisfy fano condition
void fillCodeTable(Encoder *en, TreeNode * tree, char *prefix, int prefixLen);

/// method to free spaces taken by encoder
void deleteEncoder(Encoder * en);

#endif //HUFFMAN_FILES_ENCODE_H
