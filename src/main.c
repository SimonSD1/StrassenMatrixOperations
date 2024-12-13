// Simon Sepiol-Duchemin Joshua Setia

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/matrix.h"
#include "../include/strassen.h"
#include "../include/LU.h"
#include "../include/analyse.h"



int main(int argc, char const *argv[])
{
/*    int n =2*2*2*2*2*2*2*2;

    matrix *A = creeMatrix(n, n);
    matrix *B = creeMatrix(n, n);
    matrix *C = creeMatrix(n, n);

    matrix *P = creeMatrix(n, n);
    matrix *L = creeMatrix(n, n);
    matrix *U = creeMatrix(n, n);
    matrix *Q = creeMatrix(n, n);

    double M[16] = {
    0, 1, 3, 1,
    0, 1, 1, 5,
    2, 3, 4, 1, 
    1, 2, 1, 1};

    srand(time(NULL));

    for (int i = 0; i < A->rows; i++)
    {
        for (int j = 0; j < A->columns; j++)
        {
            A->coefs[i][j] = (float)rand()/((float)RAND_MAX/1);
        }
    }

    for (int i = 0; i < B->rows; i++)
    {
        for (int j = 0; j < B->columns; j++)
        {
            B->coefs[i][j] = rand() % 10;
        }
    }

    clock_t start = clock();
    strassen_inverse_recursive_strassen(A, B, 50);
    clock_t end = clock();

    double temps = end - start;

    start = clock();
    strassen_inverse_recursive_naive(A, B);
    end = clock();

    double temps2 = end - start;

    printf("temps=%lf , %lf\n", temps, temps2);

    naiveMultMat(A, B, P);

    printf("valide = %d\n",testIdentity(P));*/
    printf("Multiplication naive petites tailles, ");
    analysePetitesTailles(tpsMoy_MultNaive, 100, 64);
    printf("\nMultiplication strassen petites tailles, ");
    analysePetitesTailles(tpsMoy_MultStrassen, 100, 64);

    printf("\n\nMultiplication naive grandes tailles, ");
    analyseGrandesTailles(tpsMoy_MultNaive, 30, 11);
    printf("\nMultiplication strassen grandes tailles, ");
    analyseGrandesTailles(tpsMoy_MultStrassen, 30, 11);

    printf("\n\nInversion PLUQ, ");
    analyseGrandesTailles(tpsMoy_InversePLUQ, 30, 11);
    printf("\nInversion strassen (avec multiplication naive), ");
    analyseGrandesTailles(tpsMoy_InverseStrassenNaive, 30, 11);
    printf("\nInversion strassen (avec multiplication strassen), ");
    analyseGrandesTailles(tpsMoy_InverseStrassenStrassen, 30, 11);
    return 0;
}
