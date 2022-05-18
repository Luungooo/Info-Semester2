#include <stdio.h>

int isBigger(int arr1[], int arr2[], int length1, int length2) {
    int sumArr1 = 0;
    int sumArr2 = 0;

    for (int i = 0; i < length1; i++) {
        sumArr1 += arr1[i];
    }
    for (int i = 0; i < length2; i++) {
        sumArr2 += arr2[i];
    }
    return sumArr1 >= sumArr2;
}

int main() {
    int myArr1[5] = { 1, 2, 3, 4, 6 };
    int sizeArr1 = sizeof myArr1 / sizeof myArr1[0];

    int myArr2[5] = { 1, 2, 3, 4, 5 };
    int sizeArr2 = sizeof myArr2 / sizeof myArr2[0];

    int myArr3[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int sizeArr3 = sizeof myArr3 / sizeof myArr3[0];

    int result = isBigger(myArr1, myArr3, sizeArr1, sizeArr3);
    printf("%d", result);

    return 0;
}
