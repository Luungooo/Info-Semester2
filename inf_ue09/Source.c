#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

heap* createMemoryForHeap(heap** myHeapPtr, int depth) {
	int n = (1 << depth) - 1;
	heap* newHeap = (heap*)malloc(sizeof(heap));
	if (newHeap == NULL) { exit(1); }
	newHeap->heapArray = (unsigned int*)calloc(n, sizeof(unsigned int));
	if (newHeap->heapArray == NULL) { exit(1); }
	newHeap->size = n;
	return newHeap;
}

void deleteHeap(heap** myHeapPtr) {
	free((*myHeapPtr)->heapArray);
	free(*myHeapPtr);
}

void addToHeap(heap* myHeap, unsigned int node) {
	if (node == 0) {
		return;
	}
	unsigned int* heapArray = myHeap->heapArray;
	for (int i = 0; i < myHeap->size; i++) {
		if (*(heapArray + i) == 0) {
			*(heapArray + i) = node;
			while (*(heapArray + i) > *(heapArray + ((i - 1) / 2)) && i != 0) {
				unsigned int tmp = *(heapArray + i);
				*(heapArray + i) = *(heapArray + ((i - 1) / 2));
				*(heapArray + ((i - 1) / 2)) = tmp;
				i = (i - 1) / 2;
			}
			return;
		}
	}
}

void printHeap(heap* myHeap) {
	for (unsigned int i = 0; i < myHeap->size; i++) {
		if (*(myHeap->heapArray + i) == 0) {
			return;
		}
		printf("%d\n", *(myHeap->heapArray + i));
	}
}

int main() {
	heap* myHeap = NULL;
	myHeap = createMemoryForHeap(&myHeap, 4);
	addToHeap(myHeap, 8);
	addToHeap(myHeap, 4);
	addToHeap(myHeap, 9);
	addToHeap(myHeap, 3);
	addToHeap(myHeap, 5);
	addToHeap(myHeap, 1);
	addToHeap(myHeap, 2);
	addToHeap(myHeap, 6);
	addToHeap(myHeap, 10);
	printHeap(myHeap);
	deleteHeap(&myHeap);
	return 0;
}