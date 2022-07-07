#include <stdio.h>
#include <stdlib.h>
#include "binarySearchTree.h"
#include "queue.h"

void addNode(bst** root, int value) {
    bst* newNode = (bst*) malloc(sizeof(bst));
    if (newNode == NULL) {
        exit(1);
    }
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    if (*root == NULL) {
        *root = newNode;
        return;
    }
    if (newNode->value < (*root)->value) {
        addNode(&((*root)->left), value);
    }
    if (newNode->value > (*root)->value) {
        addNode(&((*root)->right), value);
    }
    if (newNode->value == (*root)->value) {
        printf("Wert ist schon im Baum. Konnte nicht hinzugefuegt werden!");
    }
}

int find(bst* root, int value) {
    if (root == NULL) {
        return -1;
    }
    if (root->value == value) {
        return 1;
    }
    if (root->value < value) {
        return find(root->right, value);
    } else {
        return find(root->left, value);
    }
}

int findDepthFunc(bst* root, int value, int counter) {
    ++counter;
    if (root == NULL) {
        return -1;
    }
    if (root->value == value) {
        return counter;
    }
    if (root->value < value) {
        return findDepthFunc(root->right, value, counter);
    } else {
        return findDepthFunc(root->left, value, counter);
    }
}

int findDepth(bst* root, int value) {
    unsigned int counter = 0;
    return findDepthFunc(root, value, counter);
}

void deleteTree(bst** rootPtr) {
    if (rootPtr == NULL) {
        return;
    }
    if (*rootPtr != NULL) {
        deleteTree(&((*rootPtr)->left));
        deleteTree(&((*rootPtr)->right));
        free(*rootPtr);
        *rootPtr = NULL;
    }
}

int findByDepthFirstSearch(bst* root, int value) {
    if (root == NULL) {
        return -1;
    }
    if (root->value == value) {
        return 1;
    }
    if (findByDepthFirstSearch(root->left, value)) {
        return 1;
    }
    if (findByDepthFirstSearch(root->right, value)) {
        return 1;
    }
    return -1;
}


void addToQueue(queue** myQueue, bst* node) {
    queue* newElement = (queue*) malloc(sizeof(queue));
    if (newElement == NULL) {
        exit(1);
    }
    newElement->next = NULL;
    newElement->node = node;
    if (*myQueue == NULL) {
        *myQueue = newElement;
        return;
    }
    queue* current = *myQueue;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newElement;
}

int removeFromQueueTail(queue** myQueue) {
    if (myQueue == NULL) {
        return 0;
    }
    if (*myQueue == NULL) {
        return 0;
    }
    queue* current = *myQueue;
    if (current->next == NULL) {
        free(current);
        *myQueue = NULL;
        return 1;
    }
    while (current->next->next != NULL) {
        current = current->next;
    }
    free(current->next);
    current->next = NULL;
    return 1;
}

void removeFromQueue(queue** myQueue) {
    if (myQueue == NULL) {
        return;
    }
    if (*myQueue == NULL) {
        return;
    }
    queue* current = *myQueue;
    if (current->next->node == NULL) {
        free(current);
        *myQueue = NULL;
        return;
    }
    *myQueue = current->next;
    free(current);
    current = NULL;
}


void deleteQueue(queue** myQueue) {
    if (myQueue == NULL) {
        return;
    }
    if (*myQueue == NULL) {
        return;
    }
    while (removeFromQueueTail(myQueue)) {}
}

int findByBreadthFirstSearch(bst* root, int value) {
    queue* myQueue = NULL;
    addToQueue(&myQueue, root);
    while (myQueue != NULL) {
        if (myQueue->node->value == value) {
            deleteQueue(&myQueue);
            return 1;
        }
        addToQueue(&myQueue, myQueue->node->left);
        addToQueue(&myQueue, myQueue->node->right);
        removeFromQueue(&myQueue);
    }
    return -1;
}

int main() {
    bst* root = NULL;
    addNode(&root, 20);
    addNode(&root, 10);
    addNode(&root, 5);
    addNode(&root, 30);
    addNode(&root, 15);
    addNode(&root, 25);
    bst* root2 = NULL;
    int result = findByBreadthFirstSearch(root, 20);
    deleteTree(&root);
    int x = 2147483647;
    int y = 783465;
    x = x ^ y;
    y = x ^ y;
    x = x ^ y;
    x = 2147483647;
    y = 783465;
    x = x + y;
    y = x - y;
    x = x - y;
    return 0;
}
