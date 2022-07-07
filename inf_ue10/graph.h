#ifndef GRAPH_H
#define GRAPH_H

typedef struct edge {
    struct node* toNode;
    unsigned int distance;
    struct edge* next;
} edge;

typedef struct node {
    char name;
    int visited;
    edge* edges;
    struct node* next;
} node;

typedef struct adjacencyMatrix {
    unsigned int** A;
    unsigned int numberOfNodes;
    char* names;
} adM;

#endif //GRAPH_H
