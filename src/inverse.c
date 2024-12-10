// Simon Sepiol-Duchemin Joshua Setia

#include <stdio.h>
#include "../include/inverse.h"
#include "../include/matrix.h"
#include "../include/LU.h"


void inverse_PLUQ(matrix *A, matrix *result) {
    matrix *L = creeMatrix(A->rows, A->columns);
    matrix *U = creeMatrix(A->rows, A->columns);
    matrix *P = creeMatrix(A->rows, A->columns);
    matrix *Q = creeMatrix(A->rows, A->columns);
    matrix *I = creeMatrix(A->rows, A->columns);
    
    identity(I);
    PLUQ(A,P,L,U,Q);
    
    printMatrix(*L);
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

    matrix* P_inverse= creeMatrix(A->rows,A->columns);
    matrix* Q_inverse= creeMatrix(A->rows,A->columns);

    transposeMatrix(P,P_inverse);
    transposeMatrix(Q,Q_inverse);

    // result = u-1 * l-1
    naiveMultMat(Q_inverse,result,U);
    naiveMultMat(U,P_inverse,result);

    
    freeMatrix(*L);
    freeMatrix(*U);
    freeMatrix(*I);
}
