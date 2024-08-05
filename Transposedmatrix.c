#include <stdio.h>
#define ROWS 3
#define COLS 3
int main() {
    int A[ROWS][COLS];
    int B[COLS][ROWS];
    printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("A[%d][%d]= ",i,j);
            scanf("%d", &A[i][j]);
        }
    }
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            B[j][i] = A[i][j];
        }
    }
    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("Expected address: %lu\n", &B[j][i]);
            printf("Calculated address: %p\n", (int)(&B[0][0] + i*COLS*sizeof(int) + j*sizeof(int)) - B[0][0]);
        }
    }
    return 0;
}