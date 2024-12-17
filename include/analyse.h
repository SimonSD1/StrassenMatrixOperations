// Simon Sepiol-Duchemin Joshua Setia

#ifndef ANALYSE_H
#define ANALYSE_H

#include "../include/matrix.h"
#include "../include/LU.h"
#include "../include/strassen.h"

void fillMatrixRandom(matrix *M);
double tpsMoy_MultNaive(int nbTests, int taille, int tpsMem);
double tpsMoy_MultStrassen(int nbTests, int taille, int tpsMem, int limite);
double tpsMoy_InversePLUQ(int nbTests, int taille, int tpsMem);
double tpsMoy_InverseStrassenNaive(int nbTests, int taille, int tpsMem);
double tpsMoy_InverseStrassenStrassen(int nbTests, int taille, int tpsMem, int limite);
void analysePetitesTailles(double (*func)(int, int, int), int nbTests, int tailleMax, int tpsMem);
void analysePetitesTaillesStrassen(double (*func)(int, int, int, int), int nbTests, int tailleMax, int tpsMem, int limite);
void analyseGrandesTailles(double (*func)(int, int, int), int nbTests, int tailleMax, int tpsMem);
void analyseGrandesTaillesStrassen(double (*func)(int, int, int, int), int nbTests, int tailleMax, int tpsMem, int limite);  //Permet de fixer la limite

#endif