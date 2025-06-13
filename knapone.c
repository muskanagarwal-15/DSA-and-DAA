#include <stdio.h>

#define MAX 100

int max(int a, int b) {
    return (a > b) ? a : b;
}

void knapsack(int n, int C, int weights[], int profits[]) {
    int P[MAX][MAX]; // DP table

    // Initialize
    for (int w = 0; w <= C; w++)
        P[0][w] = 0;

    for (int i = 1; i <= n; i++)
        P[i][0] = 0;

    // Fill table using bottom-up dynamic programming
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= C; w++) {
            if (weights[i - 1] <= w) {
                if (profits[i - 1] + P[i - 1][w - weights[i - 1]] > P[i - 1][w]) {
                    P[i][w] = profits[i - 1] + P[i - 1][w - weights[i - 1]];
                } else {
                    P[i][w] = P[i - 1][w];
                }
            } else {
                P[i][w] = P[i - 1][w];
            }
        }
    }

    // Output maximum profit
    printf("Maximum Profit: %d\n", P[n][C]);

    // Find which items are included
    int i = n, k = C;
    printf("Items included (1-based indices): ");
    while (i > 0 && k > 0) {
        if (P[i][k] != P[i - 1][k]) {
            printf("%d ", i);
            k = k - weights[i - 1];
        }
        i = i - 1;
    }
    printf("\n");
}

int main() {
    int n, C;
    int weights[MAX], profits[MAX];

    printf("Enter number of items: ");
    scanf("%d", &n);

    printf("Enter knapsack capacity: ");
    scanf("%d", &C);

    printf("Enter weights of the items:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &weights[i]);
    }

    printf("Enter profits of the items:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &profits[i]);
    }

    knapsack(n, C, weights, profits);

    return 0;
}
