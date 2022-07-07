#include <stdio.h>
#include <stdlib.h>
#include "myList.h"

int addToTail(myList* current, int value) {
    if (current == NULL) {
        return 1;
    }
    myList* newElement = (myList*) malloc(sizeof(myList));
    if (newElement == NULL) {
        return 1;
    }
    newElement->value = value;
    newElement->next = NULL;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newElement;
    return 0;
}

int printList(myList* a) {
    if (a == NULL) {
        printf("Uebergebene Liste ist leer!\n");
        return 0;
    }
    while (a != NULL) {
        printf("%d\n", a->value);
        a = a->next;
    }
    return 1;
}

int removeFromTail(myList** ptrToHead) {
    if (ptrToHead == NULL) {
        return 0;
    }
    if (*ptrToHead == NULL) {
        return 0;
    }
    myList* current = *ptrToHead;
    if (current->next == NULL) {
        free(current);
        *ptrToHead = NULL;
        return 1;
    }
    while (current->next->next != NULL) {
        current = current->next;
    }
    free(current->next);
    current->next = NULL;
    return 1;
}

int deleteList(myList** ptrToHead) {
    if (ptrToHead == NULL) {
        return 0;
    }
    if (*ptrToHead == NULL) {
        return 0;
    }
    while (removeFromTail(ptrToHead)) {}
    return 1;
}

int addSorted(myList** ptrToHead, int value) {
    myList* newElement = (myList*) malloc(sizeof(myList));
    if (newElement == NULL) {
        return 0;
    }
    newElement->value = value;
    newElement->next = NULL;
    myList* current = *ptrToHead;
    if (current == NULL) {
        *ptrToHead = newElement;
        return 1;
    }
    if (current->value > value) {
        newElement->next = current;
        *ptrToHead = newElement;
        return 1;
    }
    while (current->next != NULL && current->next->value < value) {
        current = current->next;
    }
    newElement->next = current->next;
    current->next = newElement;
    return 1;
}

int main() {
    myList* head = NULL;
    head = (myList*) malloc(sizeof(myList));
    if (head == NULL) {
        printf("Konnte Element nicht hinzufuegen!\n");
        return EXIT_FAILURE;
    }
    head->value = 1;
    head->next = NULL;
    if (addToTail(head, 23)) {
        printf("Konnte Element nicht hinzufuegen!\n");
        return EXIT_FAILURE;
    }
    if (addToTail(head, 56)) {
        printf("Konnte Element nicht hinzufuegen!\n");
        return EXIT_FAILURE;
    }
    printList(head);
    deleteList(&head);
    printList(head);

    myList* headOfSortedList = NULL;
    if (!addSorted(&headOfSortedList, 5)) {
        printf("Konnte Element nicht hinzufuegen!\n");
        return EXIT_FAILURE;
    }
    printList(headOfSortedList);
    printf("\n");
    if (!addSorted(&headOfSortedList, 3)) {
        printf("Konnte Element nicht hinzufuegen!\n");
        return EXIT_FAILURE;
    }
    printList(headOfSortedList);
    printf("\n");
    if (!addSorted(&headOfSortedList, 53)) {
        printf("Konnte Element nicht hinzufuegen!\n");
        return EXIT_FAILURE;
    }
    printList(headOfSortedList);
    printf("\n");
    if (!addSorted(&headOfSortedList, 1)) {
        printf("Konnte Element nicht hinzufuegen!\n");
        return EXIT_FAILURE;
    }
    printList(headOfSortedList);
    printf("\n");
    if (!addSorted(&headOfSortedList, 66)) {
        printf("Konnte Element nicht hinzufuegen!\n");
        return EXIT_FAILURE;
    }
    printList(headOfSortedList);
    printf("\n");
    if (!addSorted(&headOfSortedList, 12)) {
        printf("Konnte Element nicht hinzufuegen!\n");
        return EXIT_FAILURE;
    }
    printList(headOfSortedList);
    printf("\n");
    deleteList(&headOfSortedList);
    return 0;
}
