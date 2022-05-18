#include <stdio.h>
#include <stdlib.h>
#include "binarySearchTree.h"

void addNode(bst** root, int value) {
	bst* newNode = (bst*)malloc(sizeof(bst));
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
		printf("Wert ist schon im Baum. Konnte nicht hinzugefügt werden!");
	}
}

void traverseInorder(bst** root) {
	bst* rootPointer = *root;
	if ((*root) != NULL) {
		traverseInorder(&(rootPointer->left));
		printf("%d\n", rootPointer->value);
		traverseInorder(&(rootPointer->right));
	}
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

int main() {
	bst* root = NULL;
	addNode(&root, 20);
	addNode(&root, 10);
	addNode(&root, 5);
	addNode(&root, 30);
	addNode(&root, 15);
	addNode(&root, 25);
	traverseInorder(&root);
	deleteTree(&root);
	return 0;
}