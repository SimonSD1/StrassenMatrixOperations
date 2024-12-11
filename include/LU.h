// Simon Sepiol-Duchemin Joshua Setia

#ifndef DECOMPOSITION_H
#define DECOMPOSITION_H

#include "../include/matrix.h"

void LU(matrix *A, matrix *L, matrix *U);
int PLUQ(matrix *A, matrix *P, matrix *L, matrix *U, matrix *Q);
void inverse_PLUQ(matrix *A, matrix *result);


#endif
