#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int dest;
    struct Node* next;
} Node;

typedef struct {
    Node** adjList;
    int V;
} Graph;

// Create a new node
Node* createNode(int dest) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->dest = dest;
    node->next = NULL;
    return node;
}

// Create a graph
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->adjList = (Node**)malloc(V * sizeof(Node*));
    for (int i = 0; i < V; i++)
        graph->adjList[i] = NULL;
    return graph;
}

// Add edge
void addEdge(Graph* graph, int u, int v) {
    Node* node = createNode(v);
    node->next = graph->adjList[u];
    graph->adjList[u] = node;

    // For undirected graph:
    // node = createNode(u);
    // node->next = graph->adjList[v];
    // graph->adjList[v] = node;
}

// Display adjacency list
void printGraph(Graph* graph) {
    for (int i = 0; i < graph->V; i++) {
        printf("%d: ", i);
        Node* temp = graph->adjList[i];
        while (temp) {
            printf("%d -> ", temp->dest);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

// Free memory
void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->V; i++) {
        Node* temp = graph->adjList[i];
        while (temp) {
            Node* next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(graph->adjList);
    free(graph);
}

int main() {
    int V, E;
    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);

    Graph* graph = createGraph(V);

    printf("Enter edges (u v):\n");
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
    }

    printf("\nAdjacency List:\n");
    printGraph(graph);
    freeGraph(graph);
    return 0;
}

// Reuse previous Graph, Node, addEdge, printGraph, freeGraph functions here...
//Edge list from a file
// int main() {
//     FILE *file = fopen("graph.txt", "r");
//     if (!file) {
//         printf("Failed to open file.\n");
//         return 1;
//     }

//     int V, E;
//     fscanf(file, "%d %d", &V, &E);

//     Graph* graph = createGraph(V);

//     for (int i = 0; i < E; i++) {
//         int u, v;
//         fscanf(file, "%d %d", &u, &v);
//         addEdge(graph, u, v);
//     }

//     printf("Adjacency List from file:\n");
//     printGraph(graph);
//     fclose(file);
//     freeGraph(graph);
//     return 0;
// }

//adjacency matrix
// int main() {
//     int V;
//     printf("Enter number of vertices: ");
//     scanf("%d", &V);

//     int matrix[V][V];
//     printf("Enter the adjacency matrix:\n");
//     for (int i = 0; i < V; i++)
//         for (int j = 0; j < V; j++)
//             scanf("%d", &matrix[i][j]);

//     Graph* graph = createGraph(V);

//     for (int i = 0; i < V; i++) {
//         for (int j = 0; j < V; j++) {
//             if (matrix[i][j] != 0) {
//                 addEdge(graph, i, j);
//             }
//         }
//     }

//     printf("Adjacency List from matrix:\n");
//     printGraph(graph);
//     freeGraph(graph);
//     return 0;
// }

