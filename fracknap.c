#include <stdio.h>

#define MAX 100

// Structure to store items
typedef struct {
    int index;
    float profit;
    float weight;
    float ratio;
} Item;

// Function to sort items by profit/weight ratio in descending order
void sortItems(Item items[], int n) {
    Item temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (items[j].ratio > items[i].ratio) {
                temp = items[i];
                items[i] = items[j];
                items[j] = temp;
            }
        }
    }
}

// Fractional Knapsack function
float fractionalKnapsack(Item items[], int n, float m, float X[]) {
    sortItems(items, n); // sort items by value-to-weight ratio

    for (int i = 0; i < n; i++) {
        X[i] = 0.0;
    }

    float U = m;
    float totalProfit = 0.0;
    int i;

    for (i = 0; i < n; i++) {
        if (items[i].weight > U)
            break;

        X[items[i].index] = 1.0;
        totalProfit += items[i].profit;
        U -= items[i].weight;
    }

    if (i < n) {
        X[items[i].index] = U / items[i].weight;
        totalProfit += X[items[i].index] * items[i].profit;
    }

    return totalProfit;
}

int main() {
    int n;
    float m, totalProfit;
    Item items[MAX];
    float X[MAX];

    printf("Enter number of items: ");
    scanf("%d", &n);

    printf("Enter capacity of knapsack: ");
    scanf("%f", &m);

    printf("Enter profit and weight of each item:\n");
    for (int i = 0; i < n; i++) {
        items[i].index = i;
        printf("Item %d - Profit: ", i + 1);
        scanf("%f", &items[i].profit);
        printf("Item %d - Weight: ", i + 1);
        scanf("%f", &items[i].weight);
        items[i].ratio = items[i].profit / items[i].weight;
    }

    totalProfit = fractionalKnapsack(items, n, m, X);

    printf("\nFraction of items included:\n");
    for (int i = 0; i < n; i++) {
        printf("Item %d: %.2f\n", i + 1, X[i]);
    }

    printf("Total profit: %.2f\n", totalProfit);

    return 0;
}
