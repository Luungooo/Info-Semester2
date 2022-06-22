#include <stdio.h>
#include <stdlib.h>
#include "numArrays.h"
#include "sortingHelperStructures.h"

void mySort(int* myArray, unsigned long length) {
	while (!isSortedArray(myArray, length)) {
		for (unsigned long i = 0; i < length - 1; i++) {
				if (myArray[i] > myArray[i + 1]) {
					myArray[i] = myArray[i] ^ myArray[i + 1];
					myArray[i + 1] = myArray[i] ^ myArray[i + 1];
					myArray[i] = myArray[i] ^ myArray[i + 1];
				}
			}
	}
}


void quicksort(int* myArray, unsigned long length) {
	if (isSortedArray(myArray, length)) {
		return;
	}
	if (length <= 1) {
		return;
	}

	int p = myArray[length / 2 - 1];
	unsigned long i = 0;
	unsigned long j = length - 1;

	while (1) {
		while (myArray[i] < p) {
			i++;
		}
		while (myArray[j] > p) {
			j--;
		}
		if (i >= j) {
			break;
		}
		else {
			myArray[i] = myArray[i] ^ myArray[j];
			myArray[j] = myArray[i] ^ myArray[j];
			myArray[i] = myArray[i] ^ myArray[j];
			i++;
			j--;
		}
	}
	quicksort(myArray, j + 1);
	quicksort(myArray + j + 1, length - j - 1);
}



int main(void) {
	//you don't need to make any changes to the code below.
	//but feel free, if you like ...
	setvbuf(stdout, 0, _IONBF, 0);
	numArrays* myNA = initializeArrays(getUserInput());

	//If you look closely, we do some interesting stuff here:
	//We pass a function (our sorting algorithm) as an argument into
	//the function callSorter. If have a look in sortingHelperStructures.c
	//you will see, how the parameter list looks like
	callSorter(mySort, myNA, "mySort");
	callSorter(quicksort, myNA, "Quicksort");


	deleteNumArray(&myNA);
	return EXIT_SUCCESS;
}
