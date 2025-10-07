#include <stdio.h>
#include <stdlib.h>

// --- Adjacency List Representation ---
struct AdjListNode {
    int dest;
    struct AdjListNode* next;
};

struct AdjList {
    struct AdjListNode* head;
};

struct GraphList {
    int V;
    struct AdjList* array;
};

struct AdjListNode* newAdjListNode(int dest) {
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// --- Adjacency Matrix Representation ---
struct GraphMatrix {
    int V;
    int** adj;
};

struct GraphMatrix* createGraphMatrix(int V) {
    struct GraphMatrix* graph = (struct GraphMatrix*)malloc(sizeof(struct GraphMatrix));
    graph->V = V;
    graph->adj = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        graph->adj[i] = (int*)calloc(V, sizeof(int));
    }
    return graph;
}

void addEdge(struct GraphMatrix* graph, int src, int dest) {
    // For a directed graph
    if (src < graph->V && dest < graph->V) {
        graph->adj[src][dest] = 1;
    }
}

void printGraphMatrix(struct GraphMatrix* graph) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < graph->V; i++) {
        for (int j = 0; j < graph->V; j++) {
            printf("%d ", graph->adj[i][j]);
        }
        printf("\n");
    }
}

void calculateDegrees(struct GraphMatrix* graph) {
    int inDegree[graph->V];
    int outDegree[graph->V];

    for (int i = 0; i < graph->V; i++) {
        inDegree[i] = 0;
        outDegree[i] = 0;
    }

    for (int i = 0; i < graph->V; i++) {
        for (int j = 0; j < graph->V; j++) {
            if (graph->adj[i][j] == 1) {
                outDegree[i]++;
                inDegree[j]++;
            }
        }
    }

    printf("\nVertex\tIn-Degree\tOut-Degree\n");
    for (int i = 0; i < graph->V; i++) {
        printf("%d\t%d\t\t%d\n", i, inDegree[i], outDegree[i]);
    }
}


int main() {
    int V = 5;
    struct GraphMatrix* graph = createGraphMatrix(V);

    // Using a directed graph to show in-degree and out-degree
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    // Representation of graph using Adjacency Matrix
    printGraphMatrix(graph);

    // Computing various parameters (indegree, outdegree)
    calculateDegrees(graph);


    // Note: The Adjacency List representation is also a valid way to represent a graph.
    // The code for it is included above but the main function demonstrates the matrix
    // as it makes calculating in-degrees more straightforward.

    return 0;
}