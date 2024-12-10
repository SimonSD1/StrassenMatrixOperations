// Simon Sepiol-Duchemin Joshua Setia

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/matrix.h"
#include "../include/strassen.h"
#include "../include/LU.h"
#include "../include/inverse.h"

int main(int argc, char const *argv[])
{
    int n =4;

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
            A->coefs[i][j] = M[i*A->rows+j];
        }
    }

    for (int i = 0; i < B->rows; i++)
    {
        for (int j = 0; j < B->columns; j++)
        {
            B->coefs[i][j] = rand() % 10;
        }
    }

    printMatrix(*A);
    printf("\ndet=%lf\n",determinant(A));
    clock_t start = clock();
    strassen_inverse_recursive_strassen(A, B);
    clock_t end = clock();

    double temps = end - start;

    start = clock();
    // strassen_inverse_recursive_naive(A, B);
    end = clock();

    double temps2 = end - start;

    printf("\temps=%lf , %lf\n", temps, temps2);

    naiveMultMat(A, B, P);

    printMatrix(*P);

    printf("valide = %d\n",testIdentity(P));

    return 0;
}
