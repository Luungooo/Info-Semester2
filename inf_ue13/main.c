#include <stdio.h>
#include <stdlib.h>
#include "chessboard.h"
#include "maze.h"

/*
 * The solver checks, whether all queens have been placed.
 * In this case, it returns 1 to indicate success.
 * In order to add queen number n, we go to the n-th line
 * of the chess board and try to find the first spot that
 * is valid. We do so by invoking the isValid() function
 * in order to check, whether me may place a queen at a
 * certain spot. In case we may set the queen there, we
 * invoke the solver for the next queen and see, whether
 * this function call yields a successful result (i.e.
 * it returns 1). If this is not the case, we move the
 * current queen to the next possible spot in this line
 * If we have tried all positions in this line, we return
 * 0. This is the sign for the caller, that there is no valid
 * position.
 */
int solver(cb* myCB, unsigned int queen) {
    //start with the successful return, i.e.
    //the "Abbruchbedingung"

    //follow the instructions above the function...







}

/*
 * In this function, we invoke the solver() in order to
 * add the first queen to the chess board. The function
 * solves the problem by recursively calling itself.
 * After having found a solution, we print the chess board.
 */
void solveEightQueensPuzzleViaBacktracking(cb* myCB) {
    if (myCB == NULL) {
        printf("Invalid board!\n");
        return;
    }
    //at first, delete previous solutions
    eraseQueensFromBoard(myCB);

    int result = solver(myCB, 0);
    result == 1 ?
    printf("Valid Solution found! :)\n") :
    printf("No solution found :(\n");
    //now print the solution
    printChessboard(myCB);
}


/*
 * the actual solver for the maze. For each call of this
 * function, we check, whether we have found the exit. Return 1
 * indicates that we have found the exit, return 0 indicates
 * we didn't.
 */
int solveMaze(maze* myMaze, unsigned int x, unsigned int y) {
    //in case we have found the exit, we return with ...?



    //in case a hit a border of the maze, we return with ...?



    //in case we hit a wall, we return with ...?



    //in case we already have been on this field, we return with ...?



    //ok in case, we are inside the borders of the field, we are
    //not standing on a wall and we have not visited this field yet,
    //we mark it as visited



    //now we see, if calling the solver on the next field to the right
    //returns the solution. (How do we check whether the function we have
    //called has found a solution?) If not, we try the field below us. If thats
    //also not successful, we try the field to the right or at least,
    //the field above us

















    //in case we checked for every direction, but did not find the exit,
    //what do we return?


}

/*
 * findWayThroughMaze calls the actual solver,
 * function solveMaze(...). In case a solution
 * is found, it is printed to the console.
 * You do not need to make any changes here.
 */
void findWayThroughMaze(maze* myMaze) {
    //we start at the topmost row to the left
    int x = 0;
    int y = 0;
    if (solveMaze(myMaze, x, y) == 0) {
        printf("No way to exit found :( \n");
    } else {
        printf("Found a way to the exit :) \n");
    }
    printMaze(myMaze);
}

/*
 * Here we initialize our board and invoke the function
 * to solve the queens problem. You do not need to make
 * any changes.
 */
int main(void) {

    //n queens problem
    unsigned int SIZE_OF_BOARD;
    printf("Please enter size of chessboard: \n");
    scanf("%u%*c", &SIZE_OF_BOARD);
    cb* myCB = initChessboard(SIZE_OF_BOARD);
    solveEightQueensPuzzleViaBacktracking(myCB);
    freeMemoryFromBoard(&myCB);

    printf("\n\n\n");

    //maze
    unsigned int SIZE_OF_MAZE;
    unsigned int PATH_TO_WALL;
    printf("Please enter size of maze: \n");
    scanf("%u%*c", &SIZE_OF_MAZE);
    printf("Please enter path-to-wall ratio (>= 1): \n");
    scanf("%u%*c", &PATH_TO_WALL);
    maze* myMaze = createRandomMaze(SIZE_OF_MAZE, PATH_TO_WALL);
    findWayThroughMaze(myMaze);
    deleteRandomMaze(&myMaze);
    return EXIT_SUCCESS;
}
