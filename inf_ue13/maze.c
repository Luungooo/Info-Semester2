#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

/*
 * createRandomMaze allocates memory for a maze structure
 * containing the size of an edge of the maze as well as
 * a two-dimensional array featuring the layout of the maze
 * pathToWallRatio is an integer which defines the number of
 * paths in relation to the number of walls. Having more walls
 * than paths is not allowed. Positioning of the walls is random.
 */
maze* createRandomMaze(unsigned int size, unsigned int pathToWallRatio) {
    if (size < 2) {
        printf(
                "Invalid size entered. Minimum size is 2 (in order to create a 2x2 maze).\n");
        return 0;
    }
    if (pathToWallRatio == 0) {
        printf("Invalid Path-to-Wall ratio entered.\n");
        return 0;
    }
    maze* myMaze = (maze*) malloc(sizeof(maze));
    if (myMaze == NULL) {
        printf("Could not allocate memory for maze.\n");
        exit(1);
    }
    myMaze->size = size;
    myMaze->theMaze = (int**) malloc(size * sizeof(int*));
    if (myMaze->theMaze == NULL) {

        printf("Could not allocate memory for field of maze.\n");
        return 0;

    }
    for (int i = 0; i < size; i++) {
        myMaze->theMaze[i] = (int*) calloc(size, sizeof(int));
        if (myMaze->theMaze[i] == NULL) {
            printf("Could not allocate memory for field of maze.\n");
            return 0;
        }
    }
    int numberOfFields = myMaze->size * myMaze->size;
    int numberOfWalls = numberOfFields / (pathToWallRatio + 1);
    int fields[numberOfFields];
    int j;
    for (j = 0; j < numberOfFields; j++) {
        if (j < numberOfWalls) {
            fields[j] = 1;
        } else {
            fields[j] = 0;
        }
    }
    int tmp;
    for (int i = 0; i < 10000; i++) {
        for (int k = 0; k < numberOfFields; k++) {
            int myRand = rand();
            if (myRand < RAND_MAX / 2) {
                tmp = fields[k];
                fields[k] = fields[(k + k * i) % numberOfFields];
                fields[(k + k * i) % numberOfFields] = tmp;
            }
        }
    }
    for (int i = 0; i < myMaze->size; i++) {
        for (int j = 0; j < myMaze->size; j++) {
            myMaze->theMaze[i][j] = fields[i * myMaze->size + j];
        }
    }
    myMaze->theMaze[0][0] = 0;
    myMaze->theMaze[myMaze->size - 1][myMaze->size - 1] = 0;
    return myMaze;
}

/*
 * deleteRandomMaze frees the memory reserved by the maze structure
 */
void deleteRandomMaze(maze** myMaze) {
    if (myMaze == NULL) {
        printf("Invalid pointer given!\n");
        return;
    }
    if (*myMaze == NULL) {
        printf("Nothing to delete\n");
        return;
    }
    if ((*myMaze)->theMaze == NULL) {
        printf("No Maze to delete!\n");
    } else {
        for (int i = 0; i < (*myMaze)->size; i++) {
            free((*myMaze)->theMaze[i]);
        }
        free((*myMaze)->theMaze);
    }
    free((*myMaze));
    *myMaze = NULL;
}

/*
 * printMaze prints the map of the maze
 * For the solution, I use another encoding
 * to highlight the route taken:
 * in case, the algo goes right, I mark the
 * field visited by setting it to 4.
 * this will be printed out to >
 * for going down, I use 5, and printing it
 * as v as so forth...
 */
void printMaze(maze* myMaze) {
    int tmp;
    printf(" ");
    for (int i = 0; i < myMaze->size; i++) {
        printf("_");
    }
    printf("\n");
    for (int i = 0; i < myMaze->size; i++) {
        if (i == 0) {
            printf(">");
        } else {
            printf("|");
        }
        for (int j = 0; j < myMaze->size; j++) {
            tmp = myMaze->theMaze[i][j];
            if (tmp == 0) {
                printf(" ");
                //walls are encoded as 1
            } else if (tmp == 1) {
                printf("X");

                //going to the right is encoded as 4
            } else if (tmp == 4) {
                printf(">");

                //downwards as 5
            } else if (tmp == 5) {
                printf("v");

                //to the left as 6
            } else if (tmp == 6) {
                printf("<");

                //upwards as 7
            } else if (tmp == 7) {
                printf("^");

                //visited fields being a dead end are marked as a *
            } else {
                printf("*");
            }
        }
        if (i == myMaze->size - 1) {
            printf(">\n");
        } else {
            printf("|\n");
        }
    }
    printf(" ");
    for (int i = 0; i < myMaze->size; i++) {
        printf("_");
    }
    printf("\n");
}
