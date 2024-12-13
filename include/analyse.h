// Simon Sepiol-Duchemin Joshua Setia

#ifndef ANALYSE_H
#define ANALYSE_H

#include "../include/matrix.h"
#include "../include/LU.h"
#include "../include/strassen.h"

void fillMatrixRandom(matrix *M);
double tpsMoy_MultNaive(int nbTests, int taille);
double tpsMoy_MultStrassen(int nbTests, int taille);
double tpsMoy_InversePLUQ(int nbTests, int taille);
double tpsMoy_InverseStrassenNaive(int nbTests, int taille);
double tpsMoy_InverseStrassenStrassen(int nbTests, int taille);
void analysePetitesTailles(double (*func)(int, int), int nbTests, int tailleMax);
void analyseGrandesTailles(double (*func)(int, int), int nbTests, int tailleMax);

#endif