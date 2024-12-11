// Simon Sepiol-Duchemin Joshua Setia

#include <stdio.h>
#include "../include/LU.h"
#include "../include/matrix.h"
#include <math.h>

void LU(matrix *A, matrix *L, matrix *U)
{
    identity(L);
    copyMatrix(A, U);
    for (int i = 0; i < U->rows; i++)
    {
        if (U->coefs[i][i] == 0)
        {
            printf("LU impossible pivot 0\n");
            return;
        }
        for (int j = i + 1; j < U->rows; j++)
        {
            double coeff = U->coefs[j][i];
            for (int k = i; k < U->columns; k++)
            {
                U->coefs[j][k] -= coeff / U->coefs[i][i] * U->coefs[i][k];
            }
            L->coefs[j][i] = coeff / U->coefs[i][i];
        }
    }
}

void findMaxElement(matrix *M, int start, int *maxRow, int *maxCol)
{
    double maxVal = 0.0;
    *maxRow = start;
    *maxCol = start;

    for (int i = start; i < M->rows; i++)
    {
        for (int j = start; j < M->columns; j++)
        {
            if (fabs(M->coefs[i][j]) > maxVal)
            {
                maxVal = fabs(M->coefs[i][j]);
                *maxRow = i;
                *maxCol = j;
            }
        }
    }
}


int PLUQ(matrix *A, matrix *P, matrix *L, matrix *U, matrix *Q)
{
    int size = A->rows;
    int permut = 0;

    copyMatrix(A, U);
    identity(P);
    identity(Q);
    identity(L);

    for (int i = 0; i < size; i++)
    {
        int maxRow, maxCol;
        findMaxElement(U, i, &maxRow, &maxCol);

        if (U->coefs[maxRow][maxCol] == 0)
        {
            break;
        }

        if (maxRow != i)
        {
            
            swapColumns(P,i,maxRow);
            swapRows(L,i,maxRow);
            swapColumns(L,i,maxRow);
            swapRows(U,i,maxRow);

            permut++;
        }

        if (maxCol != i)
        {
           swapColumns(U,i,maxCol);
           swapRows(Q,i,maxCol);
            
            permut++;
        }

        for (int j = i + 1; j < size; j++)
        {
            double factor = U->coefs[j][i] / U->coefs[i][i];
            L->coefs[j][i] = factor;

            for (int k = i; k < size; k++)
            {
                U->coefs[j][k] -= factor * U->coefs[i][k];
            }
        }
    }
    return permut;
}



void inverse_PLUQ(matrix *A, matrix *result) {
    matrix *L = creeMatrix(A->rows, A->columns);
    matrix *U = creeMatrix(A->rows, A->columns);
    matrix *P = creeMatrix(A->rows, A->columns);
    matrix *Q = creeMatrix(A->rows, A->columns);
    matrix *I = creeMatrix(A->rows, A->columns);
    
    identity(I);
    PLUQ(A,P,L,U,Q);
    
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
