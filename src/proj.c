#include <stdlib.h>
#include <stdio.h>
#include "projet.h"

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

matrix creeMatrix(int rows, int columns)
{
    matrix m;
    m.columns = columns;
    m.rows = columns;
    m.coefs = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++)
    {
        m.coefs[i] = malloc(columns * sizeof(double));
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            m.coefs[i][j] = 0;
        }
    }
    return m;
}


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
{
    for (int i = 0; i < A.rows; i++)
    {
        for (int j = 0; j < B.rows; j++)
        {
            result.coefs[i][j] = 0;
            for (int k = 0; k < A.rows; k++)
            {
                result.coefs[i][j] += A.coefs[i][k] * B.coefs[k][j];
            }
        }
    }
}

void strassen(matrix A, matrix B, matrix C){
    return;
}


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
}
