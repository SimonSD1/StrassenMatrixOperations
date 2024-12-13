// Simon Sepiol-Duchemin Joshua Setia

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/matrix.h"
#include "../include/strassen.h"
#include "../include/LU.h"


void fillMatrixRandom(matrix *M)
{
    for (int i = 0; i < M->rows; i++)
    {
        for (int j = 0; j < M->columns; j++)
        {
            M->coefs[i][j] = ((float)rand() / ((float)RAND_MAX)) * 2 - 1;  // Intervalle [-1, 1]
        }
    }
}




double tpsMoy_MultNaive(int nbTests, int taille)
{
    matrix *A = creeMatrix(taille, taille);
    matrix *B = creeMatrix(taille, taille);
    matrix *C = creeMatrix(taille, taille);

    clock_t start, end;
    double tempsTotal = 0.0;
    for (int i=0; i < nbTests; i++)
    {
        fillMatrixRandom(A);
        fillMatrixRandom(B);

        start = clock();
        naiveMultMat(A, B, C);
        end = clock();

        tempsTotal += (double)(end - start);
    }
    
    freeMatrix(*A);
    freeMatrix(*B);
    freeMatrix(*C);
    return (double)(tempsTotal / nbTests);
}


double tpsMoy_MultStrassen(int nbTests, int taille)
{
    matrix *A = creeMatrix(taille, taille);
    matrix *B = creeMatrix(taille, taille);
    matrix *C = creeMatrix(taille, taille);

    clock_t start, end;
    double tempsTotal = 0.0;
    for (int i=0; i < nbTests; i++)
    {
        fillMatrixRandom(A);
        fillMatrixRandom(B);

        start = clock();
        strassen(A, B, C, 200);
        end = clock();

        tempsTotal += (double)(end - start);
    }
    
    freeMatrix(*A);
    freeMatrix(*B);
    freeMatrix(*C);
    return (double)(tempsTotal / nbTests);
}





double tpsMoy_InversePLUQ(int nbTests, int taille)
{
    matrix *A = creeMatrix(taille, taille);
    matrix *B = creeMatrix(taille, taille);

    clock_t start, end;
    double tempsTotal = 0.0;
    for (int i=0; i < nbTests; i++)
    {
        fillMatrixRandom(A);

        start = clock();
        inverse_PLUQ(A, B);
        end = clock();

        tempsTotal += (double)(end - start);
    }
    
    freeMatrix(*A);
    freeMatrix(*B);
    return (double)(tempsTotal / nbTests);
}


double tpsMoy_InverseStrassenNaive(int nbTests, int taille)
{
    matrix *A = creeMatrix(taille, taille);
    matrix *B = creeMatrix(taille, taille);

    clock_t start, end;
    double tempsTotal = 0.0;
    for (int i=0; i < nbTests; i++)
    {
        fillMatrixRandom(A);

        start = clock();
        strassen_inverse_recursive_naive(A, B);
        end = clock();

        tempsTotal += (double)(end - start);
    }
    
    freeMatrix(*A);
    freeMatrix(*B);
    return (double)(tempsTotal / nbTests);
}


double tpsMoy_InverseStrassenStrassen(int nbTests, int taille)
{
    matrix *A = creeMatrix(taille, taille);
    matrix *B = creeMatrix(taille, taille);

    clock_t start, end;
    double tempsTotal = 0.0;
    for (int i=0; i < nbTests; i++)
    {
        fillMatrixRandom(A);

        start = clock();
        strassen_inverse_recursive_strassen(A, B, 200);
        end = clock();

        tempsTotal += (double)(end - start);
    }
    
    freeMatrix(*A);
    freeMatrix(*B);
    return (double)(tempsTotal / nbTests);
}





void analyseMultNaive(double (*func)(int, int), int nbTests, int tailleMax)
{
    printf("temps moyen pour chaque taille :\n[");
    for(int i=1; i < tailleMax; i++)
    {
        printf("%lf, ", func(nbTests, 1<<i));
    }
    printf("]\n");
}