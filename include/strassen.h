#ifndef STRASSEN_H
#define STRASSEN_H

#include "../include/matrix.h"

void strassen(matrix *A, matrix *B, matrix *result, int limite);
void strassen_inverse_naive(matrix *A, matrix *result);

#endif
