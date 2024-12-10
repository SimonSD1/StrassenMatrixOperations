#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/strassen.h"
#include "../include/inverse.h"
#include "../include/matrix.h"

int nextPowerOfTwo(int n)
{
    int power = 1;
    while (power < n)
    {
        power <<= 1;
    }
    return power;
}

void ajusteMatrix(matrix *A, matrix *padded)
{
    int newSize = nextPowerOfTwo(A->rows > A->columns ? A->rows : A->columns);
    for (int i = 0; i < A->rows; i++)
    {
        for (int j = 0; j < A->columns; j++)
        {
            padded->coefs[i][j] = A->coefs[i][j];
        }
    }
    for (int i = A->rows; i < newSize; i++)
    {
        for (int j = 0; j < newSize; j++)
        {
            padded->coefs[i][j] = 0;
        }
    }
    for (int i = 0; i < A->rows; i++)
    {
        for (int j = A->columns; j < newSize; j++)
        {
            padded->coefs[i][j] = 0;
        }
    }
}

void extractResult(matrix *paddedResult, matrix *result, int originalRows, int originalColumns)
{
    for (int i = 0; i < originalRows; i++)
    {
        for (int j = 0; j < originalColumns; j++)
        {
            result->coefs[i][j] = paddedResult->coefs[i][j];
        }
    }
}

void strassenRecursive(matrix *A, matrix *B, matrix *result, int limite) {
    if (A->rows <= limite || A->columns <= limite || B->rows <= limite || B->columns <= limite) {
        naiveMultMat(A, B, result);
        return;
    }

    int size = A->rows;
    int halfSize = size / 2;

    matrix *M1 = creeMatrix(halfSize, halfSize);
    matrix *M2 = creeMatrix(halfSize, halfSize);
    matrix *M3 = creeMatrix(halfSize, halfSize);
    matrix *M4 = creeMatrix(halfSize, halfSize);
    matrix *M5 = creeMatrix(halfSize, halfSize);
    matrix *M6 = creeMatrix(halfSize, halfSize);
    matrix *M7 = creeMatrix(halfSize, halfSize);

    matrix *A11 = creeMatrix(halfSize, halfSize);
    matrix *A12 = creeMatrix(halfSize, halfSize);
    matrix *A21 = creeMatrix(halfSize, halfSize);
    matrix *A22 = creeMatrix(halfSize, halfSize);

    matrix *B11 = creeMatrix(halfSize, halfSize);
    matrix *B12 = creeMatrix(halfSize, halfSize);
    matrix *B21 = creeMatrix(halfSize, halfSize);
    matrix *B22 = creeMatrix(halfSize, halfSize);

    matrix *C11 = creeMatrix(halfSize, halfSize);
    matrix *C12 = creeMatrix(halfSize, halfSize);
    matrix *C21 = creeMatrix(halfSize, halfSize);
    matrix *C22 = creeMatrix(halfSize, halfSize);

    fillSubMatrix(A,A11,0,0);
    fillSubMatrix(A,A12,0,halfSize);
    fillSubMatrix(A,A21,halfSize,0);
    fillSubMatrix(A,A22,halfSize,halfSize);

    fillSubMatrix(B,B11,0,0);
    fillSubMatrix(B,B12,0,halfSize);
    fillSubMatrix(B,B21,halfSize,0);
    fillSubMatrix(B,B22,halfSize,halfSize);

    // M1 = (A11+A22)(B11+B22)
    matrice_add(A11,A22,C11);
    matrice_add(B11,B22,C12);
    strassenRecursive(C11,C12,M1,limite);

    // M2=(A21+A22)B11
    matrice_add(A21,A22,C11);
    strassenRecursive(C11,B11,M2,limite);

    // M3 = A11(B12-B22)
    matrice_substract(B12,B22,C11);
    strassenRecursive(A11,C11,M3,limite);

    // M4=A22(B21-B11)
    matrice_substract(B21,B11,C11);
    strassenRecursive(A22,C11,M4,limite);

    // M5=(A11+A12)B22
    matrice_add(A11,A12,C11);
    strassenRecursive(C11,B22,M5,limite);

    // M6 = (A21-A11)(B11+B12)
    matrice_substract(A21,A11,C11);
    matrice_add(B11,B12,C12);
    strassenRecursive(C11,C12,M6,limite);

    // M7 = (A12-A22)(B21+B22)
    matrice_substract(A12,A22,C11);
    matrice_add(B21,B22,C12);
    strassenRecursive(C11,C12,M7,limite);


    // on utilise plus A11 B11 etc

    // C11 = M1+M4-M5+M7
    matrice_add(M1,M4,A11);
    matrice_substract(A11,M5,A12);
    matrice_add(A12,M7,C11);

    // C12 = M3+M5
    matrice_add(M3,M5,C12);

    // C21 = M2+M4
    matrice_add(M2,M4,C21);

    // C22 = M1-M2+M3+M6
    matrice_substract(M1,M2,A11);
    matrice_add(A11,M3,A12);
    matrice_add(A12,M6,C22);

    fillBigMatrix(result,C11,0,0);
    fillBigMatrix(result,C12,0,halfSize);
    fillBigMatrix(result,C21,halfSize,0);
    fillBigMatrix(result,C22,halfSize,halfSize);

    freeMatrix(*M1);
    freeMatrix(*M2);
    freeMatrix(*M3);
    freeMatrix(*M4);
    freeMatrix(*M5);
    freeMatrix(*M6);
    freeMatrix(*M7);
    freeMatrix(*A11);
    freeMatrix(*A12);
    freeMatrix(*A21);
    freeMatrix(*A22);
    freeMatrix(*B11);
    freeMatrix(*B12);
    freeMatrix(*B21);
    freeMatrix(*B22);
    freeMatrix(*C11);
    freeMatrix(*C12);
    freeMatrix(*C21);
    freeMatrix(*C22);
}

void strassen(matrix *A, matrix *B, matrix *result, int limite) {
    int newSizeA = nextPowerOfTwo(A->rows > A->columns ? A->rows : A->columns);
    int newSizeB = nextPowerOfTwo(B->rows > B->columns ? B->rows : B->columns);

    matrix *Aajuste = creeMatrix(newSizeA,newSizeA);
    matrix *Bajuste = creeMatrix(newSizeB,newSizeB);

    fillBigMatrix(Aajuste,A,0,0);
    fillBigMatrix(Bajuste,B,0,0);


    matrix *paddedResult = creeMatrix(Aajuste->rows, Bajuste->columns);

    strassenRecursive(Aajuste, Bajuste,paddedResult, limite);

    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
            result->coefs[i][j] = paddedResult->coefs[i][j];
        }
    }

    freeMatrix(*Aajuste);
    freeMatrix(*Bajuste);
    freeMatrix(*paddedResult);
}

void createSubmatrix(matrix *A, matrix *result, int begin_row, int begin_col)
{
    for (int i = 0; i < result->rows; i++)
    {
        for (int j = 0; j < result->columns; j++)
        {
            result->coefs[i][j] = A->coefs[i + begin_row][j + begin_col];
        }
    }
}

// https://en.wikipedia.org/wiki/Invertible_matrix#Blockwise_inversion
void strassen_inverse_recursive_naive(matrix *A, matrix *result)
{   
    // pour eviter le cas 
    // {0, 1, 1, 1, 1, 0, 1, 1, 2, 3, 0, 1, 1, 2, 0, 1};
    if (A->columns == 2)
    {
        inverse_PLUQ(A,result);
        return;
    }

    int size = A->columns;

    matrix *a = creeMatrix(size / 2, size / 2);
    matrix *b = creeMatrix(size / 2, size / 2);
    matrix *c = creeMatrix(size / 2, size / 2);
    matrix *d = creeMatrix(size / 2, size / 2);
    createSubmatrix(A, a, 0, 0);
    createSubmatrix(A, b, 0, size / 2);
    createSubmatrix(A, c, size / 2, 0);
    createSubmatrix(A, d, size / 2, size / 2);

    matrix *e = creeMatrix(size / 2, size / 2);
    matrix *Z = creeMatrix(size / 2, size / 2);

    matrix *temp = creeMatrix(size / 2, size / 2);
    matrix *temp2 = creeMatrix(size / 2, size / 2);
    matrix *temp3 = creeMatrix(size / 2, size / 2);

    matrix *x = creeMatrix(size / 2, size / 2);
    matrix *y = creeMatrix(size / 2, size / 2);
    matrix *z = creeMatrix(size / 2, size / 2);
    matrix *t = creeMatrix(size / 2, size / 2);

    int det_a = determinant(a);
    int det_d = determinant(d);
    // si a est inversible

    if (fabs(det_a) > fabs(det_d))
    {

        // e=a⁻1
        strassen_inverse_recursive_naive(a, e);

        // Z=d-ceb
        naiveMultMat(e, b, temp);
        naiveMultMat(c, temp, temp2);
        matrice_substract(d, temp2, Z);

        // t=Z⁻1
        strassen_inverse_recursive_naive(Z, t);

        naiveMultMat(b, t, temp);
        naiveMultMat(e, temp, temp2);

        copyMatrix(temp2, y);

        negativeMatrix(y);

        naiveMultMat(c, e, temp3);

        naiveMultMat(t, temp3, z);
        negativeMatrix(z);

        naiveMultMat(temp2, temp3, temp);

        matrice_add(e, temp, x);

        fillBigMatrix(result, x, 0, 0);
        fillBigMatrix(result, y, 0, size / 2);
        fillBigMatrix(result, z, size / 2, 0);
        fillBigMatrix(result, t, size / 2, size / 2);
    }
    // donc d est inversible
    else
    {
        printf("dsojbgfdsjkbfskdqjfjbfzjfk");
        // e=d⁻1
        strassen_inverse_recursive_naive(d, e);

        // Z=a-bec
        naiveMultMat(e, c, temp);
        naiveMultMat(b, temp, temp2);
        matrice_substract(a, temp2, Z);

        // t= Z⁻1
        strassen_inverse_recursive_naive(Z, t);

        // c*t
        naiveMultMat(c, t, temp);
        // e*c*t
        naiveMultMat(e, temp, z);
        // z=
        negativeMatrix(z);

        naiveMultMat(b, e, temp);
        naiveMultMat(t, temp, temp2);
        copyMatrix(temp2, y);
        negativeMatrix(y);

        naiveMultMat(c, temp2, temp);
        naiveMultMat(e, temp, temp2);

        matrice_add(e, temp2, x);

        fillBigMatrix(result, t, 0, 0);
        fillBigMatrix(result, y, 0, size / 2);
        fillBigMatrix(result, z, size / 2, 0);
        fillBigMatrix(result, x, size / 2, size / 2);
    }
}

void strassen_inverse_recursive_strassen(matrix *A, matrix *result)
{   
    // pour eviter le cas 
    // {0, 1, 1, 1, 1, 0, 1, 1, 2, 3, 0, 1, 1, 2, 0, 1};
    if (A->columns == 2)
    {
        inverse_PLUQ(A,result);
        return;
    }

    int size = A->columns;

    matrix *a = creeMatrix(size / 2, size / 2);
    matrix *b = creeMatrix(size / 2, size / 2);
    matrix *c = creeMatrix(size / 2, size / 2);
    matrix *d = creeMatrix(size / 2, size / 2);
    createSubmatrix(A, a, 0, 0);
    createSubmatrix(A, b, 0, size / 2);
    createSubmatrix(A, c, size / 2, 0);
    createSubmatrix(A, d, size / 2, size / 2);

    matrix *e = creeMatrix(size / 2, size / 2);
    matrix *Z = creeMatrix(size / 2, size / 2);

    matrix *temp = creeMatrix(size / 2, size / 2);
    matrix *temp2 = creeMatrix(size / 2, size / 2);
    matrix *temp3 = creeMatrix(size / 2, size / 2);

    matrix *x = creeMatrix(size / 2, size / 2);
    matrix *y = creeMatrix(size / 2, size / 2);
    matrix *z = creeMatrix(size / 2, size / 2);
    matrix *t = creeMatrix(size / 2, size / 2);

    int det_a = determinant(a);
    int det_d = determinant(d);
    // si a est inversible

    if (fabs(det_a) > fabs(det_d))
    {

        // e=a⁻1
        strassen_inverse_recursive_naive(a, e);

        // Z=d-ceb
        strassen(e, b, temp,2);
        strassen(c, temp, temp2,2);
        matrice_substract(d, temp2, Z);

        // t=Z⁻1
        strassen_inverse_recursive_naive(Z, t);

        strassen(b, t, temp,2);
        strassen(e, temp, temp2,2);

        copyMatrix(temp2, y);

        negativeMatrix(y);

        strassen(c, e, temp3,2);

        strassen(t, temp3, z,2);
        negativeMatrix(z);

        naiveMultMat(temp2, temp3, temp);

        matrice_add(e, temp, x);

        fillBigMatrix(result, x, 0, 0);
        fillBigMatrix(result, y, 0, size / 2);
        fillBigMatrix(result, z, size / 2, 0);
        fillBigMatrix(result, t, size / 2, size / 2);
    }
    // donc d est inversible
    else
    {
        printf("dsojbgfdsjkbfskdqjfjbfzjfk");
        // e=d⁻1
        strassen_inverse_recursive_naive(d, e);

        // Z=a-bec
        strassen(e, c, temp,2);
        strassen(b, temp, temp2,2);
        matrice_substract(a, temp2, Z);

        // t= Z⁻1
        strassen_inverse_recursive_naive(Z, t);

        // c*t
        strassen(c, t, temp,2);
        // e*c*t
        strassen(e, temp, z,2);
        // z=
        negativeMatrix(z);

        strassen(b, e, temp,2);
        strassen(t, temp, temp2,2);
        copyMatrix(temp2, y);
        negativeMatrix(y);

        strassen(c, temp2, temp,2);
        strassen(e, temp, temp2,2);

        matrice_add(e, temp2, x);

        fillBigMatrix(result, t, 0, 0);
        fillBigMatrix(result, y, 0, size / 2);
        fillBigMatrix(result, z, size / 2, 0);
        fillBigMatrix(result, x, size / 2, size / 2);
    }
}



void strassen_inverse_naive(matrix *A, matrix *result)
{
    matrix *Aajuste = creeMatrix(nextPowerOfTwo(A->rows > A->columns ? A->rows : A->columns), nextPowerOfTwo(A->rows > A->columns ? A->rows : A->columns));
    matrix *paddedResult = creeMatrix(nextPowerOfTwo(A->rows > A->columns ? A->rows : A->columns), nextPowerOfTwo(A->rows > A->columns ? A->rows : A->columns));
    ajusteMatrix(A, Aajuste);
    strassen_inverse_recursive_naive(Aajuste, paddedResult);
    extractResult(paddedResult, result, A->rows, A->columns);
    freeMatrix(*Aajuste);
    freeMatrix(*paddedResult);
}
