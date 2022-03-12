#include <stdio.h>
#include "tree_queue.h"

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

int main() {
    Queue q = process("test.txt");
    for (QueueNode *n = q.front; n; n = n->next)
        printf("%c - %ld\n", n->data->symbol, n->priority);
    TreeNode *tree = makeTree(&q);
    printTree(tree, 0);
    return 0;
}
