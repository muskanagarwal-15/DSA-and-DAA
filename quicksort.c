#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN 1
#define MAX 100
#define INPUT "input1.txt"
#define OUTPUT1 "output1.txt"

int counter_f = 0;

void generate(int numArr, int numElm)
{
    FILE *fp = fopen(INPUT, "w");
    srand(time(NULL));
    for (int j = 0; j < numArr; j++)
    {
        for (int i = 0; i < numElm; i++)
        {
            int n = (rand() % MAX) + MIN;
            fprintf(fp, "%d\t", n);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void read(int *A, int numElm, FILE *fp)
{
    int i = 0;
    while (i < numElm && fscanf(fp, "%d", &A[i]))
    {
        i++;
    }
}

void write(int *A, int numElm, FILE *fp)
{
    int i;
    for (i = 0; i < numElm; i++)
    {
        fprintf(fp, "%d\t", A[i]);
    }
    fprintf(fp, "\n");
}

int partition(int *A, int l, int h)
{
    int pivot = A[l];
    int i = l, j = h + 1, temp;
    while (i < j)
    {
        do
        {
            i++;
            counter_f++;
        } while (i < h && A[i] <= pivot);
        do
        {
            j--;
            counter_f++;
        } while (j > l && A[j] >= pivot);
        if (i < j)
        {
            temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }
    temp = A[l];
    A[l] = A[j];
    A[j] = temp;
    return j;
}

void quicksort(int *A, int l, int h)
{
    if (l < h)
    {
        int j = partition(A, l, h);
        quicksort(A, l, j);
        quicksort(A, j + 1, h);
    }
}

int main()
{
    int i;
    float total_counter_f = 0;
    int numArr = 0, numElm = 0;
    printf("Enter the number of arrays and elements:\n");
    scanf("%d%d", &numArr, &numElm);

    int *A = (int *)calloc(numElm, sizeof(int));
    int *B = (int *)calloc(numElm, sizeof(int));

    generate(numArr, numElm);
    srand(time(NULL));

    FILE *fp1 = fopen(INPUT, "r");
    FILE *fp2 = fopen(OUTPUT1, "a+");

    for (int i = 0; i < numArr; i++)
    {
        read(A, numElm, fp1);
        for (int k = 0; k < numElm; k++)
            B[k] = A[k];
        quicksort(A, 0, numElm - 1);
        printf("Number of inputs: %d | Number of comparisions: %d\n", numElm, counter_f);
        write(A, numElm, fp2);
        total_counter_f += counter_f;
        counter_f = 0;
    }

    printf("Number of inputs: %d | Number of comparisions: %f\n", numArr * numElm, total_counter_f / numArr);
    fclose(fp1);
    fclose(fp2);
    free(A);
    free(B);
    return 0;
}