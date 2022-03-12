#ifndef HUFFMAN_FILES_TREE_QUEUE_H
#define HUFFMAN_FILES_TREE_QUEUE_H
#include <stdbool.h>
#include <stdlib.h>

typedef struct tree_node_ {
    unsigned char symb;
    struct tree_node_ *left, *right;
} TreeNode;

typedef struct queue_node_ {
    TreeNode *data;
    unsigned long priority;
    struct queue_node_ *next;
} QueueNode;

typedef struct {
    QueueNode *front;
} Queue;

void enqueue(Queue *q, TreeNode *t, unsigned long priority);
QueueNode * dequeue(Queue *q);

#endif //HUFFMAN_FILES_TREE_QUEUE_H
