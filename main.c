#include <stdio.h>
#include "tree_queue.h"
#include "encode.h"

void printTree(TreeNode *tree, int deep) {
    if (!tree) return;
    printTree(tree->right, deep + 1);
    for (int i = 0; i < deep; ++i)
        printf("\t");
    printf("%u(%c)\n", tree->symbol, tree->symbol);
    printTree(tree->left, deep + 1);
}

void printQueue(Queue q) {
    for (QueueNode *n = q.front; n; n = n->next)
        printf("%c - %ld\n", n->data->symbol, n->priority);
}

void printCodeTable(char ** codeTable) {
    for (int i = 0; i < 256; ++i)
        if (codeTable[i])
            printf("%c = %s\n", (unsigned char) i, codeTable[i]);
}

int main() {
    Encoder en = {"test.txt"};
    encode(&en);

    //show results
    printTree(en.tree, 0);
    printCodeTable(en.codeTable);

    deleteEncoder(&en);
    return 0;
}
