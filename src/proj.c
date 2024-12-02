// Simon Sepiol-Duchemin
// Joshua Setia

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct matrix
{
    double **coefs;
    int columns;
    int rows;
} matrix;

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

matrix *naiveMultMat(matrix *A, matrix *B)
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
        {                                  // ligne par ligne
            double coeff = U->coefs[j][i]; // coefficient correspondant à la valeur sous le pivot
            for (int k = i; k < U->columns; k++)
            { // colonne par colonne
                U->coefs[j][k] -= coeff / U->coefs[i][i] * U->coefs[i][k];
            }
            // Affectation de coeff/A[i][i] à L
            L->coefs[j][i] = coeff / U->coefs[i][i];
        }
    }
}

int nextPowerOfTwo(int n) {
    int power = 1;
    while (power < n) {
        power <<= 1;
    }
    return power;
}

matrix *ajusteMatrix(matrix *A) {
    int newSize = nextPowerOfTwo(A->rows > A->columns ? A->rows : A->columns);
    matrix *padded = creeMatrix(newSize, newSize);

    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            padded->coefs[i][j] = A->coefs[i][j];
        }
    }

    for (int i = A->rows; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            padded->coefs[i][j] = 0;
        }
    }
    for (int i = 0; i < A->rows; i++) {
        for (int j = A->columns; j < newSize; j++) {
            padded->coefs[i][j] = 0;
        }
    }

    return padded;
}

matrix *extractResult(matrix *paddedResult, int originalRows, int originalColumns) {
    matrix *result = creeMatrix(originalRows, originalColumns);

    for (int i = 0; i < originalRows; i++) {
        for (int j = 0; j < originalColumns; j++) {
            result->coefs[i][j] = paddedResult->coefs[i][j];
        }
    }

    return result;
}

matrix *strassenRecursive(matrix *A, matrix *B, int limite) {
    if (A->rows <= limite || A->columns <= limite || B->rows <= limite || B->columns <= limite) {
        return naiveMultMat(A, B);
    }

    int size = A->rows;
    int halfSize = size / 2;

    matrix *M1 = strassenRecursive(
        subMatrixAddition(A, A, 0, 0, halfSize - 1, halfSize - 1, halfSize, halfSize, size - 1, size - 1),          
        subMatrixAddition(B, B, 0, 0, halfSize - 1, halfSize - 1, halfSize, halfSize, size - 1, size - 1), limite); 

    matrix *M2 = strassenRecursive(
        subMatrixAddition(A, A, halfSize, 0, size - 1, halfSize - 1, halfSize, halfSize, size - 1, size - 1), 
        subMatrix(B, 0, 0, halfSize - 1, halfSize - 1), limite);                                              

    matrix *M3 = strassenRecursive(
        subMatrix(A, 0, 0, halfSize - 1, halfSize - 1),                                                                   
        subMatrixSubtraction(B, B, 0, halfSize, halfSize - 1, size - 1, halfSize, halfSize, size - 1, size - 1), limite); 

    matrix *M4 = strassenRecursive(
        subMatrix(A, halfSize, halfSize, size - 1, size - 1),                                                       
        subMatrixSubtraction(B, B, halfSize, 0, size - 1, halfSize - 1, 0, 0, halfSize - 1, halfSize - 1), limite); 

    matrix *M5 = strassenRecursive(
        subMatrixAddition(A, A, 0, 0, halfSize - 1, halfSize - 1, 0, halfSize, halfSize - 1, size - 1), 
        subMatrix(B, halfSize, halfSize, size - 1, size - 1), limite);                                  

    matrix *M6 = strassenRecursive(
        subMatrixSubtraction(A, A, halfSize, 0, size - 1, halfSize - 1, 0, 0, halfSize - 1, halfSize - 1),       
        subMatrixAddition(B, B, 0, 0, halfSize - 1, halfSize - 1, 0, halfSize, halfSize - 1, size - 1), limite); 

    matrix *M7 = strassenRecursive(
        subMatrixSubtraction(A, A, 0, halfSize, halfSize - 1, size - 1, halfSize, halfSize, size - 1, size - 1),       
        subMatrixAddition(B, B, halfSize, 0, size - 1, halfSize - 1, halfSize, halfSize, size - 1, size - 1), limite); 

    matrix *result = creeMatrix(size, size);

    for (int i = 0; i < halfSize; i++) {
        for (int j = 0; j < halfSize; j++) {
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

    return result;
}

matrix *strassen(matrix *A, matrix *B, int limite) {
    matrix *Aajuste = ajusteMatrix(A);
    matrix *Bajuste = ajusteMatrix(B);

    matrix *paddedResult = strassenRecursive(Aajuste, Bajuste, limite);

    matrix *result = extractResult(paddedResult, A->rows, B->columns);

    freeMatrix(*Aajuste);
    freeMatrix(*Bajuste);
    freeMatrix(*paddedResult);

    return result;
}

int main(int argc, char const *argv[])
{

    //int n = 3;

    matrix *A = creeMatrix(3,2);
    matrix *B=creeMatrix(2,3);

    double a_values[3][2] = {{1, 3}, {2,4}, {5,4}};
    double b_values[2][3] = {{5,1,3}, {2,3,2}};

    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            A->coefs[i][j] = a_values[i][j];
        }
    }

    for (int i = 0; i < B->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
            B->coefs[i][j] = b_values[i][j];
        }
    }

    printMatrix(*A);
    printf("\n");
    printMatrix(*B);
    printf("\n");


    matrix* C = strassen(A,B,1);
    printf("\n");

    printMatrix(*C);


    return 0;
}
