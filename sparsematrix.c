#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define ROWS 3
#define COLS 3
#define MAX_SIZE 100

typedef struct {
    int row;
    int col;
    int value;
} Triplet;

int random_value() {
    return rand() % 2;
}

void toTriplet(int matrix[ROWS][COLS], Triplet *triplets, int *count) {
    *count = 0;
    int i,j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (matrix[i][j] != 0) {
                triplets[*count].row = i;
                triplets[*count].col = j;
                triplets[*count].value = matrix[i][j];
                (*count)++;
            }
        }
    }
}

void printTriplet(Triplet *triplets, int count) {
    int i;
    printf("Row Index\tColumn Index\tValue\n");
    for (i = 0; i < count; i++) {
        printf("%d\t\t%d\t\t%d\n", triplets[i].row, triplets[i].col, triplets[i].value);
    }
}

void addTriplets(Triplet *triplets1, int count1, Triplet *triplets2, int count2, Triplet *result, int *resultCount) {
    int i = 0, j = 0;
    *resultCount = 0;

    while (i < count1 && j < count2) {
        if (triplets1[i].row == triplets2[j].row && triplets1[i].col == triplets2[j].col) {
            result[*resultCount].row = triplets1[i].row;
            result[*resultCount].col = triplets1[i].col;
            result[*resultCount].value = triplets1[i].value + triplets2[j].value;
            i++;
            j++;
        } else if (triplets1[i].row < triplets2[j].row || 
                  (triplets1[i].row == triplets2[j].row && triplets1[i].col < triplets2[j].col)) {
            result[*resultCount] = triplets1[i];
            i++;
        } else {
            result[*resultCount] = triplets2[j];
            j++;
        }
        (*resultCount)++;
    }

    while (i < count1) {
        result[*resultCount] = triplets1[i];
        i++;
        (*resultCount)++;
    }

     while (j < count2) {
        result[*resultCount] = triplets2[j];
        j++;
        (*resultCount)++;
    }
}

int main() {
    int i,j;
    int matrix1[ROWS][COLS];
    int matrix2[ROWS][COLS];
    Triplet triplets1[MAX_SIZE];
    Triplet triplets2[MAX_SIZE];
    Triplet sumResult[MAX_SIZE];
    int count1, count2, sumResultCount;

    srand(time(NULL));

    printf("Original Matrix 1:\n");
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            matrix1[i][j] = random_value();
            printf("%d ", matrix1[i][j]);
        }
        printf("\n");
    }
    printf("Original Matrix 2:\n");
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            matrix2[i][j] = random_value();
            printf("%d ", matrix2[i][j]);
        }
        printf("\n");
    }

    toTriplet(matrix1, triplets1, &count1);
    toTriplet(matrix2, triplets2, &count2);

    printf("\nTriplet1 Representation:\n");
    printTriplet(triplets1, count1);
    printf("\nTriplet2 Representation:\n");
    printTriplet(triplets2, count2);

    addTriplets(triplets1, count1, triplets2, count2, sumResult, &sumResultCount);

    printf("\nSum of Triplet1 and Triplet2 Representation:\n");
    printTriplet(sumResult, sumResultCount);

    return 0;
}
