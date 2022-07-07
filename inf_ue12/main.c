#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "numArrays.h"
#include "sortingHelperStructures.h"

void merge(int* a, unsigned long length_a, int* b, unsigned long length_b);

void mySort(int* myArray, unsigned long length) {
    unsigned long j = 1;

    while (!isSortedArray(myArray, length)) {
        for (unsigned long i = 0; i < length - j; i++) {
            if (myArray[i] > myArray[i + 1]) {
                myArray[i] = myArray[i] ^ myArray[i + 1];
                myArray[i + 1] = myArray[i] ^ myArray[i + 1];
                myArray[i] = myArray[i] ^ myArray[i + 1];
            }
        }
        j++;
    }
}

void shuffle(int* myArray, unsigned long length) {
    unsigned long r;
    srand(time(0));

    for (unsigned long i = 0; i < length; i++) {
        r = rand() % length;
        if (r != i) {
            myArray[i] = myArray[i] ^ myArray[r];
            myArray[r] = myArray[i] ^ myArray[r];
            myArray[i] = myArray[i] ^ myArray[r];
        }
    }
}

void bogoSort(int* myArray, unsigned long length) {
    while (!isSortedArray(myArray, length)) {
        shuffle(myArray, length);
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
        } else {
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

void insertionSort(int* myArray, unsigned long length) {
    int tmp;
    unsigned long j;

    for (unsigned long i = 1; i < length; i++) {
        tmp = myArray[i];
        j = i;
        while (j > 0 && myArray[j - 1] > tmp) {
            myArray[j] = myArray[j - 1];
            j--;
        }
        myArray[j] = tmp;
    }
}

void mergeSort(int* myArray, unsigned long length) {
    if (myArray == NULL) {
        return;
    }
    if (length < 2) {
        return;
    }
    unsigned long j = length / 2;

    mergeSort(myArray, j);
    mergeSort(&myArray[j], length - j);
    merge(myArray, j, &myArray[j], length - j);
}

void merge(int* a, unsigned long length_a, int* b, unsigned long length_b) {
    unsigned long i_a = 0;
    unsigned long i_b = 0;
    unsigned long i_tmp = 0;

    int* tmp = (int*) malloc((length_a + length_b) * sizeof(int));
    if (tmp == NULL) {
        return;
    }

    while (i_a < length_a && i_b < length_b) {
        if (a[i_a] < b[i_b]) {
            tmp[i_tmp] = a[i_a];
            i_a++;
        } else {
            tmp[i_tmp] = b[i_b];
            i_b++;
        }
        i_tmp++;
    }
    while (i_a < length_a) {
        tmp[i_tmp] = a[i_a];
        i_a++;
        i_tmp++;
    }
    while (i_b < length_b) {
        tmp[i_tmp] = b[i_b];
        i_b++;
        i_tmp++;
    }

    for (unsigned long i = 0; i < length_a; i++) {
        a[i] = tmp[i];
    }
    for (unsigned long i = 0; i < length_b; i++) {
        b[i] = tmp[i + length_a];
    }
}

int main(void) {
    //you don't need to make any changes to the code below.
    //but feel free, if you like ...
    srand(time(0));
    numArrays* myNA = initializeArrays(getUserInput());

    //If you look closely, we do some interesting stuff here:
    //We pass a function (our sorting algorithm) as an argument into
    //the function callSorter. If have a look in sortingHelperStructures.c
    //you will see, how the parameter list looks like
    //callSorter(mySort, myNA, "mySort");
    //callSorter(insertionSort, myNA, "Insertionsort");
    callSorter(mergeSort, myNA, "Mergesort");
    callSorter(quicksort, myNA, "Quicksort");

    deleteNumArray(&myNA);
    return EXIT_SUCCESS;
}
