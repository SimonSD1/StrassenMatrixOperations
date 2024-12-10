#ifndef MATRIX_H
#define MATRIX_H

typedef struct matrix
{
    double **coefs;
    int columns;

    int rows;
} matrix;

matrix *creeMatrix(int rows, int columns);
void freeMatrix(matrix m);
void printMatrix(matrix A);
void naiveMultMat(matrix *A, matrix *B, matrix *result);
void matrice_add(matrix *A, matrix *B, matrix *result);
void subMatrixAddition(matrix *A, matrix *B, matrix *result, int startRowA, int startColA, int endRowA, int endColA, int startRowB, int startColB, int endRowB, int endColB);
void matrice_substract(matrix *A, matrix *B, matrix *result);
void subMatrixSubtraction(matrix *A, matrix *B, matrix *result, int row1_start, int col1_start, int row1_end, int col1_end, int row2_start, int col2_start, int row2_end, int col2_end);
void fillSubMatrix(matrix *original, matrix *result, int startRow, int startCol);
void identity(matrix *A);
void copyMatrix(matrix *source, matrix *destination);
void extractColumn(matrix *A, matrix *result, int col);
void setColumn(matrix *A, matrix *col, int num);
void solveUpperTriangular(matrix *U, matrix *B, matrix *result);
void solveLowerTriangular(matrix *L, matrix *B, matrix *result);
void negativeMatrix(matrix *A);
void fillBigMatrix(matrix *Big, matrix *small, int startRow, int startCol);
void find_greatest_in_sub_matrix(matrix *A, int depart, int *facteur_ligne, int *facteur_colonne);
double determinant(matrix *A);
void transposeMatrix(matrix *A, matrix* result);
int testIdentity(matrix*A);
#endif
