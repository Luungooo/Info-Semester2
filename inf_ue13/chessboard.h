#ifndef CHESSBOARD_H
#define CHESSBOARD_H

typedef struct cb {
    int** board;
    unsigned int size;
} cb;

int isValid(cb* myCB, unsigned int x, unsigned int y);

cb* initChessboard(unsigned int size);

void eraseQueensFromBoard(cb* myCB);

void freeMemoryFromBoard(cb** myCB);

void printChessboard(cb* myCB);

#endif //CHESSBOARD_H
