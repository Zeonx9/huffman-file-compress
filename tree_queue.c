#include "tree_queue.h"

void enqueue(Queue *q, TreeNode *t, unsigned long priority) {
    QueueNode * node = malloc(sizeof(QueueNode)); // allocate new node
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