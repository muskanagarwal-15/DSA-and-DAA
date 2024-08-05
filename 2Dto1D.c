#include <stdio.h>
#include <stdlib.h>

int main() {
    
    int A[3][4];
    int B[3*4];
    int i,j;
    printf("Enter the elements of the matrix A:\n");
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 4; j++) {
            printf("A[%d][%d] : ", i, j);
            scanf("%d", &A[i][j]);
        }
    }
    int k = 0;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 4; j++) {
            printf("Expected address: %lu\n",&A[i][j]);
            int x = (int)(&A[0][0] + i*4*sizeof(int) + j*sizeof(int));
            printf("Calculated address: %p\n", &A[i][j] - x);
            B[k++] = A[i][j];
        }
    }
    printf("1D array B:\n");
    for(int k = 0; k < 3 * 4; k++) {
        printf("%d ", B[k]);
    }
    printf("\n");
    return 0;
}