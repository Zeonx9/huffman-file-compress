#include "tree_queue.h"
#include "logs.h"

// memory allocated for each queue node (freed in makeTree() )
void enqueue(Queue *q, TreeNode *data, unsigned long priority) {
    QueueNode * node = malloc(sizeof(QueueNode)); // allocate new node
    if (!node) logExit(90, "cannot allocate q_node"); // cannot allocate memory for node
    node->data = data;
    node->priority = priority;
    node->next = NULL;
    ++q->len;
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
    if (!q->front) logExit(15, "empty queue (dequeue)"); // error if queue is empty
    QueueNode *out = q->front;
    q->front = q->front->next;
    return out;
}

// memory allocated for each tree node (freed in deleteTree() )
// queue is empty after
TreeNode * makeTree(Queue *q){
    if (!q->front) logExit(22, "empty queue (building tree)");
    while (q->front->next) {
        TreeNode *tree = malloc(sizeof(TreeNode));
        if (!tree) logExit(50, "cannot allocate tree_node"); // cannot allocate memory for tree node
        QueueNode *qn1 = dequeue(q), *qn2 = dequeue(q);
        tree->left = qn1->data, tree->right = qn2->data;
        tree->symbol = 0;
        enqueue(q, tree, qn1->priority + qn2->priority);
        free(qn1); free(qn2);
    }
    TreeNode *tree = q->front->data;
    free(dequeue(q));
    return tree;
}

// recursively delete tree
void deleteTree(TreeNode * tree) {
    if (!tree)
        return;
    deleteTree(tree->left);
    deleteTree(tree->right);
    free(tree);
}
