//
//  main.c
//  GAAL_1
//
//  Created by Alan Jeferson on 07/02/16.
//  Copyright © 2016 AJWorks. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/** Alocates and returns a matrix given the number of rows and columns */
int **initMatrix(int rows, int columns) {
    
    int i;
    int **matrix = (int **) malloc(rows * sizeof(int*));
    
    for (i = 0; i < rows; i++) {
        matrix[i] = (int *) malloc(columns * sizeof(int));
    }
    
    return matrix;
}

/** Sets a value on a given position of a matrix */
void setValue(int value, int **matrix, int row, int column) {
    matrix[row][column] = value;
}

/** Generates a new matrix by incrementing a number on every position */
int **linearMatriz(int from, int rows, int columns) {
    
    int i, j;
    int **result = initMatrix(rows, columns);
    
    for (i = 0; i < rows; i++) {
        for (j = 0; j < columns; j++) {
            result[i][j] = from++;
        }
    }
    
    return result;
}

/** Generates a matrix with random numbers */
int **randomMatrix(int rows, int columns, int limit) {
    
    int i, j;
    int **matrix = initMatrix(rows, columns);
    
    for (i = 0; i < rows; i++) {
        for (j = 0; j < columns; j++) {
            setValue((rand() % limit), matrix, i, j);
        }
    }
    
    return matrix;
}

/** Displays a formated matrix on the console */
void printMatrix(int **matrix, int rows, int columns) {
    
    int i, j;
    
    for (i = 0; i < rows; i++) {
        for (j = 0; j < columns; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    
}

/** Copy all values from matrixA to matrixB */
void copyMatrix(int **matrixA, int **matrixB, int rows, int columns) {
    
    int i, j;
    
    for (i = 0; i < rows; i++) {
        for (j = 0; j < columns; j++) {
            matrixB[i][j] = matrixA[i][j];
        }
    }
    
}

/** Sums two matrixes */
int** sumMatrixes(int ra, int ca, int **matrixA, int rb, int cb, int **matrixB) {
    
    int i, j;
    int **resultMatrix;
    
    if (ca != cb || ra != rb) {
        return NULL;
    }
    
    resultMatrix = initMatrix(ra, ca);

    for (i = 0; i < ra; i++) {
        for (j = 0; j < ca; j++) {
            resultMatrix[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }
    
    return resultMatrix;
    
}

/** Subtracts two matrixes */
int** subtractMatrixes(int ra, int ca, int **matrixA, int rb, int cb, int **matrixB) {
    
    int i, j;
    int **resultMatrix;
    
    if (ca != cb || ra != rb) {
        return NULL;
    }
    
    resultMatrix = initMatrix(ra, ca);
    
    for (i = 0; i < ra; i++) {
        for (j = 0; j < ca; j++) {
            resultMatrix[i][j] = matrixA[i][j] - matrixB[i][j];
        }
    }
    
    return resultMatrix;
    
}

/** Subtracts two matrix and print stuff on the console */
void coolMatrixSum(int rowsA, int columnsA, int **matrixA, int rowsB, int columnsB, int **matrixB) {
    
    printf("Trying to sum matrixes...\n\n");
    
    printf("Matrix A:\n");
    printMatrix(matrixA, rowsA, columnsA);
    printf("\n");
    
    printf("Matrix B:\n");
    printMatrix(matrixB, rowsB, columnsB);
    printf("\n");
    
    int **resultMatrix = sumMatrixes(rowsA, columnsA, matrixA, rowsB, columnsB, matrixB);
    
    if (resultMatrix != NULL) {
        printf("Result:\n");
        printMatrix(resultMatrix, rowsA, columnsA);
    } else {
        printf("Can't sum matrixes\n");
    }
}

/** Function that actually multiply two square matrixes with n equal to a exponent of two */
void strassen(int n, int **matrixA, int **matrixB, int **result) {
    
    int i, j;
    int k;
    int **a11, **a12, **a21, **a22;
    int **b11, **b12, **b21, **b22;
    int **c11, **c12, **c21, **c22;
    int **resultA, **resultB;
    int **p1, **p2, **p3, **p4, **p5, **p6, **p7;
    
    if (n == 1) {
        result[0][0] = matrixA[0][0] * matrixB[0][0];
        return;
    }
    
    k = n / 2;
    
    // Initiating the quadrants of matrixes
    a11 = initMatrix(k, k);
    a12 = initMatrix(k, k);
    a21 = initMatrix(k, k);
    a22 = initMatrix(k, k);
    
    b11 = initMatrix(k, k);
    b12 = initMatrix(k, k);
    b21 = initMatrix(k, k);
    b22 = initMatrix(k, k);
    
    p1 = initMatrix(k, k);
    p2 = initMatrix(k, k);
    p3 = initMatrix(k, k);
    p4 = initMatrix(k, k);
    p5 = initMatrix(k, k);
    p6 = initMatrix(k, k);
    p7 = initMatrix(k, k);
    
    // Filling in the submatrixes
    for (i = 0; i < k; i++) {
        for (j = 0; j < k; j++) {
            a11[i][j] = matrixA[i][j];
            a12[i][j] = matrixA[i][j + k];
            a21[i][j] = matrixA[i + k][j];
            a22[i][j] = matrixA[i + k][j + k];
            
            b11[i][j] = matrixB[i][j];
            b12[i][j] = matrixB[i][j + k];
            b21[i][j] = matrixB[i + k][j];
            b22[i][j] = matrixB[i + k][j + k];
        }
    }
    
    // Calculating from p1 to p7
    resultA = sumMatrixes(k, k, a11, k, k, a22);
    resultB = sumMatrixes(k, k, b11, k, k, b22);
    strassen(k, resultA, resultB, p1); // p1 = (a11 + a22) * (b11 + b22)
    
    resultA = sumMatrixes(k, k, a21, k, k, a22);
    strassen(k, resultA, b11, p2); // p2 = (a21 + a22) * (b11)
    
    resultB = subtractMatrixes(k, k, b12, k, k, b22);
    strassen(k, a11, resultB, p3); // p3 = (a11) * (b12 - b22)
    
    resultB = subtractMatrixes(k, k, b21, k, k, b11);
    strassen(k, a22, resultB, p4); // p4 = (a22) * (b21 - b11)
    
    resultA = sumMatrixes(k, k, a11, k, k, a12);
    strassen(k, resultA, b22, p5); // p5 = (a11 + a12) * (b22)
    
    resultA = subtractMatrixes(k, k, a21, k, k, a11);
    resultB = sumMatrixes(k, k, b11, k, k, b12);
    strassen(k, resultA, resultB, p6); // p6 = (a21 - a11) * (b11 + b12)
    
    resultA = subtractMatrixes(k, k, a12, k, k, a22);
    resultB = sumMatrixes(k, k, b21, k, k, b22);
    strassen(k, resultA, resultB, p7); // p7 = (a12 - a22) * (b21 + b22)
    
    
    // Calculating c's
    c12 = sumMatrixes(k, k, p3, k, k, p5); // c12 = p3 + p5
    c21 =  sumMatrixes(k, k, p2, k, k, p4); // c21 = p2 + p4
    
    resultA = sumMatrixes(k, k, p1, k, k, p4);
    resultB = sumMatrixes(k, k, resultA, k, k, p7);
    c11 = subtractMatrixes(k, k, resultB, k, k, p5); // c11 = p1 + p4 - p5 + p7
    
    resultA = sumMatrixes(k, k, p1, k, k, p3);
    resultB = sumMatrixes(k, k, resultA, k, k, p6);
    c22 = subtractMatrixes(k, k, resultB, k, k, p2); // c22 = p1 + p3 - p2 + p6
    
    // Copying the results
    for (i = 0; i < k; i++) {
        for (j = 0; j < k; j++) {
            result[i][j] = c11[i][j];
            result[i][j + k] = c12[i][j];
            result[i + k][j] = c21[i][j];
            result[i + k][j + k] = c22[i][j];
        }
    }
    
    // Deallocating memory
    free(a11);
    free(a12);
    free(a21);
    free(a22);
    free(b11);
    free(b12);
    free(b21);
    free(b22);
    free(c11);
    free(c12);
    free(c21);
    free(c22);
    free(resultA);
    free(resultB);
    free(p1);
    free(p2);
    free(p3);
    free(p4);
    free(p5);
    free(p6);
    free(p7);
    
}

/** Gives the closest power of two that is equal or bigger than the given number */
int closestPowerOfTwo(int value) {
    return (int) ceil(log2(value));
}

/** Multiply two matrixes */
int **multiplyMatrixes(int rowsA, int columnsA, int **matrixA, int rowsB, int columnsB, int **matrixB, int *rowsR, int *columnsR) {
    
    int **multA, **multB;
    int **result, **fineResult;
    int k = 0;
    int power;
    int i, j;
    
    // Check if the matrixes can multiply
    if(columnsA != rowsB) {
        return NULL;
    }
    
    *rowsR = rowsA;
    *columnsR = columnsB;
    
    k = rowsA > k ? rowsA : k;
    k = columnsA > k ? columnsA : k;
    k = rowsB > k ? rowsB : k;
    k = columnsB > k ? columnsB : k;
    
    power = (int) pow(2, closestPowerOfTwo(k));
    
    multA = initMatrix(power, power);
    multB = initMatrix(power, power);
    
    for (i = 0; i < power; i++) {
        
        for (j = 0; j < power; j++) {
            
            if (i < rowsA && j < columnsA) {
                multA[i][j] = matrixA[i][j];
            } else {
                multA[i][j] = 0;
            }
            
            if (i < rowsB && j < columnsB) {
                multB[i][j] = matrixB[i][j];
            } else {
                multB[i][j] = 0;
            }
            
        }
    }
    
    result = initMatrix(power, power);
    strassen(power, multA, multB, result);

    fineResult = initMatrix(*rowsR, *columnsR);

    for (i = 0; i < *rowsR; i++) {
        for (j = 0; j < *columnsR; j++) {
            fineResult[i][j] = result[i][j];
        }
    }
    
    
    // Deallocating memory
    free(multA);
    free(multB);
    free(result);
    
    return fineResult;
    
}

/** Multiply two matrixes and print stuff on the screen */
void coolMatrixesMultiplication(int rowsA, int columnsA, int **matrixA, int rowsB, int columnsB, int **matrixB) {
    
    int **result;
    int *rowsR, *columnsR;
    
    printf("Trying to multiply matrixes...\n\n");
    
    printf("Matrix A:\n");
    printMatrix(matrixA, rowsA, columnsA);
    printf("\n");
    
    printf("Matrix B:\n");
    printMatrix(matrixB, rowsB, columnsB);
    printf("\n");
    
    rowsR = (int *) malloc(sizeof(int));
    columnsR = (int *) malloc(sizeof(int));
    result = multiplyMatrixes(rowsA, columnsA, matrixA, rowsB, columnsB, matrixB, rowsR, columnsR);
    
    if (result == NULL) {
        printf("Can't multiply matrixes.\n");
    } else {
        printf("Result:\n");
        printMatrix(result, *rowsR, *columnsR);
    }
    
    free(result);
    free(rowsR);
    free(columnsR);
    
}

/** Powers a matrix */
int **powMatrix(int **matrix, int rows, int columns, int exp) {
    
    int i;
    int *a, *b;
    int **result;
    
    if (rows != columns) {
        return NULL;
    }
    
    a = (int *) malloc(sizeof(int));
    b = (int *) malloc(sizeof(int));
    
    result = initMatrix(rows, columns);
    copyMatrix(matrix, result, rows, columns);
    
    for (i = 1; i < exp; i++) {
        result = multiplyMatrixes(rows, columns, result, rows, rows, matrix, a, b);
    }
    
    free(a);
    free(b);
    
    return result;
    
}

/** Powers a matrix and prints stuff on the screen */
void coolMatrixExponentiation(int **matrix, int rows, int columns, int exp) {
    
    int **result;
    
    printf("Trying to exponentiate the following matrix to %d:\n\n", exp);
    
    printMatrix(matrix, rows, columns);
    printf("\n");
    
    result = powMatrix(matrix, rows, columns, exp);
    
    if (result == NULL) {
        printf("Can't exponentiate matrix.\n");
    } else {
        printf("Result:\n");
        printMatrix(result, rows, columns);
    }
    
    free(result);
    
}

int main(int argc, const char * argv[]) {
    
    srand((int)time(NULL));

    // Sum
//    int **matrixA = randomMatrix(3, 2, 100);
//    int **matrixB = randomMatrix(3, 2, 100);
//    coolMatrixSum(3, 2, matrixA, 3, 2, matrixB);
    
    // Multiplication
//    int **matrixA = linearMatriz(1, 5, 3);
//    int **matrixB = linearMatriz(1, 3, 3);
//    coolMatrixesMultiplication(5, 3, matrixA, 3, 3, matrixB);

    // Exponentiation
    int **matrix = randomMatrix(3, 3, 10);
    coolMatrixExponentiation(matrix, 3, 3, 3);
    
    return 0;
}
