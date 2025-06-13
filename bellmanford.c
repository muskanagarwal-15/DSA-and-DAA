#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define INF INT_MAX
#define MAX_LINE 100

// Node in adjacency list
typedef struct Node {
    int dest, weight;
    struct Node *next;
} Node;

// Graph structure
typedef struct {
    Node **adjList;
    int V;
} Graph;

// Edge structure
typedef struct {
    int u, v, weight;
} Edge;

// Create a new node
Node* createNode(int dest, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
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

// Add an edge
void addEdge(Graph* graph, int src, int dest, int weight) {
    Node* newNode = createNode(dest, weight);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;
}

// Count edges
int countEdges(Graph* graph) {
    int count = 0;
    for (int i = 0; i < graph->V; i++) {
        Node* temp = graph->adjList[i];
        while (temp) {
            count++;
            temp = temp->next;
        }
    }
    return count;
}

// Build edge list
Edge* buildEdgeList(Graph* graph, int *E) {
    *E = countEdges(graph);
    Edge* edges = (Edge*)malloc((*E) * sizeof(Edge));
    int index = 0;
    for (int i = 0; i < graph->V; i++) {
        Node* temp = graph->adjList[i];
        while (temp) {
            edges[index].u = i;
            edges[index].v = temp->dest;
            edges[index].weight = temp->weight;
            index++;
            temp = temp->next;
        }
    }
    return edges;
}

// Print path using parent array
void printPath(int *parent, int v) {
    if (parent[v] == -1) {
        printf("%d", v);
        return;
    }
    printPath(parent, parent[v]);
    printf(" -> %d", v);
}

// Bellman-Ford algorithm with path tracking
bool bellmanFord(Graph* graph, int src, int *dist, int *parent) {
    int E;
    Edge* edges = buildEdgeList(graph, &E);
    int V = graph->V;

    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[src] = 0;

    // Relax edges V-1 times
    for (int i = 1; i < V; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].u;
            int v = edges[j].v;
            int w = edges[j].weight;
            if (dist[u] != INF && dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                parent[v] = u;
            }
        }
    }

    // Check for negative cycles
    for (int j = 0; j < E; j++) {
        int u = edges[j].u;
        int v = edges[j].v;
        int w = edges[j].weight;
        if (dist[u] != INF && dist[v] > dist[u] + w) {
            free(edges);
            return false;
        }
    }

    free(edges);
    return true;
}

// Main function
int main() {
    FILE *file = fopen("graph2.txt", "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    int V, E;
    fscanf(file, "%d %d", &V, &E);
    Graph* graph = createGraph(V);

    for (int i = 0; i < E; i++) {
        int u, v, w;
        fscanf(file, "%d %d %d", &u, &v, &w);
        addEdge(graph, u, v, w);
    }

    fclose(file);

    int source;
    printf("Enter source vertex (0 to %d): ", V - 1);
    scanf("%d", &source);

    int *dist = (int*)malloc(V * sizeof(int));
    int *parent = (int*)malloc(V * sizeof(int));

    if (bellmanFord(graph, source, dist, parent)) {
        printf("Vertex\tDistance\tPath\n");
        for (int i = 0; i < V; i++) {
            printf("%d\t", i);
            if (dist[i] == INF) {
                printf("INF\t\t-\n");
            } else {
                printf("%d\t\t", dist[i]);
                printPath(parent, i);
                printf("\n");
            }
        }
    } else {
        printf("Graph contains a negative weight cycle.\n");
    }

    // Free memory
    for (int i = 0; i < V; i++) {
        Node* temp = graph->adjList[i];
        while (temp) {
            Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(graph->adjList);
    free(graph);
    free(dist);
    free(parent);

    return 0;
}

