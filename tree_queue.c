#include "tree_queue.h"

void enqueue(Queue *q, TreeNode *t, unsigned long priority) {
    QueueNode * node = malloc(sizeof(QueueNode)); // allocate new node
    if (!node)
        exit(9); // cannot allocate memory for node
    node->data = t; node->priority = priority; node->next = NULL;
    if (!q->front)  { // init queue
        q->front = node;
        return;
    }
    if (priority < q->front->priority) { // insert in front
        node->next = q->front;
        q->front = node;
        return;
    }
    QueueNode *cur = q->front; // insert in the middle of at the end
    while (cur->next && cur->next->priority <= priority)
        cur = cur->next;
    node->next = cur->next;
    cur->next = node;
}

QueueNode * dequeue(Queue *q) {
    if (!q->front) { // error if queue is empty
        exit(15);
    }
    QueueNode *out = q->front;
    q->front = q->front->next;
    return out;
}

TreeNode * makeTree(Queue *q){
    if (!q->front)
        return NULL;
    if (!q->front->next)
        return q->front->data;
    TreeNode *tree = malloc(sizeof(TreeNode));
    if (!tree)
        exit(10); // cannot allocate memory for tree node
    QueueNode *qn1 = dequeue(q), *qn2 = dequeue(q);
    tree->left = qn1->data, tree->right = qn2->data;
    tree->symbol = 0;
    enqueue(q, tree, qn1->priority + qn2->priority);
    return makeTree(q);
}