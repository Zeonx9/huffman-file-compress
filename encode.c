#include "encode.h"
#include <stdio.h>
#include <string.h>

// create a queue, memory is allocated for each symbol-node of tree (freed in deleteTree() )
// also memory allocated for counter (freed in deleteEncoder() )
Queue createPriorityQueueFromFile(Encoder *en) {
    FILE * file = fopen(en->fileName, "rb");
    if (!file)
        exit(13); // cannot open file
    fseek(file, 0L, SEEK_END);
    en->fileSize = ftell(file);
    fseek(file, 0L, SEEK_SET);
    unsigned long * counter = calloc(256, sizeof(unsigned long));
    for (unsigned long i = 0; i < en->fileSize; ++i) // fill counter
        ++counter[(unsigned char) fgetc(file)];
    en->counter = counter;
    fclose(file);

    Queue q = {}; // empty queue
    for (int i = 0; i < 256; ++i)
        if (counter[i]) { // for every encouraged char in the text add it to queue with its frequency as a priority
            TreeNode *node = malloc(sizeof(TreeNode));
            if (!node)
                exit(14); // cannot allocate memory
            node->right = node->left = NULL; // final node
            node->symbol = (unsigned char) i;
            enqueue(&q, node, counter[i]); // put in queue
        }
    return q;
}

// memory allocated for each code of symbol in table of codes (freed in deleteEncoder() )
void fillCodeTable(Encoder * en, TreeNode *tree, char *prefix, int prefixLen) {
    if (!tree)
        return;
    if (!tree->left && !tree->right) { // for symbols save complete code in the table
        if (!prefixLen) { // in case if tree contains only 1 node
            char *code = calloc(2, sizeof(char));
            code[0] = '0';
            en->codeTable[tree->symbol] = code;
            return;
        }
        char * code = malloc(prefixLen * sizeof(char)); // allocate memory for code string
        strcpy(code, prefix); // copy prefix
        en->codeTable[tree->symbol] = code;
        prefix[prefixLen - 1] = 0; // clear to go back
        return;
    }
    prefix[prefixLen] = '0'; // for left subtree add '0'
    fillCodeTable(en, tree->left, prefix, prefixLen + 1);
    prefix[prefixLen] = '1'; // for right subtree add '1'
    fillCodeTable(en, tree->right, prefix, prefixLen + 1);
    prefix[prefixLen] = 0; // clear to go back
}

// memory for code table is allocated (freed in deleteEncoder())
void encode(Encoder *en) {
    en->initialQueue = createPriorityQueueFromFile(en);
    en->tree = makeTree(&en->initialQueue);
    char prefix[25] = "";
    en->codeTable = calloc(256, sizeof(char *));
    fillCodeTable(en, en->tree, prefix, 0);
}

void deleteEncoder(Encoder * en) {
    for (int i = 0; i < 256; ++i)
        if (en->codeTable[i])
            free(en->codeTable[i]);
    free(en->codeTable);
    free(en->counter);
    deleteTree(en->tree);
}
