#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int LCS(char *a, char *b, int m, int n, int **dp) {
    // Initialize base cases in the DP table
    for (int i = 0; i <= m; i++) {
        dp[i][0] = 0;
    }
    for (int j = 0; j <= n; j++) {
        dp[0][j] = 0;
    }

    // Fill the DP table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i-1] == b[j-1]) {
                // If characters match, add 1 to previous diagonal value
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                // Take max of left and top values
                dp[i][j] = (dp[i-1][j] > dp[i][j-1]) ? dp[i-1][j] : dp[i][j-1];
            }
        }
    }

    // Return length of LCS
    return dp[m][n];
}

void printLCS(char *a, char *b, int **dp, int m, int n) {
    // Reconstruct the LCS
    int index = dp[m][n];
    char *lcs = (char *)malloc((index + 1) * sizeof(char));
    lcs[index] = '\0';  // Null-terminate the string

    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (a[i-1] == b[j-1]) {
            // If characters match, add to LCS
            lcs[index-1] = a[i-1];
            i--;
            j--;
            index--;
        }
        // Move in the direction of higher value
        else if (dp[i-1][j] > dp[i][j-1]) {
            i--;
        } else {
            j--;
        }
    }

    // Print the LCS
    printf("LCS: %s\n", lcs);
    free(lcs);
}

int main() {
    char X[100], Y[100];
    printf("Enter the first string: ");
    scanf("%s", X);
    printf("Enter the second string: ");
    scanf("%s", Y);

    int m = strlen(X), n = strlen(Y);
    
    // Allocate 2D DP table
    int **dp = (int **)malloc((m + 1) * sizeof(int *));
    for (int i = 0; i <= m; i++) {
        dp[i] = (int *)calloc((n + 1), sizeof(int));
    }

    // Compute LCS length
    int lcsLen = LCS(X, Y, m, n, dp);
    printf("Length of LCS: %d\n", lcsLen);

    // Print the LCS
    printLCS(X, Y, dp, m, n);

    // Free memory
    for (int i = 0; i <= m; i++) {
        free(dp[i]);
    }
    free(dp);

    return 0;
}