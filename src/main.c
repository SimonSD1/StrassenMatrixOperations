#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/matrix.h"
#include "../include/strassen.h"
#include "../include/LU.h"
#include "../include/inverse.h"

int main(int argc, char const *argv[]) {
    int n = 3;

    matrix *A = creeMatrix(n, n);
    matrix *B = creeMatrix(n, n);

    srand(time(NULL));

    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            A->coefs[i][j] = i * A->rows + j + 1;
        }
    }

    for (int i = 0; i < B->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
            B->coefs[i][j] = i + j;
        }
    }

    printf("A=\n");
    printMatrix(*A);
    printf("\n");

    int facl;
    int facc;

    find_greatest_in_sub_matrix(A, 4, &facl, &facc);

    printf("facl=%d facc=%d\n", facl, facc);

    matrix *P = creeMatrix(n, n);
    matrix *L = creeMatrix(n, n);
    matrix *U = creeMatrix(n, n);
    matrix *Q = creeMatrix(n, n);
    matrix *R = creeMatrix(n, n);
    matrix *R1 = creeMatrix(n, n);
    matrix *R2 = creeMatrix(n, n);


    //clock_t start = clock();
    //PLUQ(A, P, L, U, Q);
    //clock_t end = clock();
//
    //printf("temps pris = %ld\n", end - start);
//
    //printf("P=\n");
    //printMatrix(*P);
//
    //printf("L=\n");
    //printMatrix(*L);
//
    //printf("U=\n");
    //printMatrix(*U);
//
    //printf("Q=\n");
    //printMatrix(*Q);
//
    //printf("\n");
//
    //naiveMultMat(P, L, R);
    //printMatrix(*R);
    //naiveMultMat(R, U, R1);
    //printMatrix(*R);
    //naiveMultMat(R1, Q, R2);
//
    //printf("resultat main\n");
    //printMatrix(*R2);

    matrix * C = creeMatrix(n,n);

    strassen(A,B,C,200);

    printMatrix(*C);

    printf("\n");

    naiveMultMat(A,B,R2);

    printMatrix(*R2);

    freeMatrix(*A);
    freeMatrix(*B);
    freeMatrix(*P);
    freeMatrix(*L);
    freeMatrix(*U);
    freeMatrix(*Q);

    return 0;
}
