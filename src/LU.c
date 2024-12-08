#include <stdio.h>
#include "../include/LU.h"
#include "../include/matrix.h"

void LU(matrix *A, matrix *L, matrix *U) {
    identity(L);
    copyMatrix(A, U);
    for (int i = 0; i < U->rows; i++) {
        if (U->coefs[i][i] == 0) {
            printf("LU impossible pivot 0\n");
            return;
        }
        for (int j = i + 1; j < U->rows; j++) {
            double coeff = U->coefs[j][i];
            for (int k = i; k < U->columns; k++) {
                U->coefs[j][k] -= coeff / U->coefs[i][i] * U->coefs[i][k];
            }
            L->coefs[j][i] = coeff / U->coefs[i][i];
        }
    }
}

void PLUQ(matrix *A, matrix *P, matrix *L, matrix *U, matrix *Q) {
    int size = A->rows;
    copyMatrix(A, U);
    identity(L);
    identity(P);
    identity(Q);
    for (int i = 0; i < size - 1; i++) {
        int facteur_ligne;
        int facteur_colonne;
        find_greatest_in_sub_matrix(U, i, &facteur_ligne, &facteur_colonne);
        P->coefs[i][i] = 0;
        P->coefs[facteur_colonne][facteur_colonne] = 0;
        P->coefs[facteur_colonne][i] = 1;
        P->coefs[i][facteur_colonne] = 1;
        Q->coefs[i][i] = 0;
        Q->coefs[facteur_ligne][facteur_ligne] = 0;
        Q->coefs[facteur_ligne][i] = 1;
        Q->coefs[i][facteur_ligne] = 1;
        for (int k = 0; k < size; k++) {
            double temp = U->coefs[i][k];
            U->coefs[i][k] = U->coefs[facteur_ligne][k];
            U->coefs[facteur_ligne][k] = temp;
        }
        for (int k = 0; k < size; k++) {
            double temp = U->coefs[k][facteur_colonne];
            U->coefs[k][facteur_colonne] = U->coefs[k][i];
            U->coefs[k][i] = temp;
        }
        for (int j = i + 1; j < size; j++) {
            double facteur = U->coefs[j][i] / U->coefs[i][i];
            L->coefs[j][i] = facteur;
            for (int a = 0; a < size; a++) {
                U->coefs[j][a] -= U->coefs[i][a] * facteur;
            }
        }
    }
}
