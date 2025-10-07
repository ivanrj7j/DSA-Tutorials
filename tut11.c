#include <stdio.h>
#include <stdlib.h>

struct AdjListNode {
    int dest;
    struct AdjListNode* next;
};

struct AdjList {
    struct AdjListNode* head;
};

struct Graph {
    int V;
    struct AdjList* array;
};

struct AdjListNode* newAdjListNode(int dest) {
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

void DFSUtil(int v, int visited[], struct Graph* graph) {
    visited[v] = 1;
    printf("%d ", v);
    struct AdjListNode* pCrawl = graph->array[v].head;
    while (pCrawl) {
        if (!visited[pCrawl->dest])
            DFSUtil(pCrawl->dest, visited, graph);
        pCrawl = pCrawl->next;
    }
}

void DFS(struct Graph* graph, int startVertex) {
    int *visited = (int*)calloc(graph->V, sizeof(int));
    printf("Depth First Search (starting from vertex %d): ", startVertex);
    DFSUtil(startVertex, visited, graph);
    printf("\n");
    free(visited);
}

void BFS(struct Graph* graph, int startVertex) {
    int *visited = (int*)calloc(graph->V, sizeof(int));
    int* queue = (int*)malloc(graph->V * sizeof(int));
    int front = 0, rear = 0;

    printf("Breadth First Search (starting from vertex %d): ", startVertex);
    visited[startVertex] = 1;
    queue[rear++] = startVertex;

    while (front != rear) {
        int v = queue[front++];
        printf("%d ", v);
        struct AdjListNode* pCrawl = graph->array[v].head;
        while (pCrawl) {
            if (!visited[pCrawl->dest]) {
                visited[pCrawl->dest] = 1;
                queue[rear++] = pCrawl->dest;
            }
            pCrawl = pCrawl->next;
        }
    }
    printf("\n");
    free(visited);
    free(queue);
}

int main() {
    int V = 5;
    struct Graph* graph = createGraph(V);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    DFS(graph, 0);
    BFS(graph, 0);

    return 0;
}
