#include <stdio.h>
#include "myStruct.h"
#include "myList.h"

void printList(myList* a) {
    printf("%d\n", a->value);
    if (a->next != NULL) {
        printList(a->next);
    }
}

int main() {
    myStruct a;
    myStruct b;
    a.myInteger = 4;
    a.myFloat = 4.75;
    b.myInteger = 2;
    b.myFloat = 0.524;

    myStruct* c = NULL;
    c = &b;
    c->myInteger = 7;
    c->myFloat = 5.32;

    myList x;
    x.value = 2;
    x.next = NULL;

    myList y;
    y.value = 1;
    y.next = &x;

    myList z;
    z.value = 9;
    z.next = &y;

    printList(&z);
}
