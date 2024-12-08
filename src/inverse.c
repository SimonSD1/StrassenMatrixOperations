#include <stdio.h>
#include "../include/inverse.h"
#include "../include/matrix.h"
#include "../include/LU.h"

void inverse_LU(matrix *A, matrix *result) {
    matrix *L = creeMatrix(A->rows, A->columns);
    matrix *U = creeMatrix(A->rows, A->columns);
    matrix *I = creeMatrix(A->rows, A->columns);
    
    identity(I);
    LU(A, L, U);
    for (int i = 0; i < A->rows; i++) {
        matrix *y = creeMatrix(A->rows, 1);
        matrix *x = creeMatrix(A->rows, 1);
        extractColumn(I, y, i);
        solveLowerTriangular(L, y, y);
        solveUpperTriangular(U, y, x);
        setColumn(result, x, i);
        freeMatrix(*y);
        freeMatrix(*x);
    }
    freeMatrix(*L);
    freeMatrix(*U);
    freeMatrix(*I);
}
