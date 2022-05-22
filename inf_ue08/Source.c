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

int find(bst* root, int value) {
	if (root == NULL) {
		return -1;
	}
	if (root->value == value) {
		return 1;
	}
	if (root->value < value) {
		return find(root->right, value);
	}
	else {
		return find(root->left, value);
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
	int result = find(root, 15);
	deleteTree(&root);
	return 0;
}