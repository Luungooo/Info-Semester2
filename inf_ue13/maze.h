#ifndef MAZE_H
#define MAZE_H

typedef struct maze {
    unsigned int size;
    int** theMaze;
} maze;


maze* createRandomMaze(unsigned int size, unsigned int pathToWallRatio);

void deleteRandomMaze(maze** myMaze);

void printMaze(maze* myMaze);

#endif //MAZE_H
