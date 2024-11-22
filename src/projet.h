typedef struct matrix
{
    double **coefs;
    int columns;
    int rows;
} matrix;



void printMatrix(matrix A);
void freeMatrix(matrix m);
matrix creeMatrix(int rows, int columns);
void remplirMatrixManuel(matrix A); //Fonction qui remplie manuellement la matrice à partir du terminal
void copyMatrix(matrix A, matrix copy); //Fonction qui copie la matrice A dans la matrice copy
void identity(matrix A); //Fonction qui retourne la matrice identité
void naiveMultMat(matrix A, matrix B, matrix result);
void strassen(matrix A, matrix B, matrix C);
void LU(matrix A, matrix L, matrix U);
