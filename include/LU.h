#ifndef DECOMPOSITION_H
#define DECOMPOSITION_H

#include "../include/matrix.h"

void LU(matrix *A, matrix *L, matrix *U);
int PLUQ(matrix *A, matrix *P, matrix *L, matrix *U, matrix *Q);

void swapRows(matrix *M, int row1, int row2);
void swapColumns(matrix *M, int row1, int row2);
#endif
