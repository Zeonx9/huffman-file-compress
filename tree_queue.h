#ifndef HUFFMAN_FILES_TREE_QUEUE_H
#define HUFFMAN_FILES_TREE_QUEUE_H
#include <stdbool.h>
#include <stdlib.h>

// ---structures---

/// Recursive structure of binary tree, as data on each node here is a ascii code of symbol
typedef struct tree_node_ {
    unsigned char symbol;
    struct tree_node_ *left, *right;
} TreeNode;

/// Node of queue structure of tree is similar to linked list, also each node has a priority
typedef struct queue_node_ {
    TreeNode *data;
    unsigned long priority;
    struct queue_node_ *next;
} QueueNode;

/// wrapper for QueueNode, has pointer to first element of queue
typedef struct {
    QueueNode *front;
} Queue;

// ---functions---

/// main method to cope with priority queue, all elements are in ascending order by priority
void enqueue(Queue *q, TreeNode *data, unsigned long priority);

/// main method to get element from queue, return QueueNode with lowest priority
QueueNode * dequeue(Queue *q);

/// method to build a Huffman tree using queue
TreeNode * makeTree(Queue *q);

/// method to delete tree and free space
void deleteTree(TreeNode * tree);

#endif //HUFFMAN_FILES_TREE_QUEUE_H
