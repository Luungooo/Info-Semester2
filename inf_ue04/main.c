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

void printList(myList* a) {
    if (a == NULL) {
        printf("Uebergebene Liste ist leer!\n");
        return;
    }
    printf("%d\n", a->value);
    if (a->next != NULL) {
        printList(a->next);
    }
}

/* void removeFromTail(myList* current) {
    if (current->next == NULL) {
        free(current);
        return;
    }
    while (current->next->next != NULL) {
        current = current->next;
    }
    free(current->next);
    current->next = NULL;
}*/

void removeFromTail(myList** ptrToHead) {
    if (*ptrToHead == NULL) {
        return;
    }
    myList* current = *ptrToHead;
    if (current->next == NULL) {
        free(current);
        *ptrToHead = NULL;
        return;
    }
    while (current->next->next != NULL) {
        current = current->next;
    }
    free(current->next);
    current->next = NULL;
}

int main() {
    myList* head = NULL;
    head = (myList*) malloc(sizeof(myList));
    if (head == NULL) {
        printf("Konnte Element nicht hinzuf�gen!\n");
        return EXIT_FAILURE;
    }
    head->value = 1;
    head->next = NULL;
    if (addToTail(head, 23) == 1) {
        printf("Konnte Element nicht hinzufuegen!\n");
        return EXIT_FAILURE;
    }
    printList(head);
    removeFromTail(&head);
    printList(head);
    removeFromTail(&head);
    printList(head);
    return 0;
}
