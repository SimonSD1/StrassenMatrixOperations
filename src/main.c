#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/matrix.h"
#include "../include/strassen.h"
#include "../include/LU.h"
#include "../include/inverse.h"

int main(int argc, char const *argv[])
{
    int n = 5;

    matrix *A = creeMatrix(n, n);
    matrix *B = creeMatrix(n, n);
    matrix *C = creeMatrix(n, n);

    matrix *P = creeMatrix(n, n);
    matrix *L = creeMatrix(n, n);
    matrix *U = creeMatrix(n, n);
    matrix *Q = creeMatrix(n, n);

    double M[16] = {0, 1, 1, 1, 1, 0, 1, 1, 2, 3, 0, 1, 1, 2, 0, 1};

    srand(time(NULL));

    for (int i = 0; i < A->rows; i++)
    {
        for (int j = 0; j < A->columns; j++)
        {
            A->coefs[i][j] = rand()%10;
        }
    }

    for (int i = 0; i < B->rows; i++)
    {
        for (int j = 0; j < B->columns; j++)
        {
            B->coefs[i][j] = rand()%10;
        }
    }

    clock_t start = clock();
    naiveMultMat(A,B,P);
    clock_t end = clock();

    double naive = end-start;

    start=clock();
    strassen(A,B,L,200);
    end=clock();

    double stra = end-start;

    printf("\nnaive=%lf\n",naive);
    printMatrix(*P);


    printf("\nstras=%lf\n",stra);
    printMatrix(*L);

    return 0;
}
