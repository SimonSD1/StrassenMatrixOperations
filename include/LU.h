#ifndef DECOMPOSITION_H
#define DECOMPOSITION_H

#include "../include/matrix.h"

void LU(matrix *A, matrix *L, matrix *U);
void PLUQ(matrix *A, matrix *P, matrix *L, matrix *U, matrix *Q);

#endif
