// Simon Sepiol-Duchemin Joshua Setia

#ifndef STRASSEN_H
#define STRASSEN_H

#include "../include/matrix.h"

void strassen(matrix *A, matrix *B, matrix *result, int limite);
void strassen_inverse_naive(matrix *A, matrix *result);
void strassen_inverse_recursive_naive(matrix *A, matrix *result);
void strassen_inverse_recursive_strassen(matrix *A, matrix *result, int limite);
void strassenRecursive(matrix *C, matrix *A, matrix *B, int limite) ;

#endif
