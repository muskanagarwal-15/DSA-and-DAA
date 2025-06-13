#include <stdio.h>
#include <stdlib.h>

// Define Priority Queue as a Min Heap
typedef struct {
    int *data;
    int size;
    int capacity;
} PriorityQueue;

// Create a priority queue
PriorityQueue* create_priority_queue(int capacity) {
    PriorityQueue *pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    pq->data = (int *)malloc(sizeof(int) * capacity);
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}

// Swap two integers
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Heapify up to maintain min-heap
void heapify_up(PriorityQueue *pq, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (pq->data[parent] > pq->data[index]) {
            swap(&pq->data[parent], &pq->data[index]);
            index = parent;
        } else {
            break;
        }
    }
}

// Heapify down to maintain min-heap
void heapify_down(PriorityQueue *pq, int index) {
    int left, right, smallest;

    while (1) {
        left = 2 * index + 1;
        right = 2 * index + 2;
        smallest = index;

        if (left < pq->size && pq->data[left] < pq->data[smallest])
            smallest = left;
        if (right < pq->size && pq->data[right] < pq->data[smallest])
            smallest = right;

        if (smallest != index) {
            swap(&pq->data[index], &pq->data[smallest]);
            index = smallest;
        } else {
            break;
        }
    }
}

// Insert into min-heap
void insert(PriorityQueue *pq, int value) {
    if (pq->size == pq->capacity) {
        pq->capacity *= 2;
        pq->data = realloc(pq->data, pq->capacity * sizeof(int));
    }
    pq->data[pq->size] = value;
    heapify_up(pq, pq->size);
    pq->size++;
}

// Extract min from min-heap
int extract_min(PriorityQueue *pq) {
    if (pq->size == 0) return -1;
    int min = pq->data[0];
    pq->data[0] = pq->data[--pq->size];
    heapify_down(pq, 0);
    return min;
}

// Free memory
void free_priority_queue(PriorityQueue *pq) {
    free(pq->data);
    free(pq);
}

// Heap sort using min-heap priority queue (ascending order)
void heap_sort(int arr[], int size) {
    PriorityQueue *pq = create_priority_queue(size);

    // Insert all elements into the min-heap
    for (int i = 0; i < size; i++)
        insert(pq, arr[i]);

    // Extract min elements to sort in ascending order
    for (int i = 0; i < size; i++)
        arr[i] = extract_min(pq);

    free_priority_queue(pq);
}

int main() {
    int n;

    // Input array size
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));

    // Input array elements
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    // Perform heap sort (ascending)
    heap_sort(arr, n);

    // Output sorted array
    printf("Sorted array (ascending order):\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    free(arr);
    return 0;
}
