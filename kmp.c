#include <stdio.h>
#include <string.h>

#define MAX 1000

// Function to compute prefix function
void computePrefixFunction(char *P, int *pi) {
    int m = strlen(P);
    pi[0] = 0;
    int k = 0;

    for (int q = 1; q < m; q++) {
        while (k > 0 && P[k] != P[q]) {
            k = pi[k - 1];
        }
        if (P[k] == P[q]) {
            k++;
        }
        pi[q] = k;
    }
}

// KMP Matcher function
void KMPMatcher(char *T, char *P) {
    int n = strlen(T);
    int m = strlen(P);
    int pi[m];
    int found = 0; 

    computePrefixFunction(P, pi);

    int q = 0;
    for (int i = 0; i < n; i++) {
        while (q > 0 && P[q] != T[i]) {
            q = pi[q - 1];
        }
        if (P[q] == T[i]) {
            q++;
        }
        if (q == m) {
            printf("Pattern valid shift %d\n", i - m + 1);
            q = pi[q - 1];
            found = 1;
        }
    }
    if (!found) {
        printf("Pattern not found in the text.\n");
    }
}

int main() {
    char text[MAX], pattern[MAX];

    printf("Enter the text (no spaces): ");
    scanf("%s", text);

    printf("Enter the pattern (no spaces): ");
    scanf("%s", pattern);

    KMPMatcher(text, pattern);

    return 0;
}
