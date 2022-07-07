#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue {
    struct queue* next;
    struct binarySearchTree* node;
} queue;

#endif //QUEUE_H
