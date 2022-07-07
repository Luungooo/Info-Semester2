#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void addNode(node** nodeList, char Name) {
    if (nodeList == NULL) {
        printf("Invalid pointer given!\n");
        return;
    }
    //if the node list is empty or we have reached the end of the list,
    //we append the new element and leave the function
    if (*nodeList == NULL) {
        node* newNode = (node*) malloc(sizeof(node));
        if (newNode == NULL) {
            printf("Could not create node!");
            return;
        }
        newNode->edges = NULL;
        newNode->name = Name;
        newNode->visited = 0;
        newNode->next = NULL;
        *nodeList = newNode;
        return;
    }
    //check whether a node with name Name already exists
    if ((*nodeList)->name != Name) {
        //this is a recursive method to cycle through the node list
        //we might as well solve it iteratively using a pointer pointing
        //to the current element.
        addNode(&((*nodeList)->next), Name);
    } else {
        printf("Node %c already exists!\n", Name);
        return;
    }
}

/*
 * addEdgeUnidirectional adds an edge from start nameStartNode to
 * nameEndNode with distance distance.
 */
void addEdgeUnidirectional(node** nodeList, char nameStartNode,
                           char nameEndNode, unsigned int distance) {
    /* when adding a new edge, we need to make sure a few things:
     * - we need to check whether the start node exists
     * - we need to make sure that the end node exists
     * - we want to make sure that there isn't another edge
     *   from start node to end node yet (this isn't necessarily
     *   forbidden as you know from the lecture. However,
     *   we want to keep things easy within this exercise)
     *
    */


    if (nodeList == NULL) {
        printf("Invalid pointer given!\n");
        return;
    }
    node* current = *nodeList;
    node* startNode = NULL;
    node* endNode = NULL;
    while (1) {
        if (current == NULL) {
            return;
        }
        if (current->name == nameStartNode) {
            startNode = current;
            break;
        }
        current = current->next;
    }
    current = *nodeList;
    while (1) {
        if (current == NULL) {
            return;
        }
        if (current->name == nameEndNode) {
            endNode = current;
            break;
        }
        current = current->next;
    }
    if (startNode->edges != NULL) {
        edge* currentEdge = startNode->edges;
        while (currentEdge != NULL) {
            if (currentEdge->toNode->name == endNode->name) {
                return;
            }
            currentEdge = currentEdge->next;
        }
    }
    edge* newEdge = (edge*) malloc(sizeof(edge));
    if (newEdge == NULL) {
        return;
    }
    newEdge->toNode = endNode;
    newEdge->distance = distance;
    newEdge->next = startNode->edges;
    startNode->edges = newEdge;


    return;


}

/*
 * Adding a bidirectional edge is facilitated by calling
 * addEdgeUnidirectional twice (once for each direction)
 */
void addEdge(node** nodeList, char nameStartNode, char nameEndNode, unsigned int distance) {
    addEdgeUnidirectional(nodeList, nameStartNode, nameEndNode, distance);
    addEdgeUnidirectional(nodeList, nameEndNode, nameStartNode, distance);
}

void printGraph(node* nodeList) {
    if (nodeList == NULL) {
        return;
    }
    printf("%c\t", nodeList->name);
    edge* current = nodeList->edges;
    while (current != NULL) {
        printf("-- %c|%d\t", current->toNode->name, current->distance);
        current = current->next;
    }
    printf("\n");
    printGraph(nodeList->next);
}

/*
 * This function is just the full traversal of the graph
 * by the depth-first search algorithm
 */
void depthSearch(node* nodeList, char startNode) {

    if (nodeList == NULL) {
        printf("Invalid pointer given!\n");
        return;
    }
    node* current = nodeList;
    node* node = NULL;
    while (1) {
        if (current == NULL) {
            return;
        }
        if (current->name == startNode) {
            node = current;
            break;
        }
        current = current->next;
    }
    node->visited = 1;
    edge* currentEdge = node->edges;
    while (currentEdge != NULL) {
        if (!(currentEdge->toNode->visited)) {
            depthSearch(nodeList, currentEdge->toNode->name);
        }
        currentEdge = currentEdge->next;
    }


}

/* findByDepthSearch detects, whether node candidate can
 * be reached by node startNode by exploiting the depth-first search algorithm
 */
int findByDepthSearch(node* nodeList, char startNode, char candidate) {

    if (nodeList == NULL) {
        printf("Invalid pointer given!\n");
        return 0;
    }
    node* current = nodeList;
    node* node = NULL;
    while (1) {
        if (current == NULL) {
            return 0;
        }
        if (current->name == startNode) {
            node = current;
            break;
        }
        current = current->next;
    }
    node->visited = 1;
    if (node->name == candidate) {
        return 1;
    } else {
        edge* currentEdge = node->edges;
        while (currentEdge != NULL) {
            if (!(currentEdge->toNode->visited)) {
                if (findByDepthSearch(nodeList, currentEdge->toNode->name, candidate)) {
                    return 1;
                }
            }
            currentEdge = currentEdge->next;
        }
    }


    return 0;
}

/*
 * printVisitedNodes prints out all nodes that are marked
 * as visited
 */
void printVisitedNodes(node* nodeList) {
    if (nodeList != NULL) {
        if (nodeList->visited == 1) {
            printf("%c\t", nodeList->name);
        }
        printVisitedNodes(nodeList->next);
    }
}

/*
 * resetVisitedNodes resets the visited mark for all nodes
 */
void resetVisitedNodes(node* nodeList) {
    if (nodeList != NULL) {
        nodeList->visited = 0;
        resetVisitedNodes(nodeList->next);
    }
}

/*
 * freeAdjacencyMatrix frees the memory from the adjacency matrix
 */
void freeAdjacencyMatrix(adM** myAdM) {
    if (*myAdM != NULL) {
        free((*myAdM)->names);
        if ((*myAdM)->A != NULL) {
            for (unsigned int i = 0; i < (*myAdM)->numberOfNodes; i++) {
                free((*myAdM)->A[i]);
            }
            free((*myAdM)->A);
        }
        free((*myAdM));
        *myAdM = NULL;
    }
}

/*
 * given a graph structured as a list of nodes, createAdjacencyMatrix
 * builds an adjacency matrix representation of the graph
 */
adM* createAdjacencyMatrix(node* nodeList) {
    if (nodeList == NULL) {
        printf("Invalid pointer given!\n");
        return 0;
    }
    unsigned int numberOfNodes = 0;
    node* current = nodeList;
    while (current != NULL) {
        numberOfNodes++;
        current = current->next;
    }
    adM* newAdjacencyMatrix = (adM*) malloc(sizeof(adM));
    newAdjacencyMatrix->numberOfNodes = numberOfNodes;
    newAdjacencyMatrix->A = (unsigned int**) malloc(numberOfNodes * sizeof(unsigned int*));
    for (unsigned int i = 0; i < numberOfNodes; i++) {
        newAdjacencyMatrix->A[i] = (unsigned int*) calloc(numberOfNodes, sizeof(unsigned int));
    }
    newAdjacencyMatrix->names = (char*) malloc(numberOfNodes * sizeof(char));
    current = nodeList;
    int i = 0;
    int j = 0;
    edge* currentEdge;
    node* currentNode;
    while (current != NULL) {
        newAdjacencyMatrix->names[i] = current->name;
        currentEdge = current->edges;
        if (currentEdge != NULL) {
            while (currentEdge != NULL) {
                j = 0;
                currentNode = nodeList;
                while (1) {
                    if (currentEdge->toNode->name == currentNode->name) {
                        break;
                    } else {
                        j++;
                        currentNode = currentNode->next;
                    }
                }
                newAdjacencyMatrix->A[i][j] = currentEdge->distance;
                currentEdge = currentEdge->next;
            }
        }
        current = current->next;
        i++;
    }
    return newAdjacencyMatrix;
}

/*
 * printAdjacencyMatrix prints the contents of the AdjacencyMatrix
 */
void printAdjacencyMatrix(adM* myAdM) {
    if (myAdM == NULL) {
        printf("No Adjacency Matrix given!\n");
        return;
    }
    if (myAdM->A == NULL) {
        printf("Empty Matrix given!\n");
        return;
    }

    printf("\t");
    for (unsigned int i = 0; i < myAdM->numberOfNodes; i++) {
        printf("%c\t", myAdM->names[i]);
    }
    printf("\n");
    for (unsigned int i = 0; i < myAdM->numberOfNodes; i++) {
        printf("%c\t", myAdM->names[i]);
        for (unsigned int j = 0; j < myAdM->numberOfNodes; j++) {
            printf("%d\t", myAdM->A[i][j]);
        }
        printf("\n");
    }
}

/*
 * freeEdgeList is a helper function, which frees the memory
 * for a edge list of a node. It is called by freeGraph
 */
void freeEdgeList(edge* edgeList) {
    if (edgeList != NULL) {
        freeEdgeList(edgeList->next);
        free(edgeList);
    }
}

/*
 * freeGraph frees the memory allocated for the graph, i.e. for the
 * nodes as well as their corresponding edges
 */
void freeGraph(node** nodeList) {
    if (nodeList == NULL) {
        printf("Invalid pointer given!\n");
        return;
    }
    if (*nodeList != NULL) {
        freeGraph(&((*nodeList)->next));
        freeEdgeList((*nodeList)->edges);
        *nodeList = NULL;
    }
}

int main(void) {
    node* graph = NULL;
    addNode(&graph, 'a');
    addNode(&graph, 'b');
    addNode(&graph, 'c');
    addNode(&graph, 'd');
    addNode(&graph, 'e');
    addNode(&graph, 'f');
    addNode(&graph, 'g');
    addNode(&graph, 'h');
    addNode(&graph, 'i');
    addNode(&graph, 'j');
    addNode(&graph, 'k');
//check whether we handle double creation of nodes:
    addNode(&graph, 'k');

    addEdge(&graph, 'a', 'b', 5);
    addEdge(&graph, 'b', 'c', 1);
    addEdge(&graph, 'c', 'd', 3);
    addEdge(&graph, 'c', 'h', 2);
    addEdge(&graph, 'c', 'i', 3);
    addEdge(&graph, 'f', 'e', 6);
    addEdge(&graph, 'f', 'g', 4);
    addEdge(&graph, 'e', 'g', 1);
    addEdge(&graph, 'g', 'j', 2);
    addEdge(&graph, 'j', 'k', 2);
    //check whether we catch creation of edges between nodes not present:
    addEdge(&graph, 'a', 'z', 2);
    //check whether we catch creation of already existing edges
    addEdge(&graph, 'a', 'b', 2);
    //check, whether circles do work (uncomment this to test, since the exercise did not make clear whether
    //you should handle this
    //addEdge(&graph, 'a', 'a', 7);
    printGraph(graph);

    printf("\nNow traversing graph via depthSearch starting from a\n");
    depthSearch(graph, 'a');
    printVisitedNodes(graph);
    printf("\n");
    resetVisitedNodes(graph);

    //check, whether depthSearch catches invalid start node names:
    printf(
            "\nNow traversing graph via depthSearch starting from non-existing node z\n");
    depthSearch(graph, 'z');
    printVisitedNodes(graph);
    printf("\n");
    resetVisitedNodes(graph);

    printf("\nNow depth searching for h starting at a:\n");
    findByDepthSearch(graph, 'a', 'h');
    printVisitedNodes(graph);
    printf("\n");
    resetVisitedNodes(graph);

    printf("\nNow depth searching for g starting at a:\n");
    findByDepthSearch(graph, 'a', 'g');
    printVisitedNodes(graph);
    printf("\n");
    resetVisitedNodes(graph);

    printf("\nNow depth searching for z starting at a:\n");
    findByDepthSearch(graph, 'a', 'z');
    printVisitedNodes(graph);
    printf("\n");
    resetVisitedNodes(graph);

    printf("\n\n");

    adM* myAdM = createAdjacencyMatrix(graph);
    printAdjacencyMatrix(myAdM);

    freeAdjacencyMatrix(&myAdM);
    freeGraph(&graph);
    return EXIT_SUCCESS;
}
