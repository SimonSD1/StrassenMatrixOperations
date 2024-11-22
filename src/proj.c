// Simon Sepiol-Duchemin
// Joshua Setia

#include <stdlib.h>
#include <stdio.h>
<<<<<<< HEAD
#include <time.h>

typedef struct matrix
{
    double **coefs;
    int columns;
    int rows;
} matrix;
=======
#include "projet.h"
>>>>>>> 2fa9ff360ada30fcb4f509e69622ec1b2c66dc66

void printMatrix(matrix A)
{
    for (int i = 0; i < A.rows; i++)
    {
        for (int j = 0; j < A.columns; j++)
        {
            printf("%lf ", A.coefs[i][j]);
        }
        printf("\n");
    }
}

void freeMatrix(matrix m)
{
    for (int i = 0; i < m.rows; i++)
    {
        free(m.coefs[i]);
    }
    free(m.coefs);
}

matrix *creeMatrix(int rows, int columns)
{
    matrix *m = malloc(sizeof(matrix));
    m->columns = columns;
    m->rows = rows;
    m->coefs = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++)
    {
        m->coefs[i] = malloc(columns * sizeof(double));
    }
    return m;
}

<<<<<<< HEAD
matrix *naiveMultMat(matrix *A, matrix *B)
=======

void remplirMatrixManuel(matrix A) {
    for(int i=0; i<A.rows; i++) {
        for(int j=0; j<A.columns; j++) {
            printf("[%d][%d] = ", i,j);
            scanf("%lf", &A.coefs[i][j]);
        }
    }
}


void copyMatrix(matrix A, matrix copy) {
    for(int i=0; i<A.rows; i++) {
        for(int j=0; j<A.columns; j++) {
            copy.coefs[i][j] = A.coefs[i][j];
        }
    }
}


void identity(matrix A) {
    for(int i=0; i<A.rows; i++) {
        for(int j=0; j<A.columns; j++)
            A.coefs[i][j] = i==j;
    }
}


void naiveMultMat(matrix A, matrix B, matrix result)
>>>>>>> 2fa9ff360ada30fcb4f509e69622ec1b2c66dc66
{
    matrix *result = creeMatrix(A->rows, B->columns);
    for (int i = 0; i < A->rows; i++)
    {
        for (int j = 0; j < B->rows; j++)
        {
            result->coefs[i][j] = 0;
            for (int k = 0; k < A->rows; k++)
            {
                result->coefs[i][j] += A->coefs[i][k] * B->coefs[k][j];
            }
        }
    }

    return result;
}

matrix *matrice_add(matrix *A, matrix *B)
{
    if (A->rows != B->rows || A->columns != B->columns)
    {
        printf("impossible addition");
        return NULL;
    }

    matrix *result = creeMatrix(A->rows, B->columns);

    for (int i = 0; i < A->rows; i++)
    {
        for (int j = 0; j < A->columns; j++)
        {
            result->coefs[i][j] = A->coefs[i][j] + B->coefs[i][j];
        }
    }

    return result;
}

matrix *subMatrixAddition(matrix *A, matrix *B,
                          int startRowA, int startColA, int endRowA, int endColA,
                          int startRowB, int startColB, int endRowB, int endColB)
{
    // Calculate dimensions of the resulting submatrix
    int rowsA = endRowA - startRowA + 1;
    int colsA = endColA - startColA + 1;
    int rowsB = endRowB - startRowB + 1;
    int colsB = endColB - startColB + 1;

    if (rowsA != rowsB || colsA != colsB)
    {
        printf("Submatrix dimensions do not match\n");
        return NULL;
    }

    if (endRowA >= A->rows || endColA >= A->columns || startRowA < 0 || startColA < 0 ||
        endRowB >= B->rows || endColB >= B->columns || startRowB < 0 || startColB < 0)
    {
        printf("Invalid submatrix indices\n");
        return NULL;
    }

    matrix *result = creeMatrix(rowsA, colsA);

    for (int i = 0; i < rowsA; i++)
    {
        for (int j = 0; j < colsA; j++)
        {
            result->coefs[i][j] = A->coefs[startRowA + i][startColA + j] + B->coefs[startRowB + i][startColB + j];
        }
    }

    return result;
}

matrix *matrice_substract(matrix *A, matrix *B)
{
    if (A->rows != B->rows || A->columns != B->columns)
    {
        printf("impossible soustraction");
        return NULL;
    }
    matrix *result = creeMatrix(A->rows, B->columns);

    for (int i = 0; i < A->rows; i++)
    {
        for (int j = 0; j < A->columns; j++)
        {
            result->coefs[i][j] = A->coefs[i][j] - B->coefs[i][j];
        }
    }

    return result;
}

matrix *subMatrixSubtraction(matrix *A, matrix *B, int row1_start, int col1_start, int row1_end, int col1_end,
                             int row2_start, int col2_start, int row2_end, int col2_end)
{
    int rows = row1_end - row1_start + 1;
    int cols = col1_end - col1_start + 1;

    matrix *result = creeMatrix(rows, cols);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            result->coefs[i][j] = A->coefs[row1_start + i][col1_start + j] - B->coefs[row2_start + i][col2_start + j];
        }
    }
    return result;
}

matrix *subMatrix(matrix *original, int startRow, int startCol, int endRow, int endCol)
{
    int newRows = endRow - startRow + 1;
    int newCols = endCol - startCol + 1;

    matrix *sub = creeMatrix(newRows, newCols);

    for (int i = 0; i < newRows; i++)
    {
        for (int j = 0; j < newCols; j++)
        {
            sub->coefs[i][j] = original->coefs[startRow + i][startCol + j];
        }
    }

    return sub;
}

void identity(matrix *A)
{

    for (int i = 0; i < A->columns; i++)
    {

        A->coefs[i][i] = 1;
    }
}

void copyMatrix(matrix *A, matrix *B)
{
    for (int i = 0; i < A->rows; i++)
    {
        for (int j = 0; j < A->columns; j++)
        {
            B->coefs[i][j] = A->coefs[i][j];
        }
    }
}

<<<<<<< HEAD
void LU(matrix *A, matrix *L, matrix *U)
{
    // On initialise L à identity
    identity(L);
    // On initialise U à A
    copyMatrix(A, U);
    for (int i = 0; i < U->rows; i++)
    {
        // Si A a un pivot nul
        if (U->coefs[i][i] == 0)
        {
            printf("LU factorisation is impossible : A has a pivot 0\n");
            return;
        }
        for (int j = i + 1; j < U->rows; j++)
        {                                 // ligne par ligne
            double coeff = U->coefs[j][i]; // coefficient correspondant à la valeur sous le pivot
            for (int k = i; k < U->columns; k++)
            { // colonne par colonne
                U->coefs[j][k] -= coeff / U->coefs[i][i] * U->coefs[i][k];
            }
            // Affectation de coeff/A[i][i] à L
            L->coefs[j][i] = coeff / U->coefs[i][i];
        }
    }
=======
void strassen(matrix A, matrix B, matrix C){
    return;
>>>>>>> 2fa9ff360ada30fcb4f509e69622ec1b2c66dc66
}

// si limite = 2 comme dans un cas theorique, prend plus de temps que naif
matrix *strassen(matrix *A, matrix *B, int limite)
{
    if (A->rows <= limite || A->columns <= limite || B->rows <= limite || B->columns <= limite)
    {
        return naiveMultMat(A, B);
    }

<<<<<<< HEAD
    int size = A->rows;
    int halfSize = size / 2;

    matrix *M1 = strassen(
        subMatrixAddition(A, A, 0, 0, halfSize - 1, halfSize - 1, halfSize, halfSize, size - 1, size - 1),          // A11 + A22
        subMatrixAddition(B, B, 0, 0, halfSize - 1, halfSize - 1, halfSize, halfSize, size - 1, size - 1), limite); // B11 + B22

    matrix *M2 = strassen(
        subMatrixAddition(A, A, halfSize, 0, size - 1, halfSize - 1, halfSize, halfSize, size - 1, size - 1), // A21 + A22
        subMatrix(B, 0, 0, halfSize - 1, halfSize - 1), limite);                                              // B11

    matrix *M3 = strassen(
        subMatrix(A, 0, 0, halfSize - 1, halfSize - 1),                                                                   // A11
        subMatrixSubtraction(B, B, 0, halfSize, halfSize - 1, size - 1, halfSize, halfSize, size - 1, size - 1), limite); // B12 - B22

    matrix *M4 = strassen(
        subMatrix(A, halfSize, halfSize, size - 1, size - 1),                                                       // A22
        subMatrixSubtraction(B, B, halfSize, 0, size - 1, halfSize - 1, 0, 0, halfSize - 1, halfSize - 1), limite); // B21 - B11

    matrix *M5 = strassen(
        subMatrixAddition(A, A, 0, 0, halfSize - 1, halfSize - 1, 0, halfSize, halfSize - 1, size - 1), // A11 + A12
        subMatrix(B, halfSize, halfSize, size - 1, size - 1), limite);                                  // B22

    matrix *M6 = strassen(
        subMatrixSubtraction(A, A, halfSize, 0, size - 1, halfSize - 1, 0, 0, halfSize - 1, halfSize - 1),       // A21 - A11
        subMatrixAddition(B, B, 0, 0, halfSize - 1, halfSize - 1, 0, halfSize, halfSize - 1, size - 1), limite); // B11 + B12

    matrix *M7 = strassen(
        subMatrixSubtraction(A, A, 0, halfSize, halfSize - 1, size - 1, halfSize, halfSize, size - 1, size - 1),       // A12 - A22
        subMatrixAddition(B, B, halfSize, 0, size - 1, halfSize - 1, halfSize, halfSize, size - 1, size - 1), limite); // B21 + B22

    matrix *result = creeMatrix(size, size);

    for (int i = 0; i < halfSize; i++)
    {
        for (int j = 0; j < halfSize; j++)
        {
            // C11 = M1 + M4 - M5 + M7
            result->coefs[i][j] = M1->coefs[i][j] + M4->coefs[i][j] - M5->coefs[i][j] + M7->coefs[i][j];

            // C12 = M3 + M5
            result->coefs[i][j + halfSize] = M3->coefs[i][j] + M5->coefs[i][j];

            // C21 = M2 + M4
            result->coefs[i + halfSize][j] = M2->coefs[i][j] + M4->coefs[i][j];

            // C22 = M1 - M2 + M3 + M6
            result->coefs[i + halfSize][j + halfSize] = M1->coefs[i][j] - M2->coefs[i][j] + M3->coefs[i][j] + M6->coefs[i][j];
        }
    }

    // Free intermediate matrices
    freeMatrix(*M1);
    freeMatrix(*M2);
    freeMatrix(*M3);
    freeMatrix(*M4);
    freeMatrix(*M5);
    freeMatrix(*M6);
    freeMatrix(*M7);

    return result;
}

int main(int argc, char const *argv[])
{

    

    //int size = 64 * 2 * 2 * 2 * 2 * 2 * 2;
    //matrix *A = creeMatrix(size, size);
    //matrix *B = creeMatrix(size, size);
//
    //for (int i = 0; i < size; i++)
    //{
    //    for (int j = 0; j < size; j++)
    //    {
    //        A->coefs[i][j] = i + j + 1 + 100000000;
    //        B->coefs[i][j] = (i + 1) * (j + 1) + 100000000;
    //    }
    //}
//
    //clock_t start_naive = clock();
    //// matrix *result_naive = naiveMultMat(A, B);
    //clock_t end_naive = clock();
//
    //double time_naive = (double)(end_naive - start_naive) / CLOCKS_PER_SEC;
    //printf("Time naive : %f seconds\n", time_naive);
//
    //clock_t start_strassen = clock();
    //matrix *result_strassen = strassen(A, B, 100);
    //clock_t end_strassen = clock();
//
    //double time_strassen = (double)(end_strassen - start_strassen) / CLOCKS_PER_SEC;
    //printf("Time Strassen : %f seconds\n", time_strassen);
//
    //// Libérez la mémoire
    //freeMatrix(*A);
    //freeMatrix(*B);
    //// freeMatrix(*result_naive);
    //freeMatrix(*result_strassen);

    return 0;
=======
void LU(matrix A, matrix L, matrix U) {
    //On initialise L à identity
    identity(L);
    //On initialise U à A
    copyMatrix(A, U);
    for(int i=0; i<U.rows; i++) {
        //Si A a un pivot nul
        if (U.coefs[i][i]==0) {
            printf("LU factorisation is impossible : A has a pivot 0\n");
            return;
        }
        for(int j=i+1; j<U.rows; j++) {   //ligne par ligne
            double coeff = U.coefs[j][i];  //coefficient correspondant à la valeur sous le pivot
            for(int k=i; k<U.columns; k++) {     //colonne par colonne
                U.coefs[j][k] -= coeff/U.coefs[i][i]*U.coefs[i][k];
            }
            //Affectation de coeff/A[i][i] à L
            L.coefs[j][i] = coeff/U.coefs[i][i];
        }
    }
>>>>>>> 2fa9ff360ada30fcb4f509e69622ec1b2c66dc66
}
