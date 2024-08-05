#include<stdio.h>
#include<stdlib.h>
#include<time.h>

float **allocate_matrix(int n1, int n2) {
    int i;
    float **matrix = (float **)malloc(n1 * sizeof(float *));
    for (i = 0; i < n1; i++) {
        matrix[i] = (float *)malloc(n2 * sizeof(float));
    }
    return matrix;
}
void initialize_matrix(float **matrix, int n1, int n2) {
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            scanf("%f",&matrix[i][j]) ;
        }
    }
}
void print_matrix(float **matrix, int n1, int n2) {
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
}
void multiply_matrices(float **matrixOne, float **matrixTwo, float **resultMatrix, int n1, int n2) {
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            resultMatrix[i][j] = 0;
            for (int k = 0; k < n2; k++) {
                resultMatrix[i][j] += matrixOne[i][k] * matrixTwo[k][j];
            }
        }
    }
}
int main()
{
    int i,j,n;
    float **matrixOne, **matrixTwo, **resultMatrix;
    srand(time(NULL));
    printf("enter number of rows and columns: ");
    scanf("%d",&n);
    clock_t t;
    t=clock();
    matrixOne = allocate_matrix(n,n);
    matrixTwo = allocate_matrix(n,n);
    resultMatrix = allocate_matrix(n,n);
    for (i=0; i < n; i++){ 
        for (j = 0; j < n; j++){
            matrixOne[i][j] = (float) (rand() % 100);
        }
    }
    for (i=0; i < n; i++){ 
        for (j = 0; j < n; j++){
            matrixTwo[i][j] = (float) (rand() % 100);
        }
    }
    multiply_matrices(matrixOne, matrixTwo, resultMatrix, n, n);

    printf("Matrix One:\n");
    print_matrix(matrixOne, n, n);
    printf("Matrix Two:\n");
    print_matrix(matrixTwo, n, n);
    printf("Result Matrix:\n");
    print_matrix(resultMatrix, n, n);
    t = clock() - t;
    printf("Time taken: %lf secs\n", (double)t / CLOCKS_PER_SEC); 
    for (int i = 0; i < n; i++){
        free(matrixOne[i]);
        free(matrixTwo[i]);
        free(resultMatrix[i]);
    }
    free(matrixOne);
    free(matrixTwo);
    free(resultMatrix);
    return 0;

}

















