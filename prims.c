#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

typedef struct Node{
    int dest, weight;
    struct Node *next;
} Node;

typedef struct AdjList{
    Node *head;
} AdjList;

typedef struct Graph{
    int V;
    AdjList *array;
} Graph;

typedef struct{
    int v;
    int key;
} HeapNode;

typedef struct{
    int size;
    int *pos;
    HeapNode *nodes;
} MinHeap;

Node *newNode(int dest, int weight){
    Node *node = malloc(sizeof(Node));
    node->dest = dest;
    node->weight = weight;
    node->next = NULL;
    return node;
}

Graph *createGraph(int V){
    Graph *graph = malloc(sizeof(Graph));
    graph->V = V;
    graph->array = malloc(V * sizeof(AdjList));
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;
    return graph;
}

void addEdge(Graph *graph, int src, int dest, int weight){
    Node *node = newNode(dest, weight);
    node->next = graph->array[src].head;
    graph->array[src].head = node;

    // For undirected graph
    node = newNode(src, weight);
    node->next = graph->array[dest].head;
    graph->array[dest].head = node;
}

MinHeap *createMinHeap(int capacity){
    MinHeap *heap = malloc(sizeof(MinHeap));
    heap->pos = malloc(capacity * sizeof(int));
    heap->size = capacity;
    heap->nodes = malloc(capacity * sizeof(HeapNode));
    return heap;
}

void swapHeapNode(HeapNode *a, HeapNode *b){
    HeapNode t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(MinHeap *heap, int idx){
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->nodes[left].key < heap->nodes[smallest].key)
        smallest = left;

    if (right < heap->size && heap->nodes[right].key < heap->nodes[smallest].key)
        smallest = right;

    if (smallest != idx)
    {
        HeapNode smallestNode = heap->nodes[smallest];
        HeapNode idxNode = heap->nodes[idx];

        heap->pos[smallestNode.v] = idx;
        heap->pos[idxNode.v] = smallest;

        swapHeapNode(&heap->nodes[smallest], &heap->nodes[idx]);

        minHeapify(heap, smallest);
    }
}

int isInMinHeap(MinHeap *heap, int v){
    return heap->pos[v] < heap->size;
}

HeapNode extractMin(MinHeap *heap){
    HeapNode root = heap->nodes[0];
    HeapNode last = heap->nodes[heap->size - 1];
    heap->nodes[0] = last;

    heap->pos[root.v] = heap->size - 1;
    heap->pos[last.v] = 0;

    heap->size--;
    minHeapify(heap, 0);

    return root;
}

void decreaseKey(MinHeap *heap, int v, int key){
    int i = heap->pos[v];
    heap->nodes[i].key = key;

    while (i && heap->nodes[i].key < heap->nodes[(i - 1) / 2].key)
    {
        heap->pos[heap->nodes[i].v] = (i - 1) / 2;
        heap->pos[heap->nodes[(i - 1) / 2].v] = i;
        swapHeapNode(&heap->nodes[i], &heap->nodes[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void primMST(Graph *graph){
    int V = graph->V;
    int *parent = malloc(V * sizeof(int));
    int *key = malloc(V * sizeof(int));
    int totalWeight = 0;

    // 1) Pick a random source
    srand((unsigned)time(NULL));
    int src = rand() % V;

    MinHeap *heap = createMinHeap(V);

    // 2) Initialize keys & heap
    for (int v = 0; v < V; ++v)
    {
        parent[v] = -1;
        key[v] = INT_MAX;
        heap->nodes[v] = (HeapNode){.v = v, .key = key[v]};
        heap->pos[v] = v;
    }
    heap->size = V;

    // 3) Set key[src] = 0 and bubble it up
    key[src] = 0;
    heap->nodes[src].key = 0;
    decreaseKey(heap, src, 0);

    // 4) Standard Prim’s loop
    while (heap->size > 0)
    {
        HeapNode minNode = extractMin(heap);
        int u = minNode.v;

        for (Node *nbr = graph->array[u].head; nbr; nbr = nbr->next)
        {
            int v = nbr->dest;
            int weight = nbr->weight;
            if (isInMinHeap(heap, v) && weight < key[v])
            {
                key[v] = weight;
                parent[v] = u;
                decreaseKey(heap, v, weight);
            }
        }
    }

    // 5) Print with total weight
    printf("Starting from vertex: %d\n", src);
    printf("Edge \tWeight\n");
    for (int i = 0; i < V; ++i)
    {
        if (parent[i] != -1)
        {
            printf("%d - %d \t%d\n", parent[i], i, key[i]);
            totalWeight += key[i];
        }
    }
    printf("Total Weight of MST: %d\n", totalWeight);
    free(parent);
    free(key);
}

int main()
{
    FILE *file = fopen("graph.txt", "r");
    if (!file)
    {
        perror("Error opening graph.txt");
        return EXIT_FAILURE;
    }

    int V;
    if (fscanf(file, "%d", &V) != 1)
    {
        fprintf(stderr, "Invalid format: first line should be vertex count\n");
        fclose(file);
        return EXIT_FAILURE;
    }

    Graph *graph = malloc(sizeof(Graph));
    graph->V = V;
    graph->array = malloc(V * sizeof(AdjList));
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    int u, v, w;
    while (fscanf(file, "%d %d %d", &u, &v, &w) == 3)
        addEdge(graph, u, v, w);
    fclose(file);

    primMST(graph);
    return 0;
}