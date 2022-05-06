#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ints = (int *) malloc(256 * sizeof(int));
    if (ints == NULL) {
        exit(1);
    }
    for (int i = 0; i < 256; i++) {
        ints[i] = i;
    }
    double *doubles = (double *) malloc(1048576);
    if (doubles == NULL) {
        exit(1);
    }
    int numberOfDoubles = 1048576 / sizeof(double);
    printf("%d", numberOfDoubles);
    int counter = 0;
    while(1) {
        int* integers = (int* ) malloc(1073741824);
        if (integers == NULL) {
            break;
        }
        for (int i = 0; i < 268435456; i++) {
            integers[i] = i;
        }
        counter += 1;
    }
    free(ints);
    ints = NULL;
    free(doubles);
    doubles = NULL;
    return 0;
}
