// Simon Sepiol-Duchemin Joshua Setia

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/matrix.h"
#include "../include/strassen.h"
#include "../include/LU.h"
#include "../include/analyse.h"



int main(int argc, char const *argv[])
{
    srand(time(NULL));
    
    //Tests temps d'exécution
    printf("Multiplication naive petites tailles, ");
    analysePetitesTailles(tpsMoy_MultNaive, 40, 64, 0);
    printf("\nMultiplication strassen petites tailles Limite=200, ");
    analysePetitesTaillesStrassen(tpsMoy_MultStrassen, 40, 64, 0, 200);
    printf("\nMultiplication strassen petites tailles Limite=128, ");
    analysePetitesTaillesStrassen(tpsMoy_MultStrassen, 40, 64, 0, 128); 
    printf("\nMultiplication strassen petites tailles Limite=64, ");
    analysePetitesTaillesStrassen(tpsMoy_MultStrassen, 40, 64, 0, 64);

    printf("\n\nMultiplication naive, ");
    analyseGrandesTailles(tpsMoy_MultNaive, 40, 10, 0);
    printf("\nMultiplication strassen Limite=256, ");
    analyseGrandesTaillesStrassen(tpsMoy_MultStrassen, 40, 10, 0, 256);
    printf("\nMultiplication strassen Limite=128, ");
    analyseGrandesTaillesStrassen(tpsMoy_MultStrassen, 40, 10, 0, 128);
    printf("\nMultiplication strassen Limite=64, ");
    analyseGrandesTaillesStrassen(tpsMoy_MultStrassen, 40, 10, 0, 64);
    printf("\nMultiplication strassen Limite=32, ");
    analyseGrandesTaillesStrassen(tpsMoy_MultStrassen, 40, 10, 0, 32);
    printf("\nMultiplication strassen Limite=16, ");
    analyseGrandesTaillesStrassen(tpsMoy_MultStrassen, 40, 10, 0, 16);
    //printf("\nMultiplication strassen Limite=8, ");
    //analyseGrandesTaillesStrassen(tpsMoy_MultStrassen, 40, 11, 0, 8);

    printf("\n\nInversion PLUQ, ");
    analyseGrandesTailles(tpsMoy_InversePLUQ, 30, 10, 0);
    printf("\nInversion strassen (avec multiplication naive), ");
    analyseGrandesTailles(tpsMoy_InverseStrassenNaive, 30, 10, 0);
    printf("\nInversion strassen (avec multiplication strassen) Limite=64, ");
    analyseGrandesTaillesStrassen(tpsMoy_InverseStrassenStrassen, 30, 10, 0, 64);




    //Tests mémoire
    printf("Multiplication naive petites tailles, ");
    analysePetitesTailles(tpsMoy_MultNaive, 40, 64, 1);
    printf("\nMultiplication strassen petites tailles Limite=200, ");
    analysePetitesTaillesStrassen(tpsMoy_MultStrassen, 40, 64, 1, 200);
    printf("\nMultiplication strassen petites tailles Limite=128, ");
    analysePetitesTaillesStrassen(tpsMoy_MultStrassen, 40, 64, 1, 128); 
    printf("\nMultiplication strassen petites tailles Limite=64, ");
    analysePetitesTaillesStrassen(tpsMoy_MultStrassen, 40, 64, 1, 64);

    printf("\n\nMultiplication naive, ");
    analyseGrandesTailles(tpsMoy_MultNaive, 40, 10, 1);
    printf("\nMultiplication strassen Limite=256, ");
    analyseGrandesTaillesStrassen(tpsMoy_MultStrassen, 40, 10, 1, 256);
    printf("\nMultiplication strassen Limite=128, ");
    analyseGrandesTaillesStrassen(tpsMoy_MultStrassen, 40, 10, 1, 128);
    printf("\nMultiplication strassen Limite=64, ");
    analyseGrandesTaillesStrassen(tpsMoy_MultStrassen, 40, 10, 1, 64);
    printf("\nMultiplication strassen Limite=32, ");
    analyseGrandesTaillesStrassen(tpsMoy_MultStrassen, 40, 10, 1, 32);
    printf("\nMultiplication strassen Limite=16, ");
    analyseGrandesTaillesStrassen(tpsMoy_MultStrassen, 40, 10, 1, 16);
    //printf("\nMultiplication strassen Limite=8, ");
    //analyseGrandesTaillesStrassen(tpsMoy_MultStrassen, 40, 11, 1, 8);

    printf("\n\nInversion PLUQ, ");
    analyseGrandesTailles(tpsMoy_InversePLUQ, 40, 10, 1);
    printf("\nInversion strassen (avec multiplication naive), ");
    analyseGrandesTailles(tpsMoy_InverseStrassenNaive, 40, 10, 1);
    printf("\nInversion strassen (avec multiplication strassen) Limite=64, ");
    analyseGrandesTaillesStrassen(tpsMoy_InverseStrassenStrassen, 40, 10, 1, 64);
    return 0;
}
