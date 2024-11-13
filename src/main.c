#include <stdlib.h>
#include <stdio.h>
#include "projet.h"


int main(int argc, char const *argv[])
{
    matrix A = creeMatrix(4,4);
    /*A.coefs[0][0] = 4;
    A.coefs[0][1] = 4;
    A.coefs[0][2] = 8;
    A.coefs[0][3] = 1;
    A.coefs[1][0] = 2;
    A.coefs[1][1] = 8;
    A.coefs[1][2] = 7;
    A.coefs[1][3] = 1;
    A.coefs[2][0] = 1;
    A.coefs[2][1] = 3;
    A.coefs[2][2] = 6;
    A.coefs[2][3] = 1;
    A.coefs[3][0] = -4;
    A.coefs[3][1] = 6;
    A.coefs[3][2] = 5;
    A.coefs[3][3] = 1;*/
    remplirMatrixManuel(A);

    printMatrix(A);
    matrix L = creeMatrix(4,4);
    matrix U = creeMatrix(4,4);
    LU(A,L,U);
    printMatrix(L);
    printMatrix(U);
    freeMatrix(A);
    freeMatrix(L);
    freeMatrix(U);
    return 0;
}