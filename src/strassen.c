#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/strassen.h"

#include "../include/matrix.h"

int nextPowerOfTwo(int n)
{
    int power = 1;
    while (power < n)
    {
        power <<= 1;
    }
    return power;
}

void ajusteMatrix(matrix *A, matrix *padded)
{
    int newSize = nextPowerOfTwo(A->rows > A->columns ? A->rows : A->columns);
    for (int i = 0; i < A->rows; i++)
    {
        for (int j = 0; j < A->columns; j++)
        {
            padded->coefs[i][j] = A->coefs[i][j];
        }
    }
    for (int i = A->rows; i < newSize; i++)
    {
        for (int j = 0; j < newSize; j++)
        {
            padded->coefs[i][j] = 0;
        }
    }
    for (int i = 0; i < A->rows; i++)
    {
        for (int j = A->columns; j < newSize; j++)
        {
            padded->coefs[i][j] = 0;
        }
    }
}

void extractResult(matrix *paddedResult, matrix *result, int originalRows, int originalColumns)
{
    for (int i = 0; i < originalRows; i++)
    {
        for (int j = 0; j < originalColumns; j++)
        {
            result->coefs[i][j] = paddedResult->coefs[i][j];
        }
    }
}

void strassenRecursive(matrix *A, matrix *B, matrix *result, int limite)
{
    if (A->rows <= limite || A->columns <= limite || B->rows <= limite || B->columns <= limite)
    {
        naiveMultMat(A, B, result);
        return;
    }
    int size = A->rows;
    int halfSize = size / 2;
    matrix *M1 = creeMatrix(halfSize, halfSize);
    matrix *M2 = creeMatrix(halfSize, halfSize);
    matrix *M3 = creeMatrix(halfSize, halfSize);
    matrix *M4 = creeMatrix(halfSize, halfSize);
    matrix *M5 = creeMatrix(halfSize, halfSize);
    matrix *M6 = creeMatrix(halfSize, halfSize);
    matrix *M7 = creeMatrix(halfSize, halfSize);
    matrix *A11 = creeMatrix(halfSize, halfSize);
    matrix *A12 = creeMatrix(halfSize, halfSize);
    matrix *A21 = creeMatrix(halfSize, halfSize);
    matrix *A22 = creeMatrix(halfSize, halfSize);
    matrix *B11 = creeMatrix(halfSize, halfSize);
    matrix *B12 = creeMatrix(halfSize, halfSize);
    matrix *B21 = creeMatrix(halfSize, halfSize);
    matrix *B22 = creeMatrix(halfSize, halfSize);
    subMatrix(A, A11, 0, 0, halfSize - 1, halfSize - 1);
    subMatrix(A, A12, 0, halfSize, halfSize - 1, size - 1);
    subMatrix(A, A21, halfSize, 0, size - 1, halfSize - 1);
    subMatrix(A, A22, halfSize, halfSize, size - 1, size - 1);
    subMatrix(B, B11, 0, 0, halfSize - 1, halfSize - 1);
    subMatrix(B, B12, 0, halfSize, halfSize - 1, size - 1);
    subMatrix(B, B21, halfSize, 0, size - 1, halfSize - 1);
    subMatrix(B, B22, halfSize, halfSize, size - 1, size - 1);
    matrice_add(A11, A22, M1);
    matrice_add(A21, A22, M2);
    matrice_substract(B12, B22, M3);
    matrice_substract(B21, B11, M4);
    matrice_add(A11, A12, M5);
    matrice_substract(A21, A11, M6);
    matrice_substract(A12, A22, M7);
    strassenRecursive(M1, M1, M1, limite);
    strassenRecursive(M2, B11, M2, limite);
    strassenRecursive(A11, M3, M3, limite);
    strassenRecursive(A22, M4, M4, limite);
    strassenRecursive(M5, B22, M5, limite);
    strassenRecursive(M6, M6, M6, limite);
    strassenRecursive(M7, M7, M7, limite);
    for (int i = 0; i < halfSize; i++)
    {
        for (int j = 0; j < halfSize; j++)
        {
            result->coefs[i][j] = M1->coefs[i][j] + M4->coefs[i][j] - M5->coefs[i][j] + M7->coefs[i][j];
            result->coefs[i][j + halfSize] = M3->coefs[i][j] + M5->coefs[i][j];
            result->coefs[i + halfSize][j] = M2->coefs[i][j] + M4->coefs[i][j];
            result->coefs[i + halfSize][j + halfSize] = M1->coefs[i][j] - M2->coefs[i][j] + M3->coefs[i][j] + M6->coefs[i][j];
        }
    }
    freeMatrix(*M1);
    freeMatrix(*M2);
    freeMatrix(*M3);
    freeMatrix(*M4);
    freeMatrix(*M5);
    freeMatrix(*M6);
    freeMatrix(*M7);
    freeMatrix(*A11);
    freeMatrix(*A12);
    freeMatrix(*A21);
    freeMatrix(*A22);
    freeMatrix(*B11);
    freeMatrix(*B12);
    freeMatrix(*B21);
    freeMatrix(*B22);
}

void strassen(matrix *A, matrix *B, matrix *result, int limite)
{
    matrix *Aajuste = creeMatrix(nextPowerOfTwo(A->rows > A->columns ? A->rows : A->columns), nextPowerOfTwo(A->rows > A->columns ? A->rows : A->columns));
    matrix *Bajuste = creeMatrix(nextPowerOfTwo(B->rows > B->columns ? B->rows : B->columns), nextPowerOfTwo(B->rows > B->columns ? B->rows : B->columns));
    matrix *paddedResult = creeMatrix(nextPowerOfTwo(A->rows > A->columns ? A->rows : A->columns), nextPowerOfTwo(A->rows > A->columns ? A->rows : A->columns));
    ajusteMatrix(A, Aajuste);
    ajusteMatrix(B, Bajuste);
    strassenRecursive(Aajuste, Bajuste, paddedResult, limite);
    extractResult(paddedResult, result, A->rows, B->columns);
    freeMatrix(*Aajuste);
    freeMatrix(*Bajuste);
    freeMatrix(*paddedResult);
}

void createSubmatrix(matrix *A, matrix *result, int begin_row, int begin_col)
{
    for (int i = 0; i < result->rows; i++)
    {
        for (int j = 0; j < result->columns; j++)
        {
            result->coefs[i][j] = A->coefs[i + begin_row][j + begin_col];
        }
    }
}

void strassen_inverse_recursive_naive(matrix *A, matrix *result)
{
    if (A->columns == 1)
    {
        result->coefs[0][0] = 1.0 / A->coefs[0][0];
        return;
    }
    int col = A->columns;
    int row = A->rows;
    matrix *a = creeMatrix(row / 2, col / 2);
    matrix *b = creeMatrix(row / 2, col / 2);
    matrix *c = creeMatrix(row / 2, col / 2);
    matrix *d = creeMatrix(row / 2, col / 2);
    createSubmatrix(A, a, 0, 0);
    createSubmatrix(A, b, 0, col / 2);
    createSubmatrix(A, c, row / 2, 0);
    createSubmatrix(A, d, row / 2, col / 2);
    matrix *e = creeMatrix(row / 2, col / 2);
    strassen_inverse_recursive_naive(a, e);
    matrix *Z = creeMatrix(row / 2, col / 2);
    naiveMultMat(c, e, Z);
    naiveMultMat(Z, b, Z);
    subMatrixSubtraction(d, Z, Z, 0, 0, Z->rows - 1, Z->columns - 1, 0, 0, Z->rows - 1, Z->columns - 1);
    matrix *t = creeMatrix(row / 2, col / 2);
    strassen_inverse_recursive_naive(Z, t);
    naiveMultMat(e, b, b);
    naiveMultMat(t, c, a);
    naiveMultMat(a, e, a);
    naiveMultMat(b, t, c);
    naiveMultMat(b, a, d);
    matrice_add(e, d, d);
    negativeMatrix(c);
    negativeMatrix(a);
    fillSubmatrix(result, d, 0, 0);
    fillSubmatrix(result, c, 0, result->columns / 2);
    fillSubmatrix(result, a, result->rows / 2, 0);
    fillSubmatrix(result, t, result->rows / 2, result->columns / 2);
    freeMatrix(*a);
    freeMatrix(*b);
    freeMatrix(*c);
    freeMatrix(*d);
    freeMatrix(*e);
    freeMatrix(*Z);
    freeMatrix(*t);
}

void strassen_inverse_naive(matrix *A, matrix *result)
{
    matrix *Aajuste = creeMatrix(nextPowerOfTwo(A->rows > A->columns ? A->rows : A->columns), nextPowerOfTwo(A->rows > A->columns ? A->rows : A->columns));
    matrix *paddedResult = creeMatrix(nextPowerOfTwo(A->rows > A->columns ? A->rows : A->columns), nextPowerOfTwo(A->rows > A->columns ? A->rows : A->columns));
    ajusteMatrix(A, Aajuste);
    strassen_inverse_recursive_naive(Aajuste, paddedResult);
    extractResult(paddedResult, result, A->rows, A->columns);
    freeMatrix(*Aajuste);
    freeMatrix(*paddedResult);
}
