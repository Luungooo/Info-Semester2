#include <stdio.h>
#include <stdlib.h>
#include "binarytree.h"

bt *createNode(char value) {
    bt *newNode = (bt *) malloc(sizeof(bt));
    if (newNode == NULL) {
        exit(1);
    }
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void traversePreorder(bt *root) {
    if (root != NULL) {
        printf("%c", root->value);
        traversePreorder(root->left);
        traversePreorder(root->right);
    }
}

void traverseInorder(bt *root) {
    if (root != NULL) {
        traverseInorder(root->left);
        printf("%c", root->value);
        traverseInorder(root->right);
    }
}

void traversePostorder(bt *root) {
    if (root != NULL) {
        traversePostorder(root->left);
        traversePostorder(root->right);
        printf("%c", root->value);
    }
}

int getDepth(bt *root) {
    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL && root->right == NULL)
        return 1;
    int leftDepth, rightDepth;
    leftDepth = getDepth(root->left);
    rightDepth = getDepth(root->right);
    if (leftDepth > rightDepth) {
        return (leftDepth + 1);
    }
    return (rightDepth + 1);
}
void deleteTree(bt** rootPtr) {
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

int main() {
    bt *root = createNode('A');
    root->left = createNode('B');
    root->right = createNode('C');
    root->left->left = createNode('D');
    root->left->right = createNode('E');
    traversePreorder(root);
    printf("\n");
    traverseInorder(root);
    printf("\n");
    traversePostorder(root);
    printf("\n");
    printf("%d", getDepth(root));
    deleteTree(&root);
    return 0;
}