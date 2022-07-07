#include <stdio.h>
#include <stdlib.h>
#include "chessboard.h"

/*
 * isValid() takes the chessboard and a [x,y] position
 * It checks, whether a queen may be placed at [x,y] without
 * interfering with one of the other queens present on the board
 * A valid position is indicated by return value 1.
 */
int isValid(cb* myCB, unsigned int x, unsigned int y) {
    if (myCB == NULL) {
        printf("Invalid board!\n");
        return -1;
    }
    if (x >= myCB->size || y >= myCB->size) {
        printf("Invalid position!\n");
        return -1;
    }
    //checkHorizontally
    for (int i = 0; i < myCB->size; i++) {
        if (myCB->board[x][i] != 0) {
            return 0;
        }
    }
    //checkVertically
    for (int i = 0; i < myCB->size; i++) {
        if (myCB->board[i][y] != 0) {
            return 0;
        }
    }
    //check diagonal 1
    int i = x;
    int j = y;
    while (i >= 0 && j >= 0) {
        if (myCB->board[i][j] != 0) {
            return 0;
        }
        i--;
        j--;
    }
    i = x;
    j = y;
    while (i < myCB->size && j < myCB->size) {
        if (myCB->board[i][j] != 0) {
            return 0;
        }
        i++;
        j++;
    }
    //check diagonal 2
    i = x;
    j = y;
    while (i >= 0 && j < myCB->size) {
        if (myCB->board[i][j] != 0) {
            return 0;
        }
        i--;
        j++;
    }
    i = x;
    j = y;
    while (i < myCB->size && j >= 0) {
        if (myCB->board[i][j] != 0) {
            return 0;
        }
        i++;
        j--;
    }
    return 1;
}

cb* initChessboard(unsigned int size) {
    if (size == 0) {
        printf("Invalid size given! Must be >0!\n");
        exit(1);
    }
    cb* myCB = (cb*) malloc(sizeof(cb));
    if (myCB == NULL) {
        printf("Could not reserve memory!\n");
        exit(1);
    }
    myCB->size = size;
    //Here we use calloc, to initialize the pointer with 0 (NULL)
    //in doing so, we make sure that we may correctly free the memory
    //in case one of allocations of a line of the board fails
    myCB->board = (int**) calloc(myCB->size, sizeof(int*));
    if (myCB->board == NULL) {
        printf("Could not reserve memory!\n");
        freeMemoryFromBoard(&myCB);
        exit(1);
    }
    for (int i = 0; i < myCB->size; i++) {
        myCB->board[i] = (int*) calloc(myCB->size, sizeof(int));
        if (myCB->board[i] == NULL) {
            printf("Could not reserve memory!\n");
            exit(1);
        }
    }
    return myCB;
}

void eraseQueensFromBoard(cb* myCB) {
    if (myCB == NULL) {
        printf("Invalid board!\n");
        return;
    }
    for (int i = 0; i < myCB->size; i++) {
        for (int j = 0; j < myCB->size; j++) {
            myCB->board[i][j] = 0;
        }
    }
}

void freeMemoryFromBoard(cb** myCB) {
    if (myCB == NULL) {
        printf("Invalid pointer!\n");
        return;
    }
    if (*myCB == NULL) {
        printf("Nothing to free!\n");
        return;
    }
    if ((*myCB)->board == NULL) {
        printf("Invalid board!\n");
    } else {
        for (int i = 0; i < (*myCB)->size; i++) {
            free((*myCB)->board[i]);
        }
        free((*myCB)->board);
    }
    free((*myCB));
    *myCB = NULL;
}

void printChessboard(cb* myCB) {
    if (myCB == NULL) {
        printf("Invalid board!\n");
        return;
    }
    printf("\t");
    for (unsigned int i = 65; i < 65 + myCB->size; i++) {
        printf("%c\t", i);
    }
    printf("\n\n");
    for (unsigned int i = 0; i < myCB->size; i++) {
        printf("%d\t", myCB->size - i);
        for (unsigned int j = 0; j < myCB->size; j++) {
            printf("%d\t", myCB->board[myCB->size - 1 - i][j]);
        }
        printf("\n\n");
    }
    printf("\t");
    for (int i = 65; i < 65 + myCB->size; i++) {
        printf("%c\t", i);
    }
    printf("\n");
}
