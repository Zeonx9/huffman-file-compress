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
            TreeNode *node = malloc(sizeof(TreeNode));
            if (!node)
                exit(14); // cannot allocate memory
            node->right = node->left = NULL;
            node->symb = (unsigned char) i;
            enqueue(&q, node, counter[i]);
        }
    return q;
}

int main() {
    Queue q = process("test.txt");
    while (q.front) {
        QueueNode *n = dequeue(&q);
        printf("%c - %ld; ", n->data->symb, n->priority);
    }
    return 0;
}
