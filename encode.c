#include "encode.h"
#include <stdio.h>
#include <string.h>
#include "bits.h"

// debug
void printTree(TreeNode *tree, int deep) {
    if (!tree) return;
    printTree(tree->right, deep + 1);
    for (int i = 0; i < deep; ++i)
        printf("\t");
    printf("%u(%c)\n", tree->symbol, tree->symbol);
    printTree(tree->left, deep + 1);
}
void printCodeTable(CharCode * codeTable) {
    for (int i = 0; i < 256; ++i)
        if (codeTable[i].code)
            printf("%c = %s\n", (unsigned char) i, codeTable[i].code);
}

// count frequency of each character within file
void getCounterOfFile(Encoder *en) {
    FILE * file = fopen(en->fileName, "rb");
    if (!file) exit(13); // cannot open file
    fseek(file, 0L, SEEK_END);
    en->fileSize = ftell(file);
    fseek(file, 0L, SEEK_SET);

    unsigned long * counter = calloc(256, sizeof(unsigned long));
    for (unsigned long i = 0; i < en->fileSize; ++i) // fill counter
        ++counter[(unsigned char) fgetc(file)];
    en->counter = counter;
    fclose(file);
}

// create a queue, memory is allocated for each symbol-node of tree (freed in deleteTree() )
// also memory allocated for counter (freed in deleteEncoder() )
Queue createPriorityQueue(const unsigned long counter[256]) {
    Queue q = {}; // empty queue
    for (int i = 0; i < 256; ++i)
        if (counter[i]) { // for every encouraged char in the text add it to queue with its frequency as a priority
            TreeNode *node = malloc(sizeof(TreeNode));
            if (!node) exit(14); // cannot allocate memory
            node->right = node->left = NULL; // final node
            node->symbol = (unsigned char) i;
            enqueue(&q, node, counter[i]); // put in queue
        }
    return q;
}

// memory allocated for each code of symbol in table of codes (freed in deleteEncoder() )
void fillCodeTable(CharCode *table, const TreeNode *tree, char *prefix, int prefixLen) {
    if (!tree) return;
    if (!tree->left && !tree->right) { // for symbols save complete code in the table
        if (!prefixLen) { // in case if tree contains only 1 node
            char *code = calloc(2, sizeof(char));
            code[0] = '0';
            table[tree->symbol] = (CharCode) {code, 1};
            return;
        }
        char * code = calloc((prefixLen + 1), sizeof(char)); // allocate memory for code string
        if (!code) exit(40); // cannot allocate code of symbol

        strcpy(code, prefix); // copy prefix
        table[tree->symbol] = (CharCode) {code, prefixLen};
        prefix[prefixLen - 1] = 0; // clear to go back
        return;
    }
    prefix[prefixLen] = '0'; // for left subtree add '0'
    fillCodeTable(table, tree->left, prefix, prefixLen + 1);
    prefix[prefixLen] = '1'; // for right subtree add '1'
    fillCodeTable(table, tree->right, prefix, prefixLen + 1);
    prefix[prefixLen] = 0; // clear to go back
}

// put metadata for decode in the file buffer
void fillMeta(Encoder *en) {
    // first 2 byte - number of different bytes
    // then for each ascii code 5 bytes 1 for code itself then 4 is for frequency
    unsigned char *buffer = en->buffer;
    unsigned long bufPos = 2;
    ShortBytes sb; LongBytes lb;
    sb.asShort = en->counterLen;
    memcpy(buffer, sb.asBytes, 2);
    for (int i = 0; i < 256; ++i)
        if (en->counter[i]) {
            buffer[bufPos++] = (unsigned char) i;
            lb.asLong = en->counter[i];
            memcpy(buffer + bufPos, lb.asBytes, 4);
            bufPos += 4;
        }
    lb.asLong = en->fileSize;
    memcpy(buffer + bufPos, lb.asBytes, 4);
    en->bufPos = bufPos + 4;
}

// memory for buffer, temp buffer allocated (no free)
void fillBuffer(Encoder *en) {
    FILE *file = fopen(en->fileName, "rb");
    if (!file) exit(20); // cannot allocate

    // this buffer contains '0' & '1' string representation of encoded data
    // then it will be interpreted as byte sequence and writen to en->buffer
    unsigned long tempBufLen = en->fileSize > 4096 ? en->fileSize : 4096,
                  bufPos = en->bufPos;
    unsigned char *temp = calloc(tempBufLen, sizeof(unsigned char)),
                  *buffer = en->buffer;
    unsigned long tempPos = 0; int eof = 0;

    while (!eof) {
        // copy codes of bytes to temp buffer
        while (tempBufLen - tempPos >= 16) { // til can potentially contain next code-string
            // fill the buffer with string representation of codes
            int next_ch = fgetc(file);
            if (next_ch == EOF) { eof = 1; break; }

            CharCode code = en->codeTable[next_ch];
            memcpy(temp + tempPos, code.code, code.len); // add symbol to buffer
            tempPos += code.len; // put pos after added code
        }
        // copy encoded bytes to result buffer
        unsigned long writenPos = 0;
        for (; writenPos + 8 <= tempPos; writenPos += 8) {
            buffer[bufPos++] = convertStringByte(temp + writenPos);
        }
        memcpy(temp, temp + writenPos, tempPos - writenPos);
        tempPos -= writenPos;
    }
    fclose(file);
    // write remain byte
    if (tempPos > 0) {
        unsigned char rem[8];
        memcpy(rem, temp, tempPos);
        for (int i = (int) tempPos; i < 8; ++ i) rem[i] = '0';
        buffer[bufPos++] = convertStringByte(rem);
    }
    en->bufPos = bufPos;
    free(temp);
}

// memory for code table and code lens is allocated (freed in deleteEncoder())
void encode(Encoder *en) {
    getCounterOfFile(en);
    Queue queue = createPriorityQueue(en->counter);
    en->counterLen = (short) queue.len;
    TreeNode * tree = makeTree(&queue);
    printTree(tree, 0);

    char prefix[25] = "";
    en->codeTable = calloc(256, sizeof(CharCode));
    fillCodeTable(en->codeTable, tree, prefix, 0);
    deleteTree(tree);
    printCodeTable(en->codeTable);

    en->buffer = calloc(en->fileSize + (6 + 5 * en->counterLen), sizeof(unsigned char));
    fillMeta(en);
    fillBuffer(en);

    FILE * out = fopen(en->outName, "wb");
    if (!out) exit(63); // cannot open such file
    fwrite(en->buffer, 1, en->bufPos, out);
}

// free all remain memory allocated for encoder
void deleteEncoder(Encoder * en) {
    for (int i = 0; i < 256; ++i)
        if (en->codeTable[i].code)
            free(en->codeTable[i].code);
    free(en->codeTable);
    free(en->counter);
    free(en->buffer);
}
