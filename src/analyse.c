// Simon Sepiol-Duchemin Joshua Setia

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
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




double tpsMoy_MultNaive(int nbTests, int taille, int tpsMem)
{
    matrix *A = creeMatrix(taille, taille);
    matrix *B = creeMatrix(taille, taille);
    matrix *C = creeMatrix(taille, taille);

    clock_t start, end;
    double tempsTotal = 0.0;
    double memTotal = 0.0;
    for (int i=0; i < nbTests; i++)
    {
        fillMatrixRandom(A);
        fillMatrixRandom(B);

        struct mallinfo2 mem_before = mallinfo2();

        start = clock();
        naiveMultMat(A, B, C);
        end = clock();

        struct mallinfo2 mem_after = mallinfo2();

        tempsTotal += (double)(end - start);
        memTotal += (double)(mem_after.uordblks - mem_before.uordblks);
    }
    
    freeMatrix(*A);
    freeMatrix(*B);
    freeMatrix(*C);
    //si tpsMem == 1, on renvoie la quantité de mémoire utilisée
    if(tpsMem)
        return (double)(memTotal / nbTests);
    //on renvoie le temps d'exécution sinon
    return (double)(tempsTotal / nbTests);
}


double tpsMoy_MultStrassen(int nbTests, int taille, int tpsMem, int limite)
{
    matrix *A = creeMatrix(taille, taille);
    matrix *B = creeMatrix(taille, taille);
    matrix *C = creeMatrix(taille, taille);

    clock_t start, end;
    double tempsTotal = 0.0;
    double memTotal = 0.0;
    for (int i=0; i < nbTests; i++)
    {
        fillMatrixRandom(A);
        fillMatrixRandom(B);

        struct mallinfo2 mem_before = mallinfo2();

        start = clock();
        strassen(A, B, C, limite);
        end = clock();

        struct mallinfo2 mem_after = mallinfo2();

        tempsTotal += (double)(end - start);
        memTotal += (double)(mem_after.uordblks - mem_before.uordblks);
    }
    
    freeMatrix(*A);
    freeMatrix(*B);
    freeMatrix(*C);
    if(tpsMem)
        return (double)(memTotal / nbTests);
    return (double)(tempsTotal / nbTests);
}





double tpsMoy_InversePLUQ(int nbTests, int taille, int tpsMem)
{
    matrix *A = creeMatrix(taille, taille);
    matrix *B = creeMatrix(taille, taille);

    clock_t start, end;
    double tempsTotal = 0.0;
    double memTotal = 0.0;
    for (int i=0; i < nbTests; i++)
    {
        fillMatrixRandom(A);

        struct mallinfo2 mem_before = mallinfo2();

        start = clock();
        inverse_PLUQ(A, B);
        end = clock();

        struct mallinfo2 mem_after = mallinfo2();

        tempsTotal += (double)(end - start);
        memTotal += (double)(mem_after.uordblks - mem_before.uordblks);
    }
    
    freeMatrix(*A);
    freeMatrix(*B);
    if(tpsMem)
        return (double)(memTotal / nbTests);
    return (double)(tempsTotal / nbTests);
}


double tpsMoy_InverseStrassenNaive(int nbTests, int taille, int tpsMem)
{
    matrix *A = creeMatrix(taille, taille);
    matrix *B = creeMatrix(taille, taille);

    clock_t start, end;
    double tempsTotal = 0.0;
    double memTotal = 0.0;
    for (int i=0; i < nbTests; i++)
    {
        fillMatrixRandom(A);

        struct mallinfo2 mem_before = mallinfo2();

        start = clock();
        strassen_inverse_recursive_naive(A, B);
        end = clock();

        struct mallinfo2 mem_after = mallinfo2();

        tempsTotal += (double)(end - start);
        memTotal += (double)(mem_after.uordblks - mem_before.uordblks);
    }
    
    freeMatrix(*A);
    freeMatrix(*B);
    if(tpsMem)
        return (double)(memTotal / nbTests);
    return (double)(tempsTotal / nbTests);
}


double tpsMoy_InverseStrassenStrassen(int nbTests, int taille, int tpsMem, int limite)
{
    matrix *A = creeMatrix(taille, taille);
    matrix *B = creeMatrix(taille, taille);

    clock_t start, end;
    double tempsTotal = 0.0;
    double memTotal = 0.0;
    for (int i=0; i < nbTests; i++)
    {
        fillMatrixRandom(A);

        struct mallinfo2 mem_before = mallinfo2();

        start = clock();
        strassen_inverse_recursive_strassen(A, B, limite);
        end = clock();

        struct mallinfo2 mem_after = mallinfo2();

        tempsTotal += (double)(end - start);
        memTotal += (double)(mem_after.uordblks - mem_before.uordblks);
    }
    
    freeMatrix(*A);
    freeMatrix(*B);
    if(tpsMem)
        return (double)(memTotal / nbTests);
    return (double)(tempsTotal / nbTests);
}




void analysePetitesTailles(double (*func)(int, int, int), int nbTests, int tailleMax, int tpsMem)
{
    if(tpsMem)
        printf("mémoire (allocations) utilisée pour chaque taille :\n[");
    else
        printf("temps moyen pour chaque taille :\n[");
    for(int i=2; i <= tailleMax; i++)
    {
        printf("%lf, ", func(nbTests, i, tpsMem));  //matrices de tailles 2 à tailleMax
    }
    printf("]\n");
}

void analysePetitesTaillesStrassen(double (*func)(int, int, int, int), int nbTests, int tailleMax, int tpsMem, int limite)
{
    if(tpsMem)
        printf("mémoire (allocations) utilisée pour chaque taille :\n[");
    else
        printf("temps moyen pour chaque taille :\n[");
    for(int i=2; i <= tailleMax; i++)
    {
        printf("%lf, ", func(nbTests, i, tpsMem, limite));  //matrices de tailles 2 à tailleMax
    }
    printf("]\n");
}


void analyseGrandesTailles(double (*func)(int, int, int), int nbTests, int tailleMax, int tpsMem)
{
    if(tpsMem)
        printf("mémoire (allocations) utilisée pour chaque taille :\n[");
    else
        printf("temps moyen pour chaque taille :\n[");
    for(int i=1; i <= tailleMax; i++)
    {
        printf("%lf, ", func(nbTests, 1<<i, tpsMem));   //matrices de tailles en puissance de 2
    }
    printf("]\n");
}

void analyseGrandesTaillesStrassen(double (*func)(int, int, int, int), int nbTests, int tailleMax, int tpsMem, int limite)
{
    if(tpsMem)
        printf("mémoire (allocations) utilisée pour chaque taille :\n[");
    else
        printf("temps moyen pour chaque taille :\n[");
    for(int i=1; i <= tailleMax; i++)
    {
        printf("%lf, ", func(nbTests, 1<<i, tpsMem, limite));   //matrices de tailles en puissance de 2
    }
    printf("]\n");
}