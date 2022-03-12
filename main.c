#include <stdio.h>
#include "tree_queue.h"
#include <string.h>

Queue process(char *fileName) {
    FILE * file = fopen(fileName, "rb");
    if (!file)
        exit(13); // cannot open file
    int counter[256] = {}, ch;
    while ((ch = fgetc(file)) != EOF)
        ++counter[(unsigned char) ch];

    fclose(file);
    Queue q = {};
    for (int i = 0; i < 256; ++i)
        if (counter[i]) {
            //printf("%c - %d\n", (unsigned char) i, counter[i]);
            TreeNode *node = malloc(sizeof(TreeNode));
            if (!node)
                exit(14); // cannot allocate memory
            node->right = node->left = NULL;
            node->symbol = (unsigned char) i;
            enqueue(&q, node, counter[i]);
        }
    return q;
}

void printTree(TreeNode *tree, int deep) {
    if (!tree) return;
    printTree(tree->right, deep + 1);
    for (int i = 0; i < deep; ++i)
        printf("\t");
    printf("%u(%c)\n", tree->symbol, tree->symbol);
    printTree(tree->left, deep + 1);
}

void fillCodeTable(TreeNode *tree, char **table, char *prefix, int prefixLen) {
    if (!tree)
        return;
    if (!tree->left && !tree->right) { // for symbols save complete code in the table
        if (!prefixLen) {
            char *code = calloc(2, sizeof(char));
            code[0] = '0';
            table[tree->symbol] = code;
            return;
        }
        char * code = malloc(prefixLen * sizeof(char));
        strcpy(code, prefix);
        table[tree->symbol] = code;
        prefix[prefixLen - 1] = 0;
        return;
    }
    prefix[prefixLen] = '0';
    fillCodeTable(tree->left, table, prefix, prefixLen + 1);
    prefix[prefixLen] = '1';
    fillCodeTable(tree->right, table, prefix, prefixLen + 1);
    prefix[prefixLen] = 0;
}

int main() {
    Queue q = process("test.txt");
    for (QueueNode *n = q.front; n; n = n->next)
        printf("%c - %ld\n", n->data->symbol, n->priority);
    TreeNode *tree = makeTree(&q);
    printTree(tree, 0);
    char **codeTable = calloc(256, sizeof(char *));
    char prefix[25] = {};
    fillCodeTable(tree, codeTable, prefix, 0);
    for (int i = 0; i < 256; ++i)
        if (codeTable[i])
            printf("%c = %s\n", (unsigned char) i, codeTable[i]);
    return 0;
}
