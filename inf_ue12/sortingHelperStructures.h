#ifndef SORTINGHELPERSTRUCTURES_H
#define SORTINGHELPERSTRUCTURES_H

void deleteNumArray(numArrays** nA);

void initializeArrayContents(numArrays* nA);

numArrays* initializeArrays(unsigned long numElements);

int isSortedArray(int* array, unsigned long length);

int isSorted(numArrays* nA);

void printArrays(numArrays* nA);

void callSorterForArray(void(* f)(int*, long unsigned int), int* arrayToSort, long unsigned int numElements, char* name,
                        char* arrayStructure);

void callSorter(void(* f)(int*, long unsigned int), numArrays* nA, char* name);

int getUserInput();

#endif //SORTINGHELPERSTRUCTURES_H
