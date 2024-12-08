#include <stdlib.h>
#include <stdio.h>
#include "../include/matrix.h"




matrix *creeMatrix(int rows, int columns) {
    matrix *m = malloc(sizeof(matrix));
    m->columns = columns;
    m->rows = rows;
    m->coefs = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
        
        m->coefs[i] = malloc(columns * sizeof(double));

    }
    return m;
}

void freeMatrix(matrix m) {
    for (int i = 0; i < m.rows; i++) {
        free(m.coefs[i]);
    }
    free(m.coefs);
}

void printMatrix(matrix A) {
    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < A.columns; j++) {
            printf("%lf ", A.coefs[i][j]);
        }
        printf("\n");
    }
}

void naiveMultMat(matrix *A, matrix *B, matrix *result) {
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
            result->coefs[i][j] = 0;
            for (int k = 0; k < A->columns; k++) {
                result->coefs[i][j] += A->coefs[i][k] * B->coefs[k][j];
            }
        }
    }
}

void matrice_add(matrix *A, matrix *B, matrix *result) {
    if (A->rows != B->rows || A->columns != B->columns) {
        printf("impossible addition");
        return;
    }
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            result->coefs[i][j] = A->coefs[i][j] + B->coefs[i][j];
        }
    }
}

void subMatrixAddition(matrix *A, matrix *B, matrix *result, int startRowA, int startColA, int endRowA, int endColA, int startRowB, int startColB, int endRowB, int endColB) {
    int rowsA = endRowA - startRowA + 1;
    int colsA = endColA - startColA + 1;
    int rowsB = endRowB - startRowB + 1;
    int colsB = endColB - startColB + 1;
    if (rowsA != rowsB || colsA != colsB) {
        printf("impossible addition\n");
        return;
    }
    if (endRowA >= A->rows || endColA >= A->columns || startRowA < 0 || startColA < 0 || endRowB >= B->rows || endColB >= B->columns || startRowB < 0 || startColB < 0) {
        printf("impossible addition\n");
        return;
    }
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsA; j++) {
            result->coefs[i][j] = A->coefs[startRowA + i][startColA + j] + B->coefs[startRowB + i][startColB + j];
        }
    }
}

void matrice_substract(matrix *A, matrix *B, matrix *result) {
    if (A->rows != B->rows || A->columns != B->columns) {
        printf("impossible soustraction");
        return;
    }
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            result->coefs[i][j] = A->coefs[i][j] - B->coefs[i][j];
        }
    }
}

void subMatrixSubtraction(matrix *A, matrix *B, matrix *result, int row1_start, int col1_start, int row1_end, int col1_end, int row2_start, int col2_start, int row2_end, int col2_end) {
    int rows = row1_end - row1_start + 1;
    int cols = col1_end - col1_start + 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result->coefs[i][j] = A->coefs[row1_start + i][col1_start + j] - B->coefs[row2_start + i][col2_start + j];
        }
    }
}

void subMatrix(matrix *original, matrix *result, int startRow, int startCol, int endRow, int endCol) {
    int newRows = endRow - startRow + 1;
    int newCols = endCol - startCol + 1;
    for (int i = 0; i < newRows; i++) {
        for (int j = 0; j < newCols; j++) {
            result->coefs[i][j] = original->coefs[startRow + i][startCol + j];
        }
    }
}

void identity(matrix *A) {
    for (int i = 0; i < A->columns; i++) {
        A->coefs[i][i] = 1;
    }
}

void copyMatrix(matrix *source, matrix *destination) {
    for (int i = 0; i < source->rows; i++) {
        for (int j = 0; j < source->columns; j++) {
            destination->coefs[i][j] = source->coefs[i][j];
        }
    }
}

void extractColumn(matrix *A, matrix *result, int col) {
    if (col < 0 || col > A->columns) {
        printf("impossible d'extraire la colonne");
        return;
    }
    for (int i = 0; i < A->rows; i++) {
        result->coefs[i][0] = A->coefs[i][col];
    }
}

void setColumn(matrix *A, matrix *col, int num) {
    for (int i = 0; i < A->rows; i++) {
        A->coefs[i][num] = col->coefs[i][0];
    }
}

void solveUpperTriangular(matrix *U, matrix *B, matrix *result) {
    for (int i = U->rows - 1; i >= 0; i--) {
        result->coefs[i][0] = B->coefs[i][0];
        for (int j = i + 1; j < U->rows; j++) {
            result->coefs[i][0] -= U->coefs[i][j] * result->coefs[j][0];
        }
        result->coefs[i][0] /= U->coefs[i][i];
    }
}

void solveLowerTriangular(matrix *L, matrix *B, matrix *result) {
    for (int i = 0; i < L->rows; i++) {
        result->coefs[i][0] = B->coefs[i][0];
        for (int j = 0; j < i; j++) {
            result->coefs[i][0] -= L->coefs[i][j] * result->coefs[j][0];
        }
        result->coefs[i][0] /= L->coefs[i][i];
    }
}

void negativeMatrix(matrix *A) {
    int col = A->columns;
    int rows = A->rows;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < col; j++) {
            A->coefs[i][j] = -A->coefs[i][j];
        }
    }
}

void fillSubmatrix(matrix *A, matrix *B, int startRow, int startCol) {
    for (int i = 0; i < B->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
            A->coefs[startRow + i][startCol + j] = B->coefs[i][j];
        }
    }
}

void find_greatest_in_sub_matrix(matrix *A, int depart, int *facteur_ligne, int *facteur_colonne) {
    int indice = 0;
    double biggest = A->coefs[A->rows - 1][A->columns - 1];
    *facteur_ligne = A->rows - 1;
    *facteur_colonne = A->columns - 1;
    for (int i = depart; i < A->rows; i++) {
        for (int j = depart; j < A->columns; j++) {
            if (A->coefs[i][j] > biggest) {
                biggest = A->coefs[i][j];
                *facteur_ligne = i;
                *facteur_colonne = j;
            }
        }
    }
}
