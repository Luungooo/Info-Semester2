#include <stdio.h>
#include <stdlib.h>
#include "numArrays.h"
#include "time.h"

void deleteNumArray(numArrays** nA) {
    if (nA == NULL) {
        return;
    }
    if (*nA == NULL) {
        return;
    }
    free((*nA)->inverseSortedArray);
    free((*nA)->presortedArray);
    free((*nA)->randomArray);
    free(*nA);
    *nA = NULL;
}

/*
 * initializeArrayContents() sets the values
 * of field randomArray to random values, the values
 * of field preSortedArray to an ascending sequence
 * starting at 0, and the values of inverseSortedSequence
 * to a descending sequence ending at 0.
 */
void initializeArrayContents(numArrays* nA) {
    if (nA == NULL) {
        printf("Empty structure given!\n");
        return;
    }
    if (nA->inverseSortedArray == NULL || nA->presortedArray == NULL || nA->randomArray == NULL) {
        printf("Arrays not correctly initialized!\n");
        return;
    }
    for (unsigned long i = 0; i < nA->numElements; i++) {
        nA->presortedArray[i] = i;
        nA->inverseSortedArray[nA->numElements - 1 - i] = i;
        nA->randomArray[i] = rand();
    }
}

/*
 * initializeArrays() reserves memory for a numArrays struct
 * Furthermore, the length of the arrays is set to numElements.
 * The arrays are not yet initialized. This happens, when initializeArrayContents
 * is called. This is done by the callSorter function
 */
numArrays* initializeArrays(unsigned long numElements) {
    numArrays* nA = (numArrays*) malloc(sizeof(numArrays));
    if (nA == NULL) {
        printf("Could not allocate memory!\n");
        exit(1);
    }
    nA->numElements = numElements;
    nA->randomArray = (int*) calloc(nA->numElements, sizeof(int));
    if (nA->randomArray == NULL) {
        printf("Could not allocate memory!\n");
        deleteNumArray(&nA);
        exit(1);
    }
    nA->presortedArray = (int*) calloc(nA->numElements, sizeof(int));
    if (nA->presortedArray == NULL) {
        printf("Could not allocate memory!\n");
        deleteNumArray(&nA);
        exit(1);
    }
    nA->inverseSortedArray = (int*) calloc(nA->numElements, sizeof(int));
    if (nA->inverseSortedArray == NULL) {
        printf("Could not allocate memory!\n");
        deleteNumArray(&nA);
        exit(1);
    }
    return nA;
}

/*
 * isSortedArray() checks, whether an array is sorted in
 * an ascending manner or not. If it is not sorted, a 0
 * is returned, else a 1.
 */
int isSortedArray(int* array, unsigned long length) {
    if (array == NULL) {
        printf("Empty array given!\n");
        return -1;
    }
    if (length == 1) {
        return 1;
    }
    for (unsigned long i = 0; i < (length - 1); i++) {
        if (array[i] > array[i + 1]) {
            return 0;
        }
    }
    return 1;
}

/*
 * printArrays() prints the contents of the arrays
 * of the numArrays struct on the command line
 */
void printArrays(numArrays* nA) {
    if (nA == NULL) {
        printf("Empty structure given!\n");
        return;
    }
    if (nA->inverseSortedArray == NULL || nA->presortedArray == NULL || nA->randomArray == NULL) {
        printf("Arrays not correctly initialized!\n");
        return;
    }
    printf("Content of Arrays within numArray struct is:\n");
    for (unsigned long i = 0; i < nA->numElements; i++) {
        printf("%12d\t%12d\t%12d\n", nA->randomArray[i], nA->presortedArray[i],
               nA->inverseSortedArray[i]);
    }
    printf("\n");
}

/*
 * isSorted() checks for the numArrays struct, whether the
 * thre arrays are sorted or not. The result is printed on
 * the command line. Furthermore, return value of 1 indicates
 * that all arrays are sorted in ascending manner. Else, a 0 is returned.
 */
int isSorted(numArrays* nA) {
    if (nA == NULL) {
        printf("Empty structure given!\n");
        return -1;
    }
    if (nA->inverseSortedArray == NULL || nA->presortedArray == NULL || nA->randomArray == NULL) {
        printf("Arrays not correctly initialized!\n");
        return -1;
    }
    int r = isSortedArray(nA->randomArray, nA->numElements);
    (r == 1) ?
    printf("Random Array is sorted.\n") :
    printf("Random Array is NOT SORTED.\n");
    int p = isSortedArray(nA->presortedArray, nA->numElements);
    (p == 1) ?
    printf("Presorted Array is sorted.\n") :
    printf("Presorted Array is NOT SORTED (any more - Yikes!).\n");
    int i = isSortedArray(nA->inverseSortedArray, nA->numElements);
    (i == 1) ?
    printf("Inverse presorted Array is sorted.\n") :
    printf("Inverse presorted Array is NOT SORTED.\n");
    (r && p && i) ?
    printf("Well done.\n\n\n") :
    printf("WROOOOOOOOOONG! Back to the drawing board...\n\n\n");
    printf("\n");
    return (r && p && i);
}

/*
 * callSorterForArray uses the sorting algorithm passed in the first parameter and sorts
 * the array passed as second parameter. Since for every list and every sorting algorithm
 * we measure the start and end time, this could lead to a lot of copied&pasted code.
 * We know that the advantage of functions is that they may perform repeating tasks with
 * different inputs. The repeating stuff here is: starting the time, invoking a sorting algo
 * with a certain array, stopping the time, measuring the time. The different input is the
 * actual sorting algorithm and the actual array to be sorted.
 */
void callSorterForArray(void(* f)(int*, long unsigned int), int* arrayToSort, long unsigned int numElements, char* name,
                        char* arrayStructure) {
    //the following two lines initialize variables for
    //performance benchmarking
    clock_t startTime, endTime;
    double computationTime;
    startTime = clock();
    (*f)(arrayToSort, numElements);
    endTime = clock();
    computationTime = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
    printf("%s - %s values: %.2f seconds.\n", name, arrayStructure, computationTime);
}

/*
 * We want to test several sorting algorithms. For each algorithm, we will sort the
 * random, the presorted, and the inverse sorted list. Instead of using copy&paste
 * for each and every algorithm and list to be sorted, we just pass the current
 * sorting algorithm to callSorter. The first parameter of callSorter, thus, is a function.
 * We take this even a step further and pass this function further to another function,
 * callSorterForArray.
 */
void callSorter(void(* f)(int*, long unsigned int), numArrays* nA, char* name) {
    initializeArrayContents(nA);
    printf(
            "Do you want to print the array contents before and after sorting by %s? (not recommended for larger lists (>10)) [y/n]?\n",
            name);
    char print = getchar();
    scanf("%*c");
    (print == 'y' || print == 'Y') ? printArrays(nA) : 0;
    printf("Now starting sorting by %s.\n", name);
    callSorterForArray(f, nA->randomArray, nA->numElements, name, "random");
    callSorterForArray(f, nA->presortedArray, nA->numElements, name, "presorted");
    callSorterForArray(f, nA->inverseSortedArray, nA->numElements, name, "inverse sorted");
    (print == 'y' || print == 'Y') ? printArrays(nA) : 0;
    isSorted(nA);
}

/*
 * getUserInputs asks the user to define the length of the lists to be sorted
 */
int getUserInput() {
    int LENGTH_OF_LISTS;
    printf(
            "Please enter length of lists (Start with small numbers (5-10), the fun begins at lengths > 100000): \n");
    scanf("%d%*c", &LENGTH_OF_LISTS);
    if (LENGTH_OF_LISTS < 1) {
        printf("Invalid length given! Aborting...\n");
        return -1;
    }
    return LENGTH_OF_LISTS;

}
